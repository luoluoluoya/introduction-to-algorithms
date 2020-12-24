//
// Created by 张锐 on 2020/12/24.
//

#ifndef ALGORITHM_INIT_SHORTEST_MATRIX_H
#define ALGORITHM_INIT_SHORTEST_MATRIX_H

/*
 * 初始化最短路径矩阵
 */

template<typename T>
static inline int** initShortestMatrix(Graph<T>* &graph) {
    int shortest[graph->vSize()][graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        shortest[i][i] = 0;
        for (int j = 0; j < graph->vSize(); ++j) {
            shortest[i][j] = graph->exists(i, j) ? graph->weight(i, j) : INT_MAX;
        }
    }
    return shortest;
}

#endif //ALGORITHM_INIT_SHORTEST_MATRIX_H
