//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：Dijkstra算法
 */

#include "relax.h"

template<typename T>
std::map<size_t, size_t> GraphAlgorithm::dijkstra(Graph<T> *graph, size_t s) {
    graph->reset();
    // 做n次贪心选择，确定所有节点的最短距离
    graph->priority(s) = 0;
    for (int i = 0; i < graph->vSize(); ++i) {
        graph->status(s) = visited;
        // 更新最短链接
        for (int v = graph->firstNbr(s); -1 < v; v = graph->nextNbr(s, v)) {
            if (graph->status(v) == undiscovered) {
                relax(graph, s, v);
            }
        }
        // 贪心选择：获取当前问题最段距离
        for (int u = 0, min = INT_MAX; u < MAX_NODE_NUM; ++u) {
            if (graph->exists(u) && graph->status(u) == undiscovered && graph->priority(u) < min) {
                min = graph->priority(u);
                s = u;
            }
        }
    }

    // 统计最短路径
    std::map<size_t, size_t> shortest;
    for (int u = 0; u < MAX_NODE_NUM; ++u) {
        if (graph->exists(u))
            shortest[u] = graph->priority(u);
    }
    return shortest;
}
