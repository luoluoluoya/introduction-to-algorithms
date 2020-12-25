//
// Created by 47302 on 2020/12/25.
//

#include "graph_algorithm.h"

template<typename T>
void GraphAlgorithm::push(Graph<T> *graph, size_t u, size_t v, std::vector<size_t> &excess, const std::vector<size_t> &height) {
    if (height[u] != height[v]+1)
        return;
}