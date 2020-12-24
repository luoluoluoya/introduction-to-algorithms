//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：动态规划求解任意节点对的最短路径
 */

#include "init_shortest_matrix.h"

template<typename T>
int** GraphAlgorithm::shortestByDynamic(Graph<T> *graph) {
    int shortest[graph->vSize()][graph->vSize()];
    int w[graph->vSize()][graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        shortest[i][i] = 0;
        w[i][i] = 0;
        for (int j = 0; j < graph->vSize(); ++j) {
            shortest[i][j] = graph->exists(i, j) ? graph->weight(i, j) : INT_MAX;
            w[i][j] = graph->exists(i, j) ? graph->weight(i, j) : INT_MAX;
        }
    }
    for (int n = 0; n < graph->vSize(); ++n) {
        for (int i = 0; i < graph->vSize(); ++i) {
            for (int j = 0; j < graph->vSize(); ++j) {
                for (int k = 0; k < graph->vSize(); ++k) {
                    if (shortest[i][j] > shortest[i][k] + w[k][j]) {
                        shortest[i][j] = shortest[i][j] + w[k][j];
                    }
                }
            }
        }
    }
    return shortest;
}