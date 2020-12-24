//
// Created by 张锐 on 2020/12/23.
//

#ifndef ALGORITHM_GRAPH_ALGORITHM_H
#define ALGORITHM_GRAPH_ALGORITHM_H

#include <vector>
#include <cstddef>
#include <exception>
#include <map>
#include "graph.h"
#include <utility>
#include <list>

/**
 * 图算法
 */
class GraphAlgorithm {
public:
    typedef std::pair<std::pair<size_t, size_t>, int> Edge;

    /**图的遍历**/
    //广度优先搜索算法
    template<typename T> void bfs(Graph<T> *graph, size_t s);
    //深度优先搜索算法
    template<typename T> void dfs(Graph<T> *graph);
    //优先级搜索框架
    template<typename T, typename PU> void pfs(Graph<T> *graph, PU pu, size_t s);

    /**强联通分量**/
    //获取强联通分量
    template<typename T> std::vector<std::vector<size_t>> bcc(Graph<T> *graph);

    /**拓扑排序问题**/
    //基于dfs的拓扑排序算法
    template<typename T> std::vector<size_t> topological(Graph<T> *graph);
    //基于InDegree的拓扑排序算法
    template<typename T> std::vector<size_t> topologicalByDegree(Graph<T> *graph);

    /**环路检测**/
    template<typename T> bool hasLoop(Graph<T> *graph);

    /**最小支撑树问题**/
    //最小支撑树Prim算法
    template<typename T> std::vector<Edge> prim(Graph<T> *graph);
    //最小支撑树Kruskal算法
    template<typename T> std::vector<Edge> kruskal(Graph<T> *graph);

    /**最短路径问题(所有最短路径的最短距离使用priority属性指代)**/
    //最短路径：BellmanFord算法
    template<typename T> std::map<size_t, size_t> bellmanFord(Graph<T> *graph, size_t s);
    //最短路径：有向无环图的单源最短路径问题
    template<typename T> void dagShortestPath(Graph<T> *dag);
    //最短路径：Dijkstra算法
    template<typename T> void dijkstra(Graph<T> *graph);
    //最短路径：Floyd-Warshall算法
    template<typename T> void floydWarshal(Graph<T> *graph);
    //最短路径：用于稀疏图的johnson算法
    template<typename T> void johnson(Graph<T> *graph);

    /**最大流问题**/
    //最大流：Edmonds-Karp算法
    template<typename T> void edmondsKarp(Graph<T> *graph, size_t s, size_t t);
    //最大流：Ford-Fulkerson算法
    template<typename T> void fordFulkerson(Graph<T> *graph, size_t s, size_t t);
    //最大流：前置重贴标签算法
    template<typename T> void relabelToFront(Graph<T> *graph, size_t s, size_t t);
    //最大流：推送重贴标签算法
    template<typename T> void pushRelabel(Graph<T> *graph, size_t s, size_t t);
    /**二分图匹配**/
    //二分图的最大匹配：匈牙利算法
    template<typename T> void hungary(Graph<T> *graph);
    //二分图的最佳完美匹配：KM算法
    template<typename T> void KM(Graph<T> *graph);

protected:
    //深度优先搜索算法
    template<typename T> void DFS(Graph<T> *graph, size_t s, size_t& clock);

private:
};

#endif //ALGORITHM_GRAPH_ALGORITHM_H
