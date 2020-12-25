//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：动态规划求解任意节点对的最短路径
 */

#include "init_graph_matrix.h"

static inline void dynamicShortestPath(int**& path, size_t i, size_t j, std::vector<size_t>& nodes) {
    size_t k = path[i][j];
    if (i != j && k != INT_MAX)
        dynamicShortestPath(path, i, k, nodes);
    nodes.push_back(k);
}

// 返回任意节点的最短路径
static inline std::vector<size_t> dynamicShortestPath(int**& path, size_t i, size_t j) {
    std::vector<size_t> nodes;
    dynamicShortestPath(path, i, j, nodes);
    nodes.push_back(j);
    return nodes;
}


// 在(i,j)中新增边以尝试扩展最短路径
template<typename T>
static inline int **extendShortestPath(Graph<T> *&graph, int **L, int **W, int **&path) {
    static int a = 1;
    int **L1 = initEmptyMatrix(graph);
    for (int i = 0; i < graph->vSize(); ++i) {
        for (int j = 0; j < graph->vSize(); ++j) {
            for (int k = 0; k < graph->vSize(); ++k) {
                // i到k可达且e(k,j)存在时尝试对其进行优化
                if (L[i][k] < INT_MAX && W[k][j] < INT_MAX) {
                    if (L1[i][j] > L[i][k] + W[k][j]) {
                        path[i][j] = k;
                        L1[i][j] = L[i][k] + W[k][j];
                    }
                }
            }
        }
    }
    return L1;
}

// 动态规划求解任意节点对的最短路径
template<typename T>
std::pair<int **, int **> GraphAlgorithm::shortestByDynamic(Graph<T> *graph) {
    int **W = initWeightMatrix(graph);
    int **shortest = initWeightMatrix(graph);
    int **path = initEmptyMatrix(graph);
    // 在任意节点对(i,j)中引入m条边
    for (int m = 2; m < graph->vSize() - 1; ++m) {
        int **LSucc = extendShortestPath(graph, shortest, W, path);
        destructGraphMatrix(graph, shortest);
        shortest = LSucc;
    }
    // 检测是否存在环路
    int **LSucc = extendShortestPath(graph, shortest, W, path);
    for (int i = 0; i < graph->vSize(); ++i) {
        for (int j = 0; j < graph->vSize(); ++j) {
            if (LSucc[i][j] < shortest[i][j])
                throw std::logic_error("The current graph has a negative loop");
        }
    }
    destructGraphMatrix(graph, W);
    destructGraphMatrix(graph, LSucc);
    return std::make_pair(shortest, path);
}
