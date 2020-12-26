//
// Created by 47302 on 2020/12/25.
//

/*
 * 最大流：推送重贴标签算法
 */

#include "init_graph_flow.h"

template<typename T>
std::vector<typename GraphAlgorithm::Edge>  GraphAlgorithm::pushRelabel(Graph<T> *graph, size_t s, size_t t) {
    initPushRelabel(graph, s);
    Graph<T>* rng = remnantNetworks(graph);
    while(true){
        // 寻找第一个存在超额流的节点
        int u;
        for (u = 0; u < graph->vSize(); ++u) { if (u == s || u == t) continue; if(graph->excess(u) > 0) break; }
        if (u == graph->vSize())
            break;
        // 执行推送/重贴标签操作
        bool pushed = false;
        for (int v = rng->firstNbr(u); -1 < v; v = rng->nextNbr(u, v)) {
            if ((pushed = push(graph, rng, u, v)))
                break;
        }
        if (!pushed)
            relabel(graph, rng, u);
        delete rng; rng = remnantNetworks(graph);
        graph->print();
    }
    return statisticalFlow(graph);
}