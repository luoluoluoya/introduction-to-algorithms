//
// Created by 张锐 on 2020/12/23.
//

#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H

//#define MAX_NODE_NUM 50
//#define MAX_EDGE_NUM 50*49

#define MAX_NODE_NUM 6
#define MAX_EDGE_NUM 6*5

#include <climits>
#include <iostream>
#include <cstddef>
#include <cassert>
#include "node_and_edge.h"

/**后续实现都是使用静态表实现**/

/**
 * 图结构抽象接口
 *
 * @tparam Tv
 */
template<typename Tv>
class Graph {
public:
    Graph():nodeNum(0),edgeNum(0) {}

    friend class GraphAlgorithm;
    int vSize() const { return nodeNum; }
    int eSize() const { return edgeNum; }

    /**顶点*/
    virtual bool exists(size_t u) const = 0;        //节点u是否存在
    virtual size_t insert(Tv const &) = 0;          //插入顶点，返回编号
    virtual Tv remove(size_t) = 0;                  //删除顶点及其关联边，返回该顶点信息
    virtual Tv &vertex(size_t) = 0;                 //顶点u的数据（该顶点的确存在）
    virtual size_t inDegree(size_t) const = 0;      //顶点u的入度（该顶点的确存在）
    virtual size_t outDegree(size_t) const = 0;     //顶点u的出度（该顶点的确存在）
    virtual int firstNbr(size_t) const = 0;         //顶点u的首个邻接顶点
    virtual int nextNbr(size_t, size_t) const = 0;  //顶点u的（相对于顶点j的）下一邻接顶点
    virtual NodeStatus &status(size_t) = 0;         //顶点u的状态
    virtual size_t &dTime(size_t) = 0;              //顶点u的时间标签dTime
    virtual size_t &fTime(size_t) = 0;              //顶点u的时间标签fTime
    virtual int &parent(size_t) = 0;                //顶点u在遍历树中的父亲
    virtual int &priority(size_t) = 0;              //顶点u在遍历树中的优先级数
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    virtual void remove(size_t, size_t) = 0;        //删除顶点u和u之间的边e，返回该边信息
    virtual EdgeType &type(size_t u, size_t v) = 0; //边(u,v)的类型
    virtual int &weight(size_t u, size_t v) = 0;    //边(u,v)的权重
    virtual bool exists(size_t u, size_t v) const = 0;      //边(u,v)是否存在
    virtual void insert(size_t u, size_t v, int w) = 0;     //在顶点u和u之间插入权重为w的边e

    /**图的转置**/
    virtual Graph<Tv>* reverse() = 0;

    /**打印图的详细信息**/
    void print() {
        printf("=======================================Print Graph Info==========================================\n");
        for (int i = 0; i < MAX_NODE_NUM; ++i) {
            if (exists(i)) {
                printf("Node: %d, inDegree: %d, outDegree: %d, parent: %d, dTime: %d, fTime: %d, priority: %d \n", i, inDegree(i), outDegree(i), parent(i), dTime(i), fTime(i), priority(i));
                if (outDegree(i)) {
                    for (int j = 0; j < MAX_NODE_NUM; ++j) {
                        if (exists(i, j)) {
                            const char *etype = type(i, j) == undetermined ? "undetermined" : ( type(i, j) == tree ? "tree" : ( type(i, j) == froward ? "froward" : ( type(i, j) == backword ? "backword" : "cross" ) ) );
                            printf("\t Edge(%d,%d) weight: %d, type: %s \n", i, j, weight(i, j), etype);
                        }
                    }
                }
            }
        }
        printf("=======================================Print End==========================================\n");
    }
protected:
    size_t nodeNum, edgeNum;    //顶点总数, 边总数
    void reset() {
        for (int i = 0; i < MAX_NODE_NUM; i++) {
            // 顶点
            status(i) = undiscovered;
            dTime(i) = fTime(i) = 0;
            parent(i) = -1;
            priority(i) = INT_MAX;
            // 边
            for (int j = 0; j < MAX_NODE_NUM; ++j) {
                if (exists(i, j)) type(i, j) = undetermined;
            }
        }
    }
};

//#include_next "./graph_algorithm.h"

#endif //ALGORITHM_GRAPH_H
