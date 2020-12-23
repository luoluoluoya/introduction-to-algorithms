//
// Created by 张锐 on 2020/12/23.
//

#ifndef ALGORITHM_MATRIX_GRAPH_H
#define ALGORITHM_MATRIX_GRAPH_H

#include "graph.h"

/**
 * 领接矩阵实现
 *
 * @tparam Tv
 */
template<typename Tv>
class MatrixGraph: public Graph<Tv> {
public:
    typedef GraphNode<Tv>* NodePointer;
    typedef GraphEdge* EdgePointer;

    MatrixGraph() { init(); }
    MatrixGraph(Tv const input[], size_t size) {
        this->nodeNum = size;
        init();
        for (int i; i < size; ++i)
            nodes[i] = new GraphNode<Tv>(input[i]);
    }
    ~MatrixGraph() {
        for (int i; i < MAX_NODE_NUM; ++i) {
            for (int j; j < MAX_NODE_NUM; ++j) {
                if (edges[i][j]) delete edges[i][j];
            }
            if (nodes[i]) delete nodes[i];
        }
    }

    /**顶点*/
    //插入顶点，返回编号
    size_t insert(Tv const & e) {
        assert(this->nodeNum < MAX_NODE_NUM);
        this->nodeNum++;
        for (int i = 0; i < MAX_NODE_NUM; ++i) {
            if (!nodes[i]) {
                nodes[i] = new GraphNode<Tv>(e);
                return i;
            }
        }
    }
    //删除顶点及其关联边，返回该顶点信息
    Tv remove(size_t u) {
        assert(nodes[u]);
        size_t delEdges = 0;
        for (int i = 0; i < MAX_NODE_NUM; ++i) {
            if (edges[u][i]) {
                ++delEdges;
                delete edges[u][i];
                --nodes[i]->inDegree;
            }
            if (edges[i][u]) {
                ++delEdges;
                delete edges[i][u];
                --nodes[i]->outDegree;
            }
        }
        Tv e = nodes[u]->data; delete nodes[u]; nodes[u] = nullptr;
        --this->nodeNum; this->edgeNum-=delEdges;
        return e;
    }
    //顶点u的数据（该顶点的确存在）
    Tv &vertex(size_t u) { assert(nodes[u]); return nodes[u]->data; }
    //顶点u的入度（该顶点的确存在）
    size_t inDegree(size_t u) const { assert(nodes[u]); return nodes[u]->inDegree; }
    //顶点u的出度（该顶点的确存在）
    size_t outDegree(size_t u) const { assert(nodes[u]); return nodes[u]->outDegree; }
    //顶点u的首个邻接顶点
    int firstNbr(size_t u) const {
        return nextNbr(u, MAX_NODE_NUM);
    }
    //顶点u的（相对于顶点v的）下一邻接顶点
    int nextNbr(size_t u, size_t v) const {
        assert(nodes[u] && nodes[v]);
        int i = v-1;
        while (i >= 0 && !edges[u][i]) i--;
        return i;
    }
    //顶点u的状态
    NodeStatus &status(size_t u) { assert(nodes[u]); return nodes[u]->status; }
    //顶点u的时间标签dTime
    size_t &dTime(size_t u) { assert(nodes[u]); return nodes[u]->dTime; }
    //顶点u的时间标签fTime
    size_t &fTime(size_t u) { assert(nodes[u]); return nodes[u]->fTime; }
    //顶点u在遍历树中的父亲
    int &parent(size_t u) { assert(nodes[u]); return nodes[u]->parent; }
    //顶点u在遍历树中的优先级数
    int &priority(size_t u) { assert(nodes[u]); return nodes[u]->priority; }
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    //删除顶点u和u之间的边e，返回该边信息
    void remove(size_t u, size_t v) {
        assert(edges[u][v]);
        delete edges[u][v]; edges[u][v] = nullptr;
        --this->edgeNum; --nodes[u]->outDegree; --nodes[v]->inDegree;
    }
    //边(u,v)的类型
    EdgeType &type(size_t u, size_t v) { assert(edges[u][v]); return edges[u][v]->type; }
    //边(u,v)的权重
    int &weight(size_t u, size_t v) { assert(edges[u][v]); return edges[u][v]->weight; }
    //边(u,v)是否存在
    bool exists(size_t u, size_t v) const { return edges[u][v]; }
    //在顶点u和u之间插入权重为w的边e
    void insert(size_t u, size_t v, int w) {
        edges[u][v] = new GraphEdge(w);
        ++this->edgeNum; ++nodes[u]->outDegree; ++nodes[v]->inDegree;
    }
private:
    void init () {
        for (int i; i < MAX_NODE_NUM; ++i) {
            for (int j = 0; j < MAX_NODE_NUM; ++j)
                edges[i][j] = nullptr;
            nodes[i] = nullptr;
        }
    }
    NodePointer nodes[MAX_NODE_NUM];
    EdgePointer edges[MAX_NODE_NUM][MAX_NODE_NUM];
};

#endif //ALGORITHM_MATRIX_GRAPH_H
