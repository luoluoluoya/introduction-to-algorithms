//
// Created by 张锐 on 2020/12/24.
//

/*
 * 基于inDegree的拓扑排序算法
 */

#include <map>
#include <vector>
#include <stack>

template<typename T>
std::vector<size_t> GraphAlgorithm::topologicalByDegree(Graph<T> *graph) {
    //基本信息获取
    std::map<size_t, size_t> inDegree;
    std::vector<size_t> nodes;
    for (int v = 0; v < MAX_NODE_NUM; ++v) {
        if (graph->exists(v)) {
            inDegree[v] = graph->inDegree(v);
            nodes.push_back(v);
        }
    }
    // 不断获取入度为0的节点加入拓扑排序序列直至所有节点均已加入。若不存在入度为0的节点时，证明存在环路，终止算法执行
    std::vector<size_t> topological;
    while (!nodes.empty()) {
        auto iter = std::find_if(nodes.begin(), nodes.end(), [&inDegree](size_t a) { return inDegree[a] == 0; });
        if (iter == nodes.end())
            throw std::logic_error("the current graph exists in a loop");
        topological.push_back(*iter);
        for (int v = graph->firstNbr(*iter); -1 < v; v = graph->nextNbr(*iter, v))
            inDegree[v]--;
        nodes.erase(iter);
    }
    return topological;
}
