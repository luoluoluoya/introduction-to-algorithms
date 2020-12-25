//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：Floyd-Warshall算法
 *  对于任意节点(i,j)的最短路径为考察在 i ~ j 中, 存在的其他节点数目k
 *      Dij(k) = min( Dij(k-1), Dik(k-1)+Dkj(k-1) ); k >= 1
 *             = w(i,j); k=0
 */

#include "init_graph_matrix.h"

static inline void printShortestPath(int**& path, size_t i, size_t j, std::vector<size_t>& nodes) {
    size_t k = path[i][j];
    if (k == INT_MAX)
        return;
    printShortestPath(path, i, k, nodes);
    nodes.push_back(k);
    printShortestPath(path, k, j, nodes);
}

// 返回任意节点的最短路径
static inline std::vector<size_t> printShortestPath(int**& path, size_t i, size_t j) {
    std::vector<size_t> nodes;
    nodes.push_back(i);
    printShortestPath(path, i, j, nodes);
    nodes.push_back(j);
    return nodes;
}

template<typename T>
std::pair<int**, int**> GraphAlgorithm::floydWarshall(Graph<T> *graph) {
    int **d = initWeightMatrix(graph);                          // (i, j) 不考察其他任何节点时的最短路径
    int **path = initEmptyMatrix(graph);
    for (int k = 0; k < graph->vSize(); ++k) {                  // (i, j) 中存在k个节点时的考察
        for (int i = 0; i < graph->vSize(); ++i) {
            for (int j = 0; j < graph->vSize(); ++j) {
                if (d[i][k] != INT_MAX && d[k][j] != INT_MAX && d[i][j] > d[i][k] + d[k][j]) {   // 判断可达性，避免int溢出
                    path[i][j] = k;
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    return std::make_pair(d, path);
}


/**
 *           10
 *      (0)----->(1)
 *               /\
 *             3/  \5
 *            /     \
 * (2)--->(3)------>(4)
 *     7        1
 */
//节点(0,0)最短路径值：0， 最短路径为：0 0
//节点(0,1)最短路径值：10， 最短路径为：0 1
//节点(0,2)不可达
//节点(0,3)最短路径值：13， 最短路径为：0 1 3
//节点(0,4)最短路径值：14， 最短路径为：0 1 3 4
//
//节点(1,0)不可达
//节点(1,1)最短路径值：0， 最短路径为：1 1
//节点(1,2)不可达
//节点(1,3)最短路径值：3， 最短路径为：1 3
//节点(1,4)最短路径值：4， 最短路径为：1 3 4
//
//节点(2,0)不可达
//节点(2,1)不可达
//节点(2,2)最短路径值：0， 最短路径为：2 2
//节点(2,3)最短路径值：7， 最短路径为：2 3
//节点(2,4)最短路径值：8， 最短路径为：2 3 4
//
//节点(3,0)不可达
//节点(3,1)不可达
//节点(3,2)不可达
//节点(3,3)最短路径值：0， 最短路径为：3 3
//节点(3,4)最短路径值：1， 最短路径为：3 4
//
//节点(4,0)不可达
//节点(4,1)不可达
//节点(4,2)不可达
//节点(4,3)不可达
//节点(4,4)最短路径值：0， 最短路径为：4 4
