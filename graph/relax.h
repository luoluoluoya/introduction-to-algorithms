//
// Created by 张锐 on 2020/12/24.
//

#ifndef ALGORITHM_RELAX_H
#define ALGORITHM_RELAX_H

/*
 * 松弛
 */

//使用u对v进行松弛操作
template<typename T>
static inline void relax(Graph<T>* &graph, size_t u, size_t v) {
    auto p = graph->priority(v);
    if (graph->priority(u) != INT_MAX && graph->priority(v) > graph->priority(u) + graph->weight(u, v)) {       // 节点u不可达时不执行+操作（溢出）
        graph->parent(v) = u;
        graph->priority(v) = graph->priority(u) + graph->weight(u, v);
    }
    printf("edge(%d,%d):%d; u.d:%d, v.d:%d, v.d.update:%d\n", u, v, graph->weight(u, v), graph->priority(u), p, graph->priority(v));
}

#endif //ALGORITHM_RELAX_H
