//
// Created by 47302 on 2020/12/25.
//

#include "graph_algorithm.h"

//推送操作
template<typename T>
bool GraphAlgorithm::push(Graph<T> *graph, Graph<T> *rng, size_t u, size_t v) {
    if (graph->height(u) != graph->height(v) + 1)
        return false;
    size_t f = graph->excess(u) < rng->weight(u, v) ? graph->excess(u) : rng->weight(u, v);
    if (graph->exists(u, v))
        graph->flow(u, v) += f;
    else
        graph->flow(v, u) -= f;
    graph->excess(u) -= f;
    graph->excess(v) += f;
    return true;
}