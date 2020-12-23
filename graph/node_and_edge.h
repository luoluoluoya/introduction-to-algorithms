//
// Created by 张锐 on 2020/12/21.
//

#ifndef ALGORITHM_NODE_AND_EDGE_H
#define ALGORITHM_NODE_AND_EDGE_H

#include <climits>
#include <cstddef>

enum NodeStatus {undiscovered, discovered, visited };
enum EdgeType { undetermined, tree, froward, backword, cross };

template<typename Tv>
struct GraphNode {
public:
    GraphNode(const Tv&e):data(e),status(undiscovered),dTime(0),fTime(0),inDegree(0),outDegree(0),parent(-1),priority(INT_MAX) {}
    Tv data;
    NodeStatus status;
    size_t dTime;
    size_t fTime;
    size_t inDegree;
    size_t outDegree;
    int parent;
    int priority;
};

struct GraphEdge {
public:
    GraphEdge(int w = 0):type(undetermined),weight(w) {}
    int weight;
    EdgeType type;
};

#endif //ALGORITHM_NODE_AND_EDGE_H
