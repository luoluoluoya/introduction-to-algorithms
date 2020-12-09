//
// Created by 47302 on 2020/12/5.
//


/*
冒泡排序算法：
    外层迭代 + 扫描交换（最大元素就位）
    起泡排序算法的不变性和单调性可分别概括为：输入规模未n的元素序列，经过k趟扫描交换之后，最大的前k个元素必然就位；经过k趟扫描交换之后，待求解问题的有效规模将缩减至n - k。

算法框架：
    bubbleSort:
        for i=1 to n:
            bubble(0, n);
    bubble:
        for i=1 to n:
            if A[i-1] > A[i]:
                swap(A[i-1], A[i]);
算法优化：
    当不存在逆序对时终止算法执行；（一次bubble中为发生交换）
    避免对输入元素中业已有序的部分进行重复比较
 */


#include <algorithm>

template<typename V>
void bubbleSort1(V arr[], int s) {
    for (int i = 0; i < s; ++i)
        for (int j = 1; j < s; ++j)
            if (arr[j-1] > arr[j])
                std::swap(arr[j-1], arr[j]);
}

template<typename V>
void bubbleSort2(V arr[], int s) {
    bool sorted = false;
    while ( (sorted = !sorted) )
        for (int i = 1; i < s; ++i)
            if (arr[i-1] > arr[i]) {
                sorted = false;
                std::swap(arr[i-1], arr[i]);
            }
}

template<typename V>
void bubbleSort3(V arr[], int s) {
    bool sorted = true;
    do {
        for (int i = 1; i < s; ++i)
            if (arr[i-1] > arr[i]) {
                sorted = false;
                std::swap(arr[i-1], arr[i]);
            }
    } while ( (sorted = !sorted) && --s);
}

template<typename V>
void bubbleSort4(V arr[], int s) {
    for (bool sorted = false; (sorted = !sorted); --s) {
        for (int i = 1; i < s; ++i)
            if (arr[i-1] > arr[i]) {
                sorted = false;
                std::swap(arr[i-1], arr[i]);
            }
    }
}

//自左向右逐对检查当前范围A[0, m)内的各相邻元素. 一旦A[i-1]与A[i]逆序，则交换之，并更新待排序区间的长度
template<typename V>
void bubbleSort5(V arr[], int s) {
    for (int m; 1 < s; s = m) {
        for (int i = m = 1; i < s; i++) {
            if (arr[i-1] > arr[i]) {
                std::swap (arr[i-1], arr[i]);
                m = i;
            }
        }
    }
}

template<typename V>
void bubbleSort(V arr[], int s) {
    int r = rand() % 4;
    switch (r) {
        case 0: bubbleSort1(arr, s);
        case 1: bubbleSort2(arr, s);
        case 2: bubbleSort3(arr, s);
        case 3: bubbleSort4(arr, s);
        default: bubbleSort5(arr, s);
    }
}