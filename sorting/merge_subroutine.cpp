//
// Created by 张锐 on 2020/12/17.
//

#include <cstddef>

/** Merge 子程序 **/

/*
 * 归并流程：
 * Merge(A[lo, mid), A[mid, hi))
 *      A1[mid-lo+1] = A[lo,mid);    A2[hi-mid+1] = A[mid, hi);      // 拷贝元素至 size+1 的新容器中
 *      A1[A1.size]  = 无穷大;        A2[A2.size]  = 无穷大;           // 未元素填充无穷大
 *      n=m=0;
 *      for i=0 to hi-mid:
 *          A[i++] = A1[n] <= A2[m] ? A[i++]=A1[n++] : A2[m++];
 */

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
