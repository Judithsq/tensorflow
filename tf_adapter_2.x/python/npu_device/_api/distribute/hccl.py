from npu_device._api.distribute import hccl_ops
from npu_device.npu_device import global_npu_ctx

import tensorflow as tf


def shard_and_rebatch_dataset(dataset, global_bs):
    if global_npu_ctx() is None or global_npu_ctx().workers_num <= 1:
        return dataset, global_bs
    if global_bs % global_npu_ctx().workers_num != 0:
        raise ValueError('Batch size must be divisible by num npus: {}'.format(global_npu_ctx().workers_num))

    batch_size = int(global_bs) / global_npu_ctx().workers_num
    dataset = dataset.shard(global_npu_ctx().workers_num, global_npu_ctx().worker_id)

    return dataset, int(batch_size)


def _all_reduce(values, reduction, fusion, fusion_id, group):
    workers_num = global_npu_ctx().workers_num

    mean_reduce = False
    if reduction == 'mean':
        mean_reduce = True
        reduction = 'sum'

    topo_guarder = tf.group(values)
    if isinstance(values, (list, tuple,)):
        reduced_values = []
        for value in values:
            reduced_value = hccl_ops.allreduce(value, reduction, fusion, fusion_id, group)
            typed_workers_num = tf.cast(workers_num, reduced_value.dtype)
            with tf.control_dependencies([topo_guarder]):
                if mean_reduce:
                    reduced_values.append(tf.divide(reduced_value, typed_workers_num))
                else:
                    reduced_values.append(tf.identity(reduced_value))
        return reduced_values
    else:
        reduced_value = hccl_ops.allreduce(values, reduction, fusion, fusion_id, group)
        typed_workers_num = tf.cast(workers_num, reduced_value.dtype)
        with tf.control_dependencies([topo_guarder]):
            if mean_reduce:
                return tf.divide(reduced_value, typed_workers_num)
            else:
                return tf.identity(reduced_value)


def all_reduce(values, reduction, fusion=1, fusion_id=-1, group="hccl_world_group"):
    if global_npu_ctx() is None or not global_npu_ctx().is_cluster_worker():
        tf.get_logger().info("Skip all-reduce value as current process is not npu cluster worker")
        return values

    return tf.function(_all_reduce)(values, reduction, fusion, fusion_id, group)


def _broadcast(values, root_rank, fusion, fusion_id, group):
    if isinstance(values, (list, tuple,)):
        for value in values:
            value.assign(hccl_ops.broadcast([value], root_rank, fusion, fusion_id, group)[0])
    else:
        values.assign(hccl_ops.broadcast([values], root_rank, fusion, fusion_id, group)[0])


def broadcast(values, root_rank, fusion=2, fusion_id=0, group="hccl_world_group"):
    if global_npu_ctx() is None or not global_npu_ctx().is_cluster_worker():
        tf.get_logger().info("Skip broadcast value as current process is not npu cluster worker")
        return

    tf.function(_broadcast)(values, root_rank, fusion, fusion_id, group)
