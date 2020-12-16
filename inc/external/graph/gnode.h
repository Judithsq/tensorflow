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

#ifndef INC_EXTERNAL_GRAPH_NODE_H_
#define INC_EXTERNAL_GRAPH_NODE_H_

#include <vector>
#include <cstdint>

#include "./ge_error_codes.h"
#include "./types.h"
#include "./tensor.h"
#include "./ascend_string.h"

namespace ge {
class AttrValue;
class GNode;
class OpDesc;
class Graph;
class ComputeGraph;
using GNodePtr = std::shared_ptr<GNode>;
using GraphPtr = std::shared_ptr<Graph>;
using OpBytes = std::vector<uint8_t>;
using OpDescPtr = std::shared_ptr<OpDesc>;
using ComputeGraphPtr = std::shared_ptr<ComputeGraph>;

class NodeImpl;
class GE_FUNC_DEV_VISIBILITY GE_FUNC_HOST_VISIBILITY GNode {
 public:
  GNode();

  ~GNode() = default;

  graphStatus GetType(ge::AscendString &type) const;

  graphStatus GetName(ge::AscendString &name) const;

  std::pair<GNodePtr, int32_t> GetInDataNodesAndPortIndexs(const int32_t index) const;

  std::vector<GNodePtr> GetInControlNodes() const;

  std::vector<std::pair<GNodePtr, int32_t>> GetOutDataNodesAndPortIndexs(const int32_t index) const;

  std::vector<GNodePtr> GetOutControlNodes() const;

  graphStatus GetInputConstData(const int32_t index, Tensor &data) const;

  graphStatus GetInputIndexByName(const ge::AscendString &name, int32_t &index);

  graphStatus GetOutputIndexByName(const ge::AscendString &name, int32_t &index);

  size_t GetInputsSize() const;

  size_t GetOutputsSize() const;

  graphStatus GetInputDesc(const int32_t index, TensorDesc &tensor_desc) const;

  graphStatus UpdateInputDesc(const int32_t index, const TensorDesc &tensor_desc);

  graphStatus GetOutputDesc(const int32_t index, TensorDesc &tensor_desc) const;

  graphStatus UpdateOutputDesc(const int32_t index, const TensorDesc &tensor_desc);

  graphStatus GetAttr(const ge::AscendString &name, int64_t &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, int32_t &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, uint32_t &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, float &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, ge::AscendString &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, bool &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, Tensor &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<int64_t> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<int32_t> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<uint32_t> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<float> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<ge::AscendString> &attr_values) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<bool> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<Tensor> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, OpBytes &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<std::vector<int64_t>> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, std::vector<ge::DataType> &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, ge::DataType &attr_value) const;
  graphStatus GetAttr(const ge::AscendString &name, AttrValue &attr_value) const;

  graphStatus SetAttr(const ge::AscendString &name, int64_t &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, int32_t &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, uint32_t &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, float &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, ge::AscendString &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, bool &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, Tensor &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<int64_t> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<int32_t> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<uint32_t> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<float> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<ge::AscendString> &attr_values) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<bool> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<Tensor> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, OpBytes &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<std::vector<int64_t>> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, std::vector<ge::DataType> &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, ge::DataType &attr_value) const;
  graphStatus SetAttr(const ge::AscendString &name, AttrValue &attr_value) const;

  bool HasAttr(const ge::AscendString &name);

  graphStatus GetSubgraph(uint32_t index, GraphPtr &graph) const;

  graphStatus GetALLSubgraphs(std::vector<GraphPtr> &graph_list) const;

 private:
   std::shared_ptr<NodeImpl> impl_;
   friend class NodeAdapter;
};
}  // namespace ge
/*lint +e148*/

#endif  // INC_EXTERNAL_GRAPH_NODE_H_