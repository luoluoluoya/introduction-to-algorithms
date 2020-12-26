//
// Created by 47302 on 2020/12/25.
//

/*
 * 最大流：Edmonds-Karp算法
 */

#include "init_graph_flow.h"


//残存网络中s->t路径上的残存容量
template<typename T>
int remainingCapacity(Graph<T> *rng, size_t s, size_t t) {
    int capacity = INT_MAX;
    while (rng->parent(t) != s) {
        capacity = std::min(capacity, rng->weight(rng->parent(t), t));
        t = rng->parent(t);
    }
    return capacity;
}

//用残存流量递增流
template<typename T>
void increasingFlow(Graph<T> *graph, Graph<T> *rng, size_t s, size_t t) {
    int capacity = remainingCapacity(rng, s, t);
    while (rng->parent(t) != -1) {
        if (graph->exists(rng->parent(t), t)) {
            graph->flow(rng->parent(t), t) += capacity;
        } else {
            graph->flow(t, rng->parent(t)) -= capacity;
        }
        t = rng->parent(t);
    }
}


// Edmonds-Karp算法
template<typename T>
std::vector<typename GraphAlgorithm::Edge> GraphAlgorithm::edmondsKarp(Graph<T> *graph, size_t s, size_t t) {
    initGraphFlow(graph);
    Graph<T> *rng = remnantNetworks(graph);
    bfs(rng, s);
    while (rng->parent(t) != -1) {
        increasingFlow(graph, rng, s, t);
        delete rng;
        rng = remnantNetworks(graph);
        bfs(rng, s);
    }
    delete rng;
    return statisticalFlow(graph);
}
