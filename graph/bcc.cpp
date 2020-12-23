//
// Created by 47302 on 2020/12/23.
//

/*
 * 强连通分量
 */

#include "graph_algorithm.h"
#include <algorithm>
#include <stack>

template <typename T> static void statistical(Graph<T> *graph, size_t s) {
    graph->status(s) = visited;
    printf("%d ", s);
    for (int v = graph->firstNbr(s); v > -1; v = graph->nextNbr(s, v)) {
        if (graph->status(v) == undiscovered) {
            graph->parent(v)  = s;
            statistical<T>(graph, v);
        }
    }
}

template<typename T>
void GraphAlgorithm::bcc(Graph<T> *graph, size_t s) {
    Graph<T>* gt = graph->reverse();
    dfs(graph, s);
    size_t nodes[graph->vSize()];
    for (int i = 0, k = 0; i < MAX_NODE_NUM; ++i) {
        if (graph->exists(i))
            nodes[k++] = i;
    }
    std::sort(nodes, nodes+graph->vSize(), [&graph](size_t a, size_t b) { return graph->fTime(a) > graph->fTime(b); });
    for (int j = 0; j < graph->vSize(); ++j) {
        printf("bcc start \n");
        statistical(gt, nodes[j]);
        printf("\nbcc end \n");
    }
}
