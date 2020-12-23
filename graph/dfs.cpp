//
// Created by 张锐 on 2020/12/23.
//

/*
 * 深度优先搜索算法
 */

template <typename T> static void DFS(Graph<T> *&graph, size_t s, size_t &clock) {
    graph->dTime(s)  = clock++;
    graph->status(s) = discovered;
    //printf("当前访问节点 %d, 开始访问时间：%d\n", s, graph->dTime(s));
    for (int v = graph->firstNbr(s); v > -1; v = graph->nextNbr(s, v)) {
        if (graph->status(v) == undiscovered) {
            //printf("引入树边: (%d, %d), 权重为：%d\n", s, v, graph->weight(s, v));
            graph->type(s, v) = tree;
            graph->parent(v)  = s;
            DFS<T>(graph, v, clock);
        } else if (graph->status(v) == discovered) {
            graph->type(s, v) = backword;
            //printf("引入后向边: (%d, %d), 权重为：%d\n", s, v, graph->weight(s, v));
        } else {
            graph->type(s, v) = ( graph->dTime(s) < graph->dTime(v) ? froward : cross );
            //graph->dTime(s) < graph->dTime(v) ? printf("引入前向边: (%d, %d), 权重为：%d\n", s, v, graph->weight(s, v)) : printf("引入跨边: (%d, %d), 权重为：%d\n", s, v, graph->weight(s, v));
        }
    }
    graph->fTime(s)  = clock++;
    graph->status(s) = visited;
    //printf("当前节点访问完成 %d, 结束访问时间：%d\n", s, graph->fTime(s));
}

template<typename T>
void GraphAlgorithm::dfs(Graph<T> *graph, size_t s) {
    graph->reset();
    size_t clock = 0; size_t v = s;
    do {
        if (graph->status(s) == undiscovered) {
            DFS<T>(graph, s, clock);
        }
    } while ( s != (v = ++v%graph->vSize()) );
}
