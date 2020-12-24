//
// Created by 张锐 on 2020/12/24.
//

/*
 * 有向图是否存在环路
 */

template<typename T>
bool GraphAlgorithm::hasLoop(Graph<T> *graph) {
    dfs(graph);
    for (int i = 0; i < MAX_NODE_NUM; ++i) {
        for (int j = 0; j < MAX_NODE_NUM; ++j) {
            if (graph->exists(i, j) && graph->type(i, j) == backword)
                return true;
        }
    }
    return false;
}
