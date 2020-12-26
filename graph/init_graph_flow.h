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
            graph->flow(u, v) = 0;
        }
    }
}

// 初始化推送重贴标签算法上的高度函数和超额流信息
template<typename T>
static inline void initPushRelabel(Graph<T> *&graph, size_t s) {
    for (int u = 0; u < graph->vSize(); ++u) {
        graph->height(u) = 0;
        graph->excess(u) = 0;
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            graph->flow(u, v) = 0;
        }
    }
    graph->height(s) = graph->vSize();
    for (int v = graph->firstNbr(s); -1 < v; v = graph->nextNbr(s, v)) {
        graph->flow(s, v) = graph->weight(s, v);
        graph->excess(v)  = graph->weight(s, v);
        graph->excess(s) -= graph->weight(s, v);
    }
}


// 统计边上的流信息
template<typename T>
std::vector<typename GraphAlgorithm::Edge> statisticalFlow(Graph<T> *graph) {
    std::vector<typename GraphAlgorithm::Edge> flow;
    for (int u = 0; u < graph->vSize(); ++u) {
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            flow.push_back( {{u, v}, graph->flow(u, v)} );
        }
    }
    return flow;
}

#endif //INTRODUCTION_TO_ALGORITHMS_INIT_GRAPH_FLOW_H
