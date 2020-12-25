//
// Created by 张锐 on 2020/12/23.
//

#ifndef ALGORITHM_ADJ_GRAPH_H
#define ALGORITHM_ADJ_GRAPH_H

#include "graph.h"

//边表节点
struct EdgeNode: public GraphEdge {
    size_t pos;
    EdgeNode* next;
    EdgeNode(size_t p, int w, EdgeNode* n = nullptr):GraphEdge(w), pos(p), next(n) {}
};

//定义顶点表节点
template <class Tv>
struct AdjNode: public GraphNode<Tv> {
    AdjNode(const Tv&e, EdgeNode* f = nullptr):GraphNode<Tv>(e), firstEdge(f) {}
    EdgeNode* firstEdge;
    ~AdjNode() {
        EdgeNode* en = firstEdge;
        while (en) { auto p = en->next; delete en; en = p; }
    }
};

/**
 * 领接表实现
 *
 * @tparam Tv
 */
template <class Tv>
class AdjGraph:public Graph<Tv> {
public:
    typedef AdjNode<Tv>* NodePointer;
    AdjGraph()=default;
    AdjGraph(Tv const arr[], const size_t& size) {
        this->nodeNum = size;
        for (int i = 0; i < size; ++i)
            nodes[i] = new AdjNode<Tv>(arr[i], nullptr);
    }
    ~AdjGraph() {
        for (int i = 0; i < MAX_NODE_NUM; ++i)
            if (nodes[i])
                delete nodes[i];
    }
    
    /**顶点*/
    bool exists(size_t u) const { assert(u < this->nodeNum); return nodes[u]; }
    //插入顶点，返回编号
    size_t insert(Tv const& e) {
        assert(this->nodeNum < MAX_NODE_NUM);
        nodes[this->nodeNum] = new AdjNode<Tv>(e, nullptr);
        return this->nodeNum++;
    }
    //删除顶点及其关联边，返回该顶点信息
    Tv remove(size_t u) {
        throw std::logic_error("维持节点在 0 ~ nodeNums 内的有效性，暂时注释");
        assert(u < this->nodeNum && nodes[u]);
        auto node = nodes[u]; nodes[u] = nullptr;
        Tv e = node->data;
        auto p = node->firstEdge;
        size_t nums = 0;
        while (p) {
            ++nums;
            --nodes[p->pos]->inDegree;
            p = p->next;
        }
        delete node; --this->nodeNum; this->edgeNum-=nums;
        return e;
    }
    //顶点u的数据（该顶点的确存在）
    Tv& vertex(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->data;
    }
    //顶点u的入度（该顶点的确存在）
    size_t inDegree(size_t u) const {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->inDegree;
    }
    //顶点u的出度（该顶点的确存在）
    size_t outDegree(size_t u) const {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->outDegree;
    }
    //顶点u的首个邻接顶点
    int firstNbr(size_t u) const {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->firstEdge ? nodes[u]->firstEdge->pos : -1;
    }
    //顶点u的（相对于顶点v的）下一邻接顶点
    int nextNbr(size_t u, size_t v) const {
        assert(u < this->nodeNum && nodes[u]);
        auto p = getEdge(u, v);
        return p && p->next ? p->next->pos : -1;
    }
    //顶点u的状态
    NodeStatus& status(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->status;
    }
    //顶点u的时间标签dTime
    size_t& dTime(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->dTime;
    }
    //顶点u的时间标签fTime
    size_t& fTime(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->fTime;
    }
    //顶点u在遍历树中的父亲
    int& parent(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->parent;
    }
    //顶点u在遍历树中的优先级数
    int& priority(size_t u) {
        assert(u < this->nodeNum && nodes[u]);
        return nodes[u]->priority;
    }
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    //边(u, v)是否存在
    bool exists(size_t u, size_t v) const {
        assert(u < this->nodeNum && nodes[u] && v < this->nodeNum);
        auto p = getEdge(u, v);
        return p;
    }
    //在顶点u和u之间插入权重为w的边e（头插法）
    void insert(size_t u, size_t v, int w) {
        assert(this->edgeNum < MAX_EDGE_NUM && u < this->nodeNum && nodes[u] && v < this->nodeNum && nodes[v]);
        ++this->edgeNum; ++nodes[u]->outDegree; ++nodes[v]->inDegree;
        nodes[u]->firstEdge = new EdgeNode(v, w, nodes[u]->firstEdge);
    }
    //删除顶点u和u之间的边e
    void remove(size_t u, size_t v) {
        assert(u < this->nodeNum && nodes[u] && v < this->nodeNum && nodes[v]);
        auto p = nodes[u]->firstEdge;
        EdgeNode* q = nullptr;
        while (p && p->pos != v) {
            q = p; p = p->next;
        }
        if (!p)
            return;
        (q ? q->next : nodes[u]->firstEdge) = p->next;
        delete p;
        --this->edgeNum; --nodes[u]->outDegree; --nodes[v]->inDegree;
    }

    //边(v, u)的类型
    EdgeType& type(size_t u, size_t v) {
        assert(u < this->nodeNum && nodes[u] && v < this->nodeNum && nodes[v]);
        auto p = getEdge(u, v);
        assert(p);
        return p->type;
    }
    //边(u, v)的权重
    int& weight(size_t u, size_t v) {
        assert(u < this->nodeNum && nodes[u] && v < this->nodeNum && nodes[v]);
        auto p = getEdge(u, v);
        assert(p);
        return p->weight;
    }

    /**图的转置**/
    virtual Graph<Tv>* reverse() {
        AdjGraph<Tv>* newGraph = new AdjGraph<Tv>();
        newGraph->nodeNum = this->nodeNum;
        for (int i = 0; i < this->nodeNum; ++i) {
            newGraph->nodes[i] = new AdjNode<Tv>(vertex(i), nullptr);
        }
        for (int i = 0; i < this->nodeNum; ++i) {
            auto p = nodes[i]->firstEdge;
            while (p) {
                newGraph->insert(p->pos, i, p->weight);
                p = p->next;
            }
        }
        return newGraph;
    }

private:
    // 返回边节点(u, v)
    EdgeNode* getEdge(size_t u, size_t v) const {
        auto p = nodes[u]->firstEdge;
        while (p && p->pos != v) p = p->next;
        return p;
    }
    NodePointer nodes[MAX_NODE_NUM];      // 顶点集
};

#endif //ALGORITHM_ADJ_GRAPH_H
