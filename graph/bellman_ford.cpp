//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：BellmanFord算法
 *  对每条边执行n-1次松弛操作
 */

#include "relax.h"

template<typename T>
void GraphAlgorithm::bellmanFord(Graph<T> *graph, size_t s) {
    graph->reset();
    // 获取所有边信息
    std::vector<Edge> edges;
    for (int u = 0; u < graph->vSize(); ++u) {
        for (int v = graph->firstNbr(u); -1 < v ; v = graph->nextNbr(u, v)) {
            edges.push_back({{u, v}, graph->weight(u, v)});
        }
    }
    // 执行BellmanFord算法
    graph->priority(s) = 0;
    for (int i = 1; i < graph->vSize(); ++i) {
        for(auto edge: edges)
            relax(graph, edge.first.first, edge.first.second);
    }
    // 检测是否存在环路
    for(auto edge: edges) {
        auto p = graph->priority(edge.first.second);
        relax(graph, edge.first.first, edge.first.second);
        if (graph->priority(edge.first.second) < p)
            throw std::logic_error("The current graph has a negative loop");
    }
}
