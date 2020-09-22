/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BBOX_PROXY_H
#define BBOX_PROXY_H

#include "bbox_proxy_config.h"

typedef struct proxy_excep_time_t {
    unsigned long long tv_sec;
    unsigned long long tv_usec;
} proxy_excep_time;

enum BBOX_PROXY_DUMP_STATUS {
    PROXY_STATUS_INIT  = 0,
    PROXY_STATUS_DOING = 1,
    PROXY_STATUS_DONE  = 2,
};

struct bbox_proxy_exception_ctrl {
    proxy_excep_time e_clock;           // 模块触发异常时间
    unsigned int e_main_excepid;        // 模块触发的异常id
    unsigned int e_sub_excepid;         // 模块触发的异常id
    unsigned int e_info_offset;         // 模块全部异常信息偏移值，基于模块预留内存首地址，从magic开始
    unsigned int e_info_len;            // 模块全部异常信息长度
    unsigned short e_dump_status;       // 模块将异常信息存预留内存的控制状态
    unsigned short e_save_status;       // 代理将异常信息从预留内存导出的控制状态
    unsigned int e_reserved;            // 结构对齐预留
};

// 通过共享内存交互
#define BBOX_PROXY_MAGIC                0x56312e31
#define BBOX_PROXY_CTRL_RESERV          192

struct bbox_proxy_module_ctrl {
    unsigned int magic;                                             // 使用宏BBOX_PROXY_MAGIC
    struct bbox_proxy_ctrl_info config;                             // ctrl块配置
    struct bbox_proxy_exception_ctrl block[BBOX_PROXY_CTRL_NUM];    // 模块dump信息控制状态
    unsigned char reserved[BBOX_PROXY_CTRL_RESERV];                 // 预留空间，用于后续扩展
};

#define BBOX_PROXY_CTRL_BLOCK_SIZE sizeof(struct bbox_proxy_module_ctrl) // total 512 byte

#endif // BBOX_PROXY_H
