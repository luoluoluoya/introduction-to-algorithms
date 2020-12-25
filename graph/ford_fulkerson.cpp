//
// Created by 47302 on 2020/12/25.
//

/*
 * 最大流：Ford-Fulkerson算法
 *      实现基本同Edmonds-Karp算法
 */

template<typename T>
int **GraphAlgorithm::fordFulkerson(Graph<T> *graph, size_t s, size_t t) {
    return edmondsKarp(graph, s, t);
}