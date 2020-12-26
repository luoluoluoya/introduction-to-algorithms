//
// Created by 47302 on 2020/12/26.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H
#define INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H

// 设置图上的流信息
template<typename T>
static inline void initGraphFlow(Graph<T> *&graph, size_t s) {
    for (int u = 0; u < graph->vSize(); ++u) {
        graph->height(u) = ( u == s ? graph->vSize() : 0 );
        graph->excess(u) = 0;
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            graph->flow(u, v) = 0;
        }
    }
}

#endif //INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H
