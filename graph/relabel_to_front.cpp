//
// Created by 47302 on 2020/12/25.
//

/*
 * 最大流：前置重贴标签算法
 *  许可边/许可网络
 *  邻接链表：u.current/u.next-neighbor/u.N.head
 */

#include "init_graph_flow.h"

// 节点链表
typedef struct FlowNode {
    size_t index;
    struct FlowNode* next;
    FlowNode(size_t i, FlowNode* n = nullptr): index(i), next(n) {}
} *FlowNodePointer;


// 释放节点
template<typename T>
void GraphAlgorithm::discharge(Graph<T> *graph, Graph<T> *rng, size_t u) {
    size_t v = rng->firstNbr(u);
    while (graph->excess(u) > 0) {
        if (v < 0) {
            relabel(graph, rng, u);
            v = rng->firstNbr(u);
        } else if (graph->height(u) != graph->height(v) + 1) {
            push(graph, rng, u, v);
            delete rng; rng = remnantNetworks(graph);
        } else {
            v = rng->nextNbr(u, v);
        }
    }
}

template<typename T>
std::vector<typename GraphAlgorithm::Edge> GraphAlgorithm::relabelToFront(Graph<T> *graph, size_t s, size_t t) {
    GraphNode<T>* rng = remnantNetworks(graph);
    FlowNodePointer head = new FlowNode(0, nullptr), p = head;
    for (int i = 1; i < graph->vSize(); ++i) {
        if (i == s || i == t) continue;
        p->next = new FlowNode(i);
    }
    p = head;
    while (p) {
        // 释放节点u
        size_t oldHeight = graph->height(p->index);
        // 重贴标签需要将其移动到列表的开头
        if (graph->height(p->index) > oldHeight) {
            p->next = head->next;
        }
        p = p->next;
    }
    return statisticalFlow(graph);
}