//
// Created by 47302 on 2020/12/25.
//

/*
 * 有向图的传递闭包
 */

#include "init_graph_matrix.h"

template<typename T>
bool **GraphAlgorithm::transitiveClosure(Graph<T> *graph) {
    bool** reach = initBoolMatrix(graph);
    for (int k = 0; k < graph->vSize(); ++k) {
        for (int i = 0; i < graph->vSize(); ++i) {
            for (int j = 0; j < graph->vSize(); ++j) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }
    return reach;
}