//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最短路径：有向无环图的单源最短路径问题
 */

#include "relax.h"

template<typename T>
std::map<size_t, size_t> GraphAlgorithm::DAGShortestPath(Graph<T> *DAG, size_t s) {
    // 获取顶点集的DFS访问fTime倒序
    dfs(DAG);
    std::vector<size_t> nodes;
    for (int i = 0; i < MAX_NODE_NUM; ++i) {
        if (DAG->exists(i))
            nodes.push_back(i);
    }

    // 核心算法，获取最短路径
    DAG->priority(s) = 0;
    std::sort(nodes.begin(), nodes.end(), [&DAG](size_t a, size_t b) { return DAG->fTime(a) > DAG->fTime(b); });
    for (int i = 0; i < nodes.size(); ++i) {
        for (int v = DAG->firstNbr(nodes[i]); -1 < v; v = DAG->nextNbr(nodes[i], v)) {
            relax(DAG, nodes[i], v);
        }
    }

    // 统计最短路径
    std::map<size_t, size_t> shortest;
    for (int u = 0; u < MAX_NODE_NUM; ++u) {
        if (DAG->exists(u))
            shortest[u] = DAG->priority(u);
    }
    return shortest;
}
