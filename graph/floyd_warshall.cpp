//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：Floyd-Warshall算法
 */

template<typename T>
void GraphAlgorithm::floydWarshall(Graph<T> *graph) {
    // 初始化
    size_t shortest[graph->vSize()][graph->vSize()] = {INT_MAX};
    for (int u = 0; u < MAX_NODE_NUM; ++u) {
        if (!graph->exists(u)) continue;
        shortest[u][u] = 0;
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            shortest[u][v] = graph->weight(u,v);
        }
    }
}