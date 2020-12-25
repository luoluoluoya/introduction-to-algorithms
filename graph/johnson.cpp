//
// Created by 张锐 on 2020/12/25.
//

#include "matrix_graph.h"
#include "init_graph_matrix.h"

// 更改图中所有边的权重为：w`(u, v) = w(u,v) + h(u)-h(v); (h(x) 为 s到x的最短距离)
template<typename T>
void changeWeight(Graph<T> *graph) {
    for (int u = 0; u < graph->vSize(); ++u) {
        for (int v = 0; v < graph->vSize(); ++v) {
            if (graph->exists(u, v)) {
                graph->weight(u, v) = graph->weight(u, v) + graph->priority(u) - graph->priority(v);
            }
        }
    }
}


template<typename T>
void resetGraph(Graph<T> *graph, std::vector<int> h) {

}


// 返回任意节点的最短路径
template<typename T>
std::pair<int **, int **> GraphAlgorithm::johnson(Graph<T> *graph) {
    int **shortest = initEmptyMatrix(graph);
    int **path = initEmptyMatrix(graph);

    // 获取引入新源节点s和更新权重之后的图结构
    size_t s = graph->insert(T());
    for (int i = 0; i < graph->vSize(); ++i) {
        graph->insert(s, i, 0);
    }
    bellmanFord(graph, s);
    changeWeight(graph);
    // 保存h(x)
    std::vector<int> h;
    for (int i = 0; i < graph->vSize(); ++i) {
        h.push_back(graph->priority(i));
    }

    // 执行n次dijkstra算法
    for (int u = 0; u < graph->vSize() - 1; ++u) {
        dijkstra(graph, u);
        // 获取最短路径
        for (int v = 0; v < graph->vSize(); ++v) {
            // 存在最短路径时, 设置最短路径值
            if (graph->priority(v) != INT_MAX) {
                shortest[u][v] = graph->priority(v) + h[v] - h[u];
            }
            path[u][v] = graph->parent(v);
        }
    }

    // 恢复当前图结构
//    for (int u = 0; u < graph->vSize(); ++u) {
//        for (int v = 0; v < graph->vSize(); ++v) {
//            if (graph->exists(u, v)) {
//                graph->weight(u, v) = graph->weight(u, v) + graph->priority(v) - graph->priority(u);
//            }
//        }
//    }
//    graph->remove(graph->vSize()-1);

    return {shortest, path};
}

