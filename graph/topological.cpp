//
// Created by 张锐 on 2020/12/24.
//

/*
 * 基于dfs的拓扑排序算法
 *  排序算法
 *  环路检测
 */


template<typename T>
std::vector<size_t> GraphAlgorithm::topologicalSort(Graph<T> *graph) {
    if (hasLoop(graph))
        throw std::logic_error("the current graph exists in a loop");
    std::vector<size_t> topological;
    size_t nodes[graph->vSize()];
    for (int i = 0, k = 0; i < MAX_NODE_NUM; ++i) {
        if (graph->exists(i))
            topological.push_back(i);
    }
    std::sort(topological.begin(), topological.end(), [&graph](size_t a, size_t b) { return graph->fTime(a) > graph->fTime(b); });
    return topological;
}
