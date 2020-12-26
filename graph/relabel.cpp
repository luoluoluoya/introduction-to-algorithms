//
// Created by 47302 on 2020/12/25.
//


#include "graph_algorithm.h"


// 存在超额流的节点u， 其所有在残存网络中的边 (u, v) 若都不满足高度v在节点u的下方而导致的无法推送，则可以进行重贴标签
template<typename T>
bool GraphAlgorithm::relabel(Graph<T> *graph, Graph<T> *rng, size_t u) {
    if (graph->excess(u) <= 0)
        return false;
    bool lessAll = true;
    size_t minH = INT_MAX;
    for (int v = rng->firstNbr(u); -1 < v; v = rng->nextNbr(u, v)) {
        if (graph->height(u) > graph->height(v)) {
            lessAll = false;
        }
        minH = std::min(minH, graph->height(v));
    }
    if (!lessAll)
        return false;
    graph->height(u) = minH + 1;
}