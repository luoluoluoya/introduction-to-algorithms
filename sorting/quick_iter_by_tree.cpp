//
// Created by 张锐 on 2020/12/18.
//

/*
 * 模拟树的前序遍历来实现快速排序算法
 * 树的前序遍历
 *  1. 一直访问并深入左侧路径直至最左侧节点处。
 *  2. 跳转到右侧节点
 *      1. 若右侧节点不存在，则跳转到存在右侧节点的祖先节点的有节点处，并执行1
 * 伪代码实现
 * struct QuickNode
 *      border [lo,hi);
 *      visited = false;
 *      QuickNode* parent, lc, rc;
 *      QuickNode(ls, hs, p=nullptr, l=nullptr, r=nullptr):lo(ls),hi(hs),parent(p),lc(l),rc(r) { }
 * quickByTree(A, size):
 *      root = Quick(0, size), pos = root;
 *      while (pos)
 *          p = partition(A, pos.border.first, pos.border.second);
 *          if (p - pos.border.first > 1)
 *              pos->lc = QuickNode(pos.border.first, p, pos);
 *          if (pos.border.second - p > 2)
 *              pos->rc = QuickNode(p+1, pos.border.second, pos);
 *          if (pos->lc)
 *              pos = pos->lc;
 *          else if (pos->rc)
 *              pos = pos->rc;
 *          else
 *              while (pos->parent && (!pos->rc || pos->rc->visited))
 *                  pos = pos->parent;
 *              if (!pos)
 *                  break;
 */

#include <utility>

struct QuickNode {
    typedef QuickNode* NodePointer;
    std::pair<size_t, size_t> border;
    NodePointer parent, lc, rc;
    bool visited = false;
    QuickNode(size_t lb, size_t hb, NodePointer p=nullptr, NodePointer l=nullptr, NodePointer r=nullptr):border({lb,hb}),parent(p),lc(l),rc(r) {}
};

static void release(QuickNode* node) {
    if (!node)
        return;
    if (node->lc) release(node->lc);
    if (node->rc) release(node->rc);
    delete node;
}

template<typename T>
void quickSortByTree(T A[], const size_t& size) {
    QuickNode::NodePointer root = new QuickNode(0, size), p = root;
    while (p) {
        p->visited = true;
        size_t n = partition(A, p->border.first, p->border.second);
        if (n - p->border.first > 1)
            p->lc = new QuickNode(p->border.first, n, p);
        if (p->border.second - n > 2)
            p->rc = new QuickNode(n+1, p->border.second, p);
        if (p->lc)
            p = p->lc;
        else if(p->rc)
            p = p->rc;
        else {
            while ((p = p->parent) && (!p->rc || p->rc->visited));
            if (p) p = p->rc;
        }
        if (!p) break;
    }
    release(root);
}
