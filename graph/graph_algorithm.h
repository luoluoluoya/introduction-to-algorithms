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
    template<typename T>
    void bfs(Graph<T> *graph, size_t s);

    //深度优先搜索算法
    template<typename T>
    void dfs(Graph<T> *graph);

    //优先级搜索框架
    template<typename T, typename PU>
    void pfs(Graph<T> *graph, PU pu, size_t s);

    /**强联通分量**/
    //获取强联通分量
    template<typename T>
    std::vector<std::vector<size_t>> bcc(Graph<T> *graph);

    /**拓扑排序问题**/
    //基于dfs的拓扑排序算法
    template<typename T>
    std::vector<size_t> topological(Graph<T> *graph);

    //基于InDegree的拓扑排序算法
    template<typename T>
    std::vector<size_t> topologicalByDegree(Graph<T> *graph);

    /**环路检测**/
    template<typename T>
    bool hasLoop(Graph<T> *graph);

    /**最小支撑树问题**/
    //最小支撑树Prim算法
    template<typename T>
    std::vector<Edge> prim(Graph<T> *graph);

    //最小支撑树Kruskal算法
    template<typename T>
    std::vector<Edge> kruskal(Graph<T> *graph);

    /**最短路径问题(所有最短路径的最短距离使用priority属性指代)**/
    //单目的地 v 的最短路径
    //  求G的转置图并在其上执行单源最短路径
    //指定节点对(u,v)的最短路径
    //  求u的单源最短路径
    //单源最短路径：BellmanFord算法
    template<typename T>
    void bellmanFord(Graph<T> *graph, size_t s);

    //单源最短路径：有向无环图的单源最短路径问题
    template<typename T>
    void DAGShortestPath(Graph<T> *DAG, size_t s);

    //单源最短路径：Dijkstra算法(该算法要求图中不存在负权边)
    template<typename T>
    void dijkstra(Graph<T> *graph, size_t s);

    //单源最短路径：Dijkstra算法(该算法要求图中不存在负权边)
    //任意节点对最短路径：动态规划求解任意节点对的最短路径; (利用矩阵重平方技术对其进行优化)
    template<typename T>
    std::pair<int **, int **> shortestByDynamic(Graph<T> *graph);

    //任意节点对最短路径：利用重平方技术优化矩阵乘法
    template<typename T>
    int **shortestByGoodMatrix(Graph<T> *graph);

    //任意节点对最短路径：Floyd-Warshall算法
    template<typename T>
    std::pair<int **, int **> floydWarshall(Graph<T> *graph);

    //任意节点对最短路径：用于稀疏图的johnson算法
    template<typename T>
    std::pair<int **, int **> johnson(Graph<T> *graph);

    /**有向图的传递闭包**/
    template<typename T>
    bool **transitiveClosure(Graph<T> *graph);

    /**最大流问题**/
    //最大流：Edmonds-Karp算法
    template<typename T>
    int **edmondsKarp(Graph<T> *graph, size_t s, size_t t);

    //最大流：Ford-Fulkerson算法
    template<typename T>
    int **fordFulkerson(Graph<T> *graph, size_t s, size_t t);

    //最大流：推送重贴标签算法
    template<typename T>
    std::vector<Edge> pushRelabel(Graph<T> *graph, size_t s, size_t t);

    //最大流：前置重贴标签算法
    template<typename T>
    std::vector<Edge> relabelToFront(Graph<T> *graph, size_t s, size_t t);

    /**二分图匹配**/
    //二分图的最大匹配：匈牙利算法
    template<typename T>
    void hungary(Graph<T> *graph);

    //二分图的最佳完美匹配：KM算法
    template<typename T>
    void KM(Graph<T> *graph);

protected:
    //深度优先搜索算法
    template<typename T>
    void DFS(Graph<T> *graph, size_t s, size_t &clock);

    //残存网络
    template<typename T>
    Graph<T> *remnantNetworks(Graph<T> *graph, int **flow);

    //重贴标签
    template<typename T>
    void relabel(Graph<T> *graph, std::vector<size_t> &height);

    //推送
    template<typename T>
    void push(Graph<T> *graph, size_t u, size_t v, std::vector<size_t> &excess, const std::vector<size_t> &height);
};

#endif //ALGORITHM_GRAPH_ALGORITHM_H
