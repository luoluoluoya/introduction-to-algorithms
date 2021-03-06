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
class MatrixGraph : public Graph<Tv> {
public:
    typedef GraphNode<Tv> *NodePointer;
    typedef GraphEdge *EdgePointer;

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
    bool exists(size_t u) const {
        assert(u < MAX_NODE_NUM);
        return nodes[u];
    }

    //插入顶点，返回编号
    size_t insert(Tv const &e) {
        assert(this->nodeNum < MAX_NODE_NUM);
        nodes[this->nodeNum] = new GraphNode<Tv>(e);
        return this->nodeNum++;
    }

    //删除顶点及其关联边，返回该顶点信息
    Tv remove(size_t u) {
        throw std::logic_error("维持节点在 0 ~ nodeNums 内的有效性，暂时注释");
        assert(u < this->nodeNum && nodes[u]);
        size_t delEdges = 0;
        for (int i = 0; i < this->nodeNum; ++i) {
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
        Tv e = nodes[u]->data;
        delete nodes[u];
        nodes[u] = nullptr;
        --this->nodeNum;
        this->edgeNum -= delEdges;
        return e;
    }

    //顶点u的数据（该顶点的确存在）
    Tv &vertex(size_t u) {
        assert(nodes[u]);
        return nodes[u]->data;
    }

    //顶点u的入度（该顶点的确存在）
    size_t inDegree(size_t u) const {
        assert(nodes[u]);
        return nodes[u]->inDegree;
    }

    //顶点u的出度（该顶点的确存在）
    size_t outDegree(size_t u) const {
        assert(nodes[u]);
        return nodes[u]->outDegree;
    }

    //顶点u的首个邻接顶点
    int firstNbr(size_t u) const {
        return nextNbr(u, this->nodeNum);
    }

    //顶点u的（相对于顶点v的）下一邻接顶点
    int nextNbr(size_t u, size_t v) const {
        assert(nodes[u]);
        int i = v - 1;
        while (i >= 0 && !edges[u][i]) i--;
        return i;
    }

    //顶点u的状态
    NodeStatus &status(size_t u) {
        assert(nodes[u]);
        return nodes[u]->status;
    }

    //顶点u的时间标签dTime
    size_t &dTime(size_t u) {
        assert(nodes[u]);
        return nodes[u]->dTime;
    }

    //顶点u的时间标签fTime
    size_t &fTime(size_t u) {
        assert(nodes[u]);
        return nodes[u]->fTime;
    }

    //顶点u在遍历树中的父亲
    int &parent(size_t u) {
        assert(nodes[u]);
        return nodes[u]->parent;
    }

    //顶点u在遍历树中的优先级数
    int &priority(size_t u) {
        assert(nodes[u]);
        return nodes[u]->priority;
    }

    //顶点u在最大流中的高度
    size_t &height(size_t u) {
        assert(nodes[u]);
        return nodes[u]->h;
    }

    //顶点u在最大流中的超额流
    int &excess(size_t u) {
        assert(nodes[u]);
        return nodes[u]->e;
    }
    /**边：无向边均统一转化为方向互逆的一对有向边**/

    //边(u,v)上的流
    size_t &flow(size_t u, size_t v) {
        assert(edges[u][v]);
        return edges[u][v]->flow;
    }

    //删除顶点u和u之间的边e，返回该边信息
    void remove(size_t u, size_t v) {
        assert(edges[u][v]);
        delete edges[u][v];
        edges[u][v] = nullptr;
        --this->edgeNum;
        --nodes[u]->outDegree;
        --nodes[v]->inDegree;
    }

    //边(u,v)的类型
    EdgeType &type(size_t u, size_t v) {
        assert(edges[u][v]);
        return edges[u][v]->type;
    }

    //边(u,v)的权重
    int &weight(size_t u, size_t v) {
        assert(edges[u][v]);
        return edges[u][v]->weight;
    }

    //边(u,v)是否存在
    bool exists(size_t u, size_t v) const { return edges[u][v]; }

    //在顶点u和u之间插入权重为w的边e
    void insert(size_t u, size_t v, int w) {
        edges[u][v] = new GraphEdge(w);
        ++this->edgeNum;
        ++nodes[u]->outDegree;
        ++nodes[v]->inDegree;
    }

    /**图的转置**/
    virtual Graph<Tv> *reverse() {
        MatrixGraph<Tv> *newGraph = new MatrixGraph<Tv>();
        newGraph->nodeNum = this->nodeNum;
        for (int u = 0; u < this->nodeNum; ++u)
            newGraph->nodes[u] = new GraphNode<Tv>(vertex(u));
        for (int u = 0; u < this->nodeNum; ++u) {
            for (int v = firstNbr(u); -1 < v; v = nextNbr(u, v)) {
                newGraph->insert(u, v, weight(u, v));
            }
        }
        return newGraph;
    }

private:
    void init() {
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
