//
// Created by 张锐 on 2020/12/25.
//

#include "adj_graph.h"
#include "init_graph_matrix.h"

// 更改图中所有边的权重并返回新节点到个节点的最短路径； 新权重为：w`(u, v) = w(u,v) + h(u)-h(v); (h(x) 为 s到x的最短距离)
template<typename T>
std::vector<int> changeWeight(Graph<T> *graph) {
    std::vector<int> h;
    for (int u = 0; u < graph->vSize(); ++u) {
        h.push_back(graph->priority(u));
        for (int v = 0; v < graph->vSize(); ++v) {
            if (graph->exists(u, v)) {
                graph->weight(u, v) = graph->weight(u, v) + graph->priority(u) - graph->priority(v);
            }
        }
    }
    return h;
}


// 引入源节点
template<typename T>
Graph<T>* introduceSource(Graph<T> *graph) {
    Graph<T>* newGraph = new AdjGraph<T>();
    for (int u = 0; u < graph->vSize(); ++u) {
        newGraph->insert(u);
    }
    size_t s = newGraph->insert(T());
    for (int u = 0; u < graph->vSize(); ++u) {
        newGraph->insert(s, u, 0);
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            newGraph->insert(u, v, graph->weight(u, v));
        }
    }
    return newGraph;
}

// 返回任意节点的最短路径
template<typename T>
std::pair<int **, int **> GraphAlgorithm::johnson(Graph<T> *graph) {
    int **shortest = initEmptyMatrix(graph);
    int **path = initEmptyMatrix(graph);
    // 获取引入新源节点s之后的图结构
    Graph<T>* newGraph = introduceSource(graph);
    bellmanFord(newGraph, newGraph->vSize()-1);
    std::vector<int> h = changeWeight(newGraph);

    // 执行n次dijkstra算法
    for (int u = 0; u < graph->vSize(); ++u) {
        dijkstra(newGraph, u);
        // 获取最短路径
        for (int v = 0; v < graph->vSize(); ++v) {
            // 存在最短路径时, 设置最短路径值
            if (newGraph->priority(v) != INT_MAX) {
                shortest[u][v] = newGraph->priority(v) + h[v] - h[u];
            }
            path[u][v] = newGraph->parent(v);
        }
    }
    return {shortest, path};
}

