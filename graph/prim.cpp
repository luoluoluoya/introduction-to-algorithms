//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最小支撑树Prim算法
 */

template<typename T>
std::vector<typename GraphAlgorithm::Edge> GraphAlgorithm::prim(Graph<T> *graph) {
    // 选择一个节点开始
    size_t s = 0;
    while (s < MAX_NODE_NUM && !graph->exists(s)) s++;
    assert(s < MAX_NODE_NUM);

    // 执行prim算法
    std::vector<Edge> mst;
    graph->reset(); graph->priority(s) = 0;
    for (int i = 1; i < graph->vSize(); ++i) {
        graph->status(s) = visited;
        for (int v = graph->firstNbr(s); -1 < v ; v = graph->nextNbr(s, v)) {
            if (graph->status(v) == undetermined && graph->priority(v) > graph->priority(s) + graph->weight(s, v)) {
                graph->parent(v)  = s;
                graph->type(s, v)  = tree;
                graph->priority(v) = graph->priority(s) + graph->weight(s, v);
            }
        }
        for (int u = 0, min = INT_MAX; u < MAX_NODE_NUM; ++u) {
            if (graph->exists(u) && undiscovered == graph->status(u) && graph->priority(u) < min) {
                min = graph->priority(u);
                s = u;
            }
        }
        mst.push_back( {{graph->parent(s), s}, graph->weight(graph->parent(s), s)} );
    }
    if (mst.size() != graph->vSize()-1)
        throw std::logic_error("The current diagram is not connected");
    //for_each(mst.begin(), mst.end(), [&graph](Edge edge){ printf("MST Tree Edge:(%d, %d),weight=%d\n", edge.first.first, edge.first.second, edge.second); });
    return mst;
}
