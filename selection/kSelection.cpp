//
// Created by 47302 on 2020/12/5.
//

/*
 k选取问题：在任意一组可比较大小的元素中，如何找出由小到大次序为k者？
 中位数选取：中位数查找问题既是选取问题的特例
=====================================================================================
 蛮力算法1：使前 k 大/小的元素就位即可;
    for i = 0 to k:  ( [0, k] )
        selectMin(A);
复杂度： O(min(k, n-k) * n);  k位于两侧时性能较好， 取中间元素时为O(n^2)的复杂度
=====================================================================================
 蛮力算法2：将元素序列进行排序，输出A[k]即可;
    sort(A);
    return A[k];
 复杂度：O(nlogn)
=====================================================================================
  基于优先级队列的选取：蛮力算法的效率之所以无法令人满意，可以解释为：“一组元素中第k大的元素”所包含的信息量，远远少于经过全排序后得到的整个有序序列。花费足以全排序的计算成本，却仅得到了少量的局部信息，未免得不偿失。
    1. 将输入序列组成一个大小为 |A| 的小顶堆，则第k次 delMax() 为期望输出
        O(n) + k∙O(logn) = O(n + klogn)
    2. 组织一个大小为k的大顶堆 G，将剩余元素不断插入堆G中并删除一个堆顶元素
        O(k) + 2(n-k)∙O(logk) = O(k + 2(n - k)logk)
    3. 将输入序列组成一个大小为 k 的大顶堆(H) 和 |A|-k的小顶堆(G)，不断执行堆顶元素交换，直至H堆顶小于G堆顶
        O(n - k) + O(k) + min(k, n - k)∙2∙(O(logk + log(n - k)))
=====================================================================================
 基于快速划分的k选取： 减治策略，任选一轴点进行划分， 考查轴点秩r与k的相对大小进行处理。
 每经过一步主迭代，都会构造出一个轴点A[i]，然后lo和hi将彼此靠拢，查找范围将收缩至A[i]的某一侧。当轴点的秩i恰为k时，算法随即终止。如此，A[k]即是待查找的目标元素。
    if k == r:
        return r;
    else k < r:
        [lo, r) 中进行 k选取
    else k > r:
        [r+1, hi) 中进行 k-r 选取
 复杂度： 尽管内循环仅需O(hi - lo + 1)时间，但很遗憾，外循环的次数却无法有效控制。与快速排序算法一样，最坏情况下外循环需执行O(n)次，总体运行时间为O(n^2)。
=====================================================================================
 O(n) 复杂度的k选取策略：
 算法描述：
    1. 仿照希尔排序将输入元素序列拆分为多个包含少量元素的序列。 对个拆分序列取中位数m1,m2,m3,m4,...mj 并组成中位数序列L，取L的中位数M; O(cn)
    2. 对输入序列 A 中的元素进行遍历，获取小于(L)，大于(G)，等于(E) A[M] 的元素; O(cn)
    3. 基于 |L|, |G|, |E| 与 k 之间的关系进行处理：
        a. 若 k < |L|: 在 L中递归执行 k选取; T(3/4n)
        b. 若 k < |G|: 在 G 中递归执行  k - |L| - |E|选取; T(3/4n)
        c. 若 |L| < k && k < |L| + |E|: 中为数为等于E中的任一元素; O(1)
 复杂度：
    T(n) = cn + T(n/Q) + T(3n/4)，c为常数, Q为分割元素的元素个数
    假设取取 Q = 5，则有
        T(n) = cn + T(n/5) + T(3n/4) = O(20cn) = O(n)
    3/4n的由来： 各子序列的中位数序列的中位数M， 必定存在至少 1/4n 的元素不大于/不小于 A[M]； 故而递归求解时问题至多为3/4n;
 */


#include <cassert>
#include <algorithm>
#include <vector>
#include "../priorityqueue/complete_binary_heap.h"


template<typename V>
V kSelect1(V arr[], int s, int k) {
    assert( 0 <= k && k < s );
    for (int i = 0; i < k+1; ++i)
        for (int j = s-1; j > 0; --j)
            if (arr[j] < arr[j-1])
                std::swap(arr[j-1], arr[j]);
    return arr[k];
}

template<typename V>
V quickKSelect(V arr[], int s, int k) {
    assert( 0 <= k && k < s );
    for (int lo = 0, hi = s-1; lo < hi;) {
        // 选取轴点进行划分
        V pivot = arr[lo]; int i = lo, j = hi;
        while ( i < j ) {
            // 此处的划分策略算法存在问题：对同相同的输入序列 eg：【5 5 5 5 5 5 5 5】 会存在长度为0， n-1的不公平划分； （勤于扩展，懒于交换）
            while ( (i < j) && (pivot <= arr[j]) ) --j; arr[i] = arr[j];
            while ( (i < j) && (arr[i] <= pivot) ) ++i; arr[j] = arr[i];
        }
        arr[i] = pivot;
        if ( k <= i ) hi = i - 1;
        if ( i <= k ) lo = i + 1;
    }
    return arr[k];
}

template<typename V>
V efficientKSelect(V arr[], int s, int k) {
    assert( 0 <= k && k < s );
    const int q = 5;
    for (int i = 0; i < s; ++i) {
    }
}

template<typename V>
V priorityKSelect1(V arr[], int s, int k) {
    assert( 0 <= k && k < s );
    CompleteBinaryHeap<V> heap(arr, k+1);
    for (int i = k+1; i < s; ++i) {
        heap.insert(arr[i]);
        heap.delMax();
    }
    return heap.getMax();
}





