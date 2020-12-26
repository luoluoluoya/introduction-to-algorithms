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
    struct FlowNode *succ;
    struct FlowNode *pre;

    FlowNode(size_t i, FlowNode *p = nullptr, FlowNode *s = nullptr) : index(i), pre(p), succ(s) {}
} *FlowNodePointer;

// 释放节点
template<typename T>
void GraphAlgorithm::discharge(Graph<T> *graph, Graph<T> *rng, size_t u) {
    int v = rng->firstNbr(u);
    while (graph->excess(u) > 0) {
        if (v < 0) {
            relabel(graph, rng, u);
            v = rng->firstNbr(u);
        } else if (graph->height(u) == graph->height(v) + 1) {
            push(graph, rng, u, v);
            delete rng;
            rng = remnantNetworks(graph);
            v = rng->nextNbr(u, v);
        } else {
            v = rng->nextNbr(u, v);
        }
    }
}

template<typename T>
std::vector<typename GraphAlgorithm::Edge> GraphAlgorithm::relabelToFront(Graph<T> *graph, size_t s, size_t t) {
    initPushRelabel(graph, s);
    Graph<T> *rng = remnantNetworks(graph);
    FlowNodePointer head = nullptr, p = head, q = head;
    for (int i = 0; i < graph->vSize(); ++i) {
        if (i == s || i == t) continue;
        if (!head)
            p = head = new FlowNode(i, nullptr, nullptr);
        else
            p = (p->succ = new FlowNode(i, p, p->succ));
    }
    p = head;
    while (p) {
        // 释放节点u
        size_t oldHeight = graph->height(p->index);
        discharge(graph, rng, p->index);
        // 重贴标签需要将其移动到列表的开头
        if (graph->height(p->index) > oldHeight) {
            if (p != head) {
                p->pre->succ = p->succ;
                p->succ->pre = p->pre;
                p->pre = nullptr;
                p->succ = head->succ;
            }
        }
        p = p->succ;
    }
    return statisticalFlow(graph);
}