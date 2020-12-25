//
// Created by 47302 on 2020/12/23.
//

/*
 * 强连通分量
 */

#include "graph_algorithm.h"
#include <algorithm>
#include <stack>

//dfs
template <typename T> static void statistical(Graph<T> *graph, size_t s, std::vector<size_t>& vec) {
    graph->status(s) = visited;
    for (int v = graph->firstNbr(s); v > -1; v = graph->nextNbr(s, v)) {
        if (graph->status(v) == undiscovered) {
            graph->parent(v)  = s;
            statistical<T>(graph, v, vec);
        }
    }
    vec.push_back(s);
}

template<typename T>
std::vector<std::vector<size_t>> GraphAlgorithm::bcc(Graph<T> *graph) {
    Graph<T>* gt = graph->reverse();
    // 获取定点集的DFS访问fTime倒序
    dfs(graph);
    size_t nodes[graph->vSize()];
    for (int i = 0, k = 0; i < graph->vSize(); ++i) {
        if (graph->exists(i))
            nodes[k++] = i;
    }
    std::sort(nodes, nodes+graph->vSize(), [&graph](size_t a, size_t b) { return graph->fTime(a) > graph->fTime(b); });

    // 依据倒序对Gt执行DFS
    std::vector<std::vector<size_t>> relations;
    for (int j = 0; j < graph->vSize(); ++j) {
        std::vector<size_t> vec;
        statistical(gt, nodes[j], vec);
        relations.push_back(vec);
    }
    return relations;
    /*std::for_each(relations.cbegin(), relations.cend(), [](const std::vector<size_t> vec) {
        std::cout << "current connected: " << std::endl;
        std::for_each(vec.cbegin(), vec.cend(), [](const size_t pos) { std::cout << pos << " "; });
        std::cout << std::endl;
    });*/
}
