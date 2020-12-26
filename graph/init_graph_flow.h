//
// Created by 47302 on 2020/12/26.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H
#define INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H

// 设置图上的流信息
template<typename T>
static inline void initGraphFlow(Graph<T> *&graph) {
    for (int u = 0; u < graph->vSize(); ++u) {
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
        }
    }
}

#endif //INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H
