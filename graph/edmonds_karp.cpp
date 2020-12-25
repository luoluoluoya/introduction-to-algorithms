//
// Created by 47302 on 2020/12/25.
//

/*
 * 最大流：Edmonds-Karp算法
 */

#include "init_graph_matrix.h"


//残存网络中s->t路径上的残存容量
template<typename T>
int remainingCapacity(Graph<T> *rng, size_t s, size_t t) {
    int capacity = INT_MAX;
    while (rng->parent(t) != -1) {
        capacity = std::min(capacity, rng->weight(rng->parent(t), t));
        t = rng->parent(t);
    }
    return capacity;
}

//用残存流量递增流
template<typename T>
void increasingFlow(Graph<T> *graph, Graph<T> *rng, size_t s, size_t t, int **flow) {
    int capacity = remainingCapacity(rng, s, t);
    while (rng->parent(t) != -1) {
        if (graph->exists(rng->parent(t), t)) {
            flow[rng->parent(t)][t] += capacity;
        } else {
            flow[t][rng->parent(t)] -= capacity;
        }
        t = rng->parent(t);
    }
}

// 获取最大流
template<typename T>
int ** GraphAlgorithm::edmondsKarp(Graph<T> *graph, size_t s, size_t t) {
    int **flow = initFlowMatrix(graph);
    Graph<T> *rng = remnantNetworks(graph, flow);
    bfs(rng, s);
    while (rng->parent(t) != -1) {
        increasingFlow(graph, rng, s, t, flow);
        delete rng;
        rng = remnantNetworks(graph, flow);
        bfs(rng, s);
    }
    delete rng;
    return flow;
}