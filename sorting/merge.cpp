//
// Created by 张锐 on 2020/12/9.
//

/**
归并排序：
    输入：给定的有限输入序列 A。序列A中元素支持`比较`操作
    输出：序列A的一个排列，{a1, a2, a3 ... an-1} 满足单调非减
基本策略：分治求解
算法思路：
 分治策略：
    1。分：等分(尽量)输入序列A为A1， A2
    2。治：排序A1， A2
    3。合：由业已有序的 A1，A2 合并得出 A
 合并策略：从分利用待合并子序列的有序性质
    1. 待合并子序列 A1， A2。 |A1| = n, |A2| = m
    2. A1[n] = 无穷大; A2[m] = 无穷大；
    3. 迭代m+n次，不断从A1与A2的首元素中拿出较小元素并追加到输出序列中
伪码实现：
    mergeSort(A, lo, hi):               // A[lo, hi)
        if (lo == hi-1) return A[lo];   // 基本情况 A[lo, lo+1)
        mid = (lo + hi) >> 1;
        A1 = mergeSort(A, lo, mid);     // 递归情况： A[lo, mid)
        A2 = mergeSort(A, mid, hi);     // 递归情况： A[mid, hi)
        return merge(A, lo, mid, hi);   // 合并返回

    merge(A, lo, mid, hi):
        copy A[lo, mid) to A1; copy A[mid, hi) to A2;
        append 无穷大 in A1[|A1|], A2[|A2|];
        int p = q = 0;
        for i=lo to hi:
            if (A1[p] <= A2[q])
                A[i] = A1[p++];
            else
                A[i] = A2[q++];
算法分析：
   归并算法的递归方程：
        T(n) = 2T(n/2) + \Thata(n);  (n > 1);
        T(n) = \Thata(1);            (n = 1);
   算法自上而下进行问题的递归分解直至基本情况(输入序列只含有一个元素，则该序列业已有序)。在自下而上的对有序子序列执行merge，故从递归树中任意球节点返回时，返回序列部分业已有序。 递归完成时整个序列有序
   递归树对归并算法进行分析：
                                O(n)
                       O(n/2)           O(n/2)
                 O(n/4)   O(n/4)  O(n/4)     O(n/4)
                 |          |       |           |
                 |          |       |           |
             O(1) O(1) O(1) O(1) O(1) O(1) O(1) O(1) O(1)
        子问题规模以 （1/2）^h 进行缩小， 子问题数量以 2^h进行递增。 h为递归树树高。 故整树高 H = logn; 叶节点数量：2^log_2n = n;
        上述递归树中，每层的复杂度为 O(n)， 故总复杂度为 T(n) = O(nlogn);
    主定理方程进行分析：
       f(n) = O(n);  叶节点复杂度 = n^(log_b{a}) = n^(log_2{2}) = O(n);
       故 T(n) = O(nlogn);

复杂度：\Theta(nlogn)
空间占用：\Theta(n)
稳定性： 稳定; (merge算法稳定则mergeSort稳定)
*/

#include "merge_subroutine.cpp"
#include "merge_iter.cpp"
#include "merge_iter_by_tree.cpp"

template<typename T>
void mergeSort(T* input, size_t lo, size_t hi) {
    if (hi - lo < 2) return;
    size_t mid = (lo + hi) >> 1;
    mergeSort(input, lo, mid);
    mergeSort(input, mid, hi);
    merge(input, lo, mid, hi);
}

template<typename T>
void mergeSort(T* input, size_t s) {
    mergeSort(input, 0, s);
}
