//
// Created by 张锐 on 2020/12/24.
//

#ifndef ALGORITHM_INIT_GRAPH_MATRIX_H
#define ALGORITHM_INIT_GRAPH_MATRIX_H

/*
 * 初始化最短路径矩阵
 */

#include <climits>

// 当前图的空矩阵,任意节点设置为不可达：W[i][j] = INT_MAX
template<typename T>
static inline int **initEmptyMatrix(Graph<T> *&graph) {
    int **W = nullptr;
    W = new int *[graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        W[i] = new int[graph->vSize()];
        for (int j = 0; j < graph->vSize(); ++j) {
            W[i][j] = INT_MAX;
        }
    }
    return W;
}

// 获取当前图的权重矩阵:
//  W[i][j] = graph->weight(i,j); (graph->exists(i, j))
//          = INT_MAX; (!graph->exists(i, j))
//          = 0; (i == j)
template<typename T>
static inline int **initWeightMatrix(Graph<T> *&graph) {
    int **W = nullptr;
    W = new int *[graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        W[i] = new int[graph->vSize()];
        for (int j = 0; j < graph->vSize(); ++j) {
            W[i][j] = i == j ? 0 : (graph->exists(i, j) ? graph->weight(i, j) : INT_MAX);
        }
    }
    return W;
}

// 获取图的布尔矩阵
// matrix[i][j] = true; (i=j || graph->exists(i, j))
//              = false; (其他)
template<typename T>
static inline bool **initBoolMatrix(Graph<T> *&graph) {
    bool **matrix = nullptr;
    matrix = new bool *[graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        matrix[i] = new bool[graph->vSize()];
        for (int j = 0; j < graph->vSize(); ++j) {
            matrix[i][j] = i == j ? true : (graph->exists(i, j) ? true : false);
        }
    }
    return matrix;
}

// 获取图的流信息：matrix[i][j] = 0;
template<typename T>
static inline int **initFlowMatrix(Graph<T> *&graph) {
    int **matrix = nullptr;
    matrix = new int *[graph->vSize()];
    for (int i = 0; i < graph->vSize(); ++i) {
        matrix[i] = new int[graph->vSize()];
        for (int j = 0; j < graph->vSize(); ++j) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

// 销毁由图graph所创建的矩阵
template<typename T>
static inline void destructGraphMatrix(Graph<T> *&graph, int **M) {
    for (int i = 0; i < graph->vSize(); ++i) {
        delete[] M[i];
    }
    delete M;
}

#endif //ALGORITHM_INIT_GRAPH_MATRIX_H
