//
// Created by 张锐 on 2020/12/24.
//

/*
 * 最小支撑树Kruskal算法
 *  不相交集合的实现
 */


template<typename T>
std::vector<typename GraphAlgorithm::Edge> GraphAlgorithm::kruskal(Graph<T> *graph) {
    // n-1个连通分量
    std::vector<Edge> edges; std::vector<size_t> nodes;
    for (int i = 0; i < MAX_NODE_NUM; ++i) {
        if (graph->exists(i)) {
            graph->parent(i) = i;
            nodes.push_back(i);
            for (int j = graph->firstNbr(i); -1 < j ; j = graph->nextNbr(i, j)) {
                edges.push_back( {{i, j}, graph->weight(i, j)} );
            }
        }
    }
    std::vector<Edge> mst;
    // 排序边集。遍历所有边，寻找权重最小且合并两个连通分量的安全边
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.second < b.second; });
    for (auto edge: edges) {
        size_t f = graph->parent(edge.first.first), s = graph->parent(edge.first.second);
        if (f != s) {
            mst.push_back(edge);
            // 将第二个连通分量的所有定点合并到当前分量中
            std::for_each(nodes.begin(), nodes.end(), [&graph, f, s](size_t v) {
                if (graph->parent(v) == s)
                    graph->parent(v) = f;
            });
        }
    }
    //for_each(mst.begin(), mst.end(), [&graph](Edge edge){ printf("MST Tree Edge:(%d, %d),weight=%d\n", edge.first.first, edge.first.second, edge.second); });
    return mst;
}
