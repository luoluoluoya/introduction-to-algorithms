//
// Created by 张锐 on 2020/12/23.
//

#include <queue>
#include "graph_algorithm.h"

/*
 * 广度优先搜索算法
 */

template <typename T> static void BFS(Graph<T> *&graph, size_t s, size_t &clock) {
    std::queue<size_t> Q; Q.push(s);
    while (!Q.empty()) {
        size_t u = Q.front(); Q.pop();
        //printf("Visited Node %d\n", u);
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            if (graph->status(v) == undiscovered) {
                graph->type(u, v) = tree;
                graph->parent(v)  = u;
                Q.push(v);
                //printf("Tree Edge: (%d, %d)\n", u, v);
            } else {
                //printf("Cross Edge: (%d, %d)\n", u, v);
                graph->type(u, v) = cross;
            }
        }
        graph->status(u) = visited;
    }
}

template<typename T>
void GraphAlgorithm::bfs(Graph<T> *graph, size_t s) {
    graph->reset();
    size_t clock = 0; size_t v = s;
    do {
        if (graph->status(s) == undiscovered) {
            BFS<T>(graph, s, clock);
        }
    } while ( s != (v = ++v%graph->vSize()) );
}
