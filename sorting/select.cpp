//
// Created by 张锐 on 2020/12/9.
//

/**
选择排序：
 基本策略：增量求解
 算法思路：
    划分数组为已排序的部分S和未排序的部分U。 不断在未排序的序列U中找到最大元素，然后将其存放到序列S的起始位置；以此类推，直到所有元素均排序完毕。
 伪码实现：
    selectSort(A):
        for i=n to 0:     // i 界定有序和无序部分; 初始化时：无序为 A[0, n), 有序为 A[n, n); 算法终止于：无序为 A[0, 0), 有序为 A[1, n)
            std::swap( A[i-1], A[ findMax(A, 0, i) ] );
    findMax(A, 0, i):
        max = A[i]; pos = i;
        while (--i)
            if (A[i] > max)
                max = A[i];
                pos = i;
 算法分析：
    算法总共迭代 n 次， 每次必定在无序序列中选中一个最大元素并使其就位。 n次之后，输入序列业已有序。 算法的复杂度呀取决于 findMax 函数的执行效率;
 复杂度：
    堆结构组织数据： T(findMax) = O(logn); T(n) = O(nlogn);
    vector,list： T(findMax) = O(n); T(n) = O(n^2);
 */

#include <algorithm>

// A[lo, hi) 中寻找最大值
template<typename T>
static int findMax(T input[], int lo, int hi) {
    int pos = hi-1; T max = input[pos];
    for (int i = pos-1; i >= lo; --i) {
        if (max < input[i]) {
            max = input[i];
            pos = i;
        }
    }
    return pos;
}

template<typename T>
void selectSort(T input[], int s) {
    for (int i = s; i > 0; --i) {
        int t = findMax(input, 0, i);
        std::swap( input[i-1], input[ t ] );
    }
}
