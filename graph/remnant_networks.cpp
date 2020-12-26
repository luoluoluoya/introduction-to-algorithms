//
// Created by 47302 on 2020/12/25.
//

/*
 * 残存网络
 */

template<typename T>
Graph<T> *GraphAlgorithm::remnantNetworks(Graph<T> *graph) {
    Graph<T> *graph1 = new AdjGraph<T>;
    for (int u = 0; u < graph->vSize(); ++u) {
        graph1->insert(u);
    }
    for (int u = 0; u < graph->vSize(); ++u) {
        for (int v = graph->firstNbr(u); -1 < v; v = graph->nextNbr(u, v)) {
            int rem = graph->weight(u, v) - graph->flow(u, v);
            if (rem > 0)
                graph1->insert(u, v, rem);
            if (graph->flow(u, v) > 0)
                graph1->insert(v, u, graph->flow(u, v));
        }
    }
    return graph1;
}
