//
// Created by 张锐 on 2020/12/16.
//

/*
 * 归并排序迭代版
 * 算法分析
 *  归并排序算法的执行无非是对归并排序的迭代树进行后序遍历处理。
 *  内部节点的处理在子节点处理完成之后执行
 *      子节点各自有序后才会执行当前节点的 merge 算法。
 *
 * 算法思路: 考察非递归版本的后序遍历如何实现
 *  图/树的遍历依赖于：
 *      1. 选择策略：处于某个节点时，对后续的节点执行什么样子的选择
 *      2. 数据结构：需要借助一些数据结构来帮助确认当前的访问位置信息 (堆栈/颜色...)
 * 利用堆栈
 *  1. 从当前节点沿最左侧路径深入，直到最左侧节点： 对于每个节点，将当前节点入栈，若右子树存在，则将右子树节点入栈，若左子树存在，则将左子树节点入栈。
 *  2. 执行出栈，访问当前元素
 *      1. 出栈节点为跟节点，算法终止
 *      2. 出栈节点是否为左子节点
 *          a. Y：从步骤2开始执行
 *          b. N：从步骤1开始执行
 *
 * 设置节点的选择策略
 *  考察后序遍历情况下元素直接后继的选择情况
 *      1. 当前节点的右兄弟节点
 *      2. 当前节点的父节点
 *
 *  算法思路
 *      1. 从当前节点沿最左侧路径深入，直到最左侧节点
 *      2. 访问当前节点
 *      3. 将当前节点替换为其直接后继节点：若节点的后继节点为其父节点时，设置回溯标志位为true，为右侧兄弟节点时，设置回溯标志位为false；
 *          1. 若当前节点为null，算法终止
 *          2. 考察节点的回溯标志
 *              1. true: 从步骤2开始执行
 *              2. false: 从步骤1开始执行
 */

#include <utility>


/** 不使用堆栈， 模仿树结构后续遍历实现 */

struct MergeNode {
    std::pair<size_t, size_t> border;
    MergeNode *lc;
    MergeNode *rc;
    MergeNode *parent;
    MergeNode(size_t lo, size_t hi, MergeNode* p = nullptr, MergeNode* l = nullptr, MergeNode* r = nullptr):border(std::make_pair(lo,hi)),parent(p),lc(l),rc(r) {}
};
// 至少包含两个元素才具有拆分的意义
static bool canSplit(MergeNode* node) {
    return node->border.second - node->border.first >= 2;
}
// 拆分
static void split(MergeNode* node) {
    if (node->lc)   // 已拆分过则不再继续执行
        return;
    size_t mid = (node->border.first + node->border.second) >> 1;
    node->lc = new MergeNode(node->border.first, mid, node);
    node->rc = new MergeNode(mid, node->border.second, node);
}
static void release(MergeNode* node) {
    if (!node)
        return;
    if (node->lc) release(node->lc);
    if (node->rc) release(node->rc);
    delete node;
}

// todo 同 merge.cpp 中的merge算法
template<typename T>
void merge(T* input, size_t lo, size_t mid, size_t hi) {
    int ls = mid - lo, rs = hi - mid;
    T* L = new T[ls];
    for (int i = 0; i < ls; ++i)
        L[i] = input[lo+i];
    T* R = input+mid;
    for (int j = lo, p = 0, q = 0; p < ls || q < rs; ++j) {
        // 当 R 元素移除完成或者当前 L首元素存在且不大于 R 首元素时，挪动当前元素
        if ( q >= rs || (p < ls && L[p] <= R[q]) )
            input[j] = L[p++];
        else
            input[j] = R[q++];
    }
    delete[] L;
}

MergeNode* rightBrother(MergeNode* p) {
    if (p->parent && p->parent->lc == p)
        return p->parent->rc;
    return nullptr;
}

template<typename T>
void mergeSortIter(T input[], size_t size) {
    MergeNode* root = new MergeNode(0, size); bool backtrace = false;
    MergeNode* p = root;
    while (true) {
        if (!backtrace && canSplit(p)) {
            split(p); p = p->lc;
        } else {
            // 非叶节点进行合并， 叶节点直接返回
            if (p->lc) {
                merge(input, p->lc->border.first, p->lc->border.second, p->rc->border.second);
            }
            MergeNode* b= rightBrother(p);
            if (b) {
                p = b; backtrace = false;
            } else {
                p = p->parent; backtrace = true;
            }
        }
        if (!p) break;
    }
}
