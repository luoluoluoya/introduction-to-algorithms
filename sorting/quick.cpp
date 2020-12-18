//
// Created by 张锐 on 2020/12/15.
//

/*
快速排序
    快速排序基于分治的求解策略对输入序列进行原地求解。
分治求解策略
分解：对输入序列 A={a1,a2,...an}, 将其分解为两个子序列 A1={a`1, a`2, .. a`k-1}, A2={a`K+1, a`K+2, .. a`n} 使得对子序列A1中任意元素i,均不大于ak，对子序列A2中任意元素j,均不小于a。
解决：对子问题递归的调用快速排序进行求解，直至到达问题规模为一的基本情况时，递归回溯。
合并：不需要合并操作。递归回溯时，分解而得的子问题和当前元素业已就位
伪代码实现
 伪码中所有位置都以左闭右开区间进行界定。
    partition(A, i, j):     // 对输入序列A的 [i,j)子序列进行划分
        x = A[j-1];
        p = x-1;            // 指向当前小等于 x 的元素位置。 x+1 指向第一个大于 x 的元素位置; (划分小等于x和大于x的元素边界)
        for q = i to j:     // 界定大于x和为知的元素部分
            if (A[q] <= x)
                p = p+1;
                swap(A[x], A[p]);
   quickSort(A, i, j):          // 对输入序列A的 [i,j)子序列进行排序
        if (j-i < 2)
            return;             // 基础情况：只含有一个元素
        r = partition(A, i, j); // 递归情况：问题划分
        quickSort(A,i, r-1);
        quickSort(A,r+1, j);
    quickSort(A):
        quickSort(A, 0, A.size);
    // 对于上诉伪码所描述的算法，当元素业已有序时，算法退化为O(n^2)复杂度的情况
复杂度分析：快速排序的性能取决于`轴点`对输入序列的划分情况
    最坏情况：原问题被分解为规模为n-1,0的两个子问题，即将问题分解为n-1和0的两个子问题（eg：对业已就绪的元素以首位节点进行轴点选取和序列划分）。此时，快速排序的递归式为 T(n)=T(n-1)+cn; 求解递归式，T(n)=\Theta(n^2);
    最好情况：问题被分解为规模缩减一半的两个子问题。递归式为T(n)=2T(n/2)+cn（与归并排序相同）;依据主定理方程， T(n)=\Theta(nlgn);
轴点划分对性能的影响：根据上述最好和最坏划分情况下的复杂度的巨大差距，我们知道轴点的选取对快速排序的性能影响重大。当元素以等比例进行划分时，不管比例如何，快速排序的复杂度渐进的等于 \Theta(nlgn) 的。
     1:9 的划分为例：
     对划分的递归树进行分析，满二叉子树的最大高度为 O(log_{10}n) (取决于问题规模缩减最快的子问题路径 1/10)的。树的最大高度为 O(log_{10/9}n) (取决于问题规模缩减最慢的子问题路径 9/10) 的。复杂度为：
     T(n) = max(O(nlog_{10}n), O(nlog_{10/9}n)) = O(nlog_{10/9}n) = O(nlgn);
快速排序与BST的构建：
    快速排序中每一次轴点的选取过程等同于在 BST 中进行一次元素的插入操作， 快排中轴点的选取的序列给定了 BST 中元素插入的序列。
快速排序与归并排序：
    归并排序需要额外的空间用以合并元素，而快排为原地排序的
    归并排序中处理问题的复杂度主要来自于子问题和子问题的合并，而快排中处理问题的复杂度主要来自于分解和处理子问题
快速排序的轴点选择策略：
    轴点以随机选择策略进行选取
基于随机轴点选择策略的伪代码实现
    random-partition(A,i,j):
        swap(A[j-1], A[i+random() % (j-i)]);
        partition(A,i,j);
   random-quickSort(A, i, j):
        if (j-i < 2)
            return;
        r = random-partition(A, i, j);
        random-quickSort(A,i, r-1);
        random-quickSort(A,r+1, j);
    random-quickSort(A):
        random-quickSort(A, 0, A.size);
*/

#include <algorithm>
#include <random>
#include <random>
#include "partition.cpp"

template<typename T>
void quickSort(T A[], size_t b, size_t e) {
    if (e - b < 2)
        return;
    size_t r = partition(A, b, e);
    quickSort(A, b, r);
    quickSort(A, r + 1, e);
}

template<typename T>
void random_quickSort(T A[], size_t b, size_t e) {
    if (e - b < 2)
        return;
    size_t r = random_partition(A, b, e);
    random_quickSort(A, b, r);
    random_quickSort(A, r + 1, e);
}
