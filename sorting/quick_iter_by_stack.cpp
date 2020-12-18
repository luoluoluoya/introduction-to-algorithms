//
// Created by 张锐 on 2020/12/18.
//

/*
 * 快速排序迭代算法
 * 算法伪代码
 * typedef pair<size_t, size_t> Border;
 *  quickSortIter(A, size)
 *      Border border = {0, size};
 *      Stack s[]; s.push(border);
 *      while (!s.empty)
 *          border = s.pop;
 *          p = partition(A, lo, hi);
 *          if (hi-p > 2)
 *              s.push({p+1, hi});
 *          if (p-lo > 1)
 *              s.push({lo, p});
 */

#include <stack>
#include <utility>

typedef std::pair<size_t,size_t> Border;


template<typename T>
void quickSortIter(T A[], const size_t& size) {
    size_t lo = 0, hi = size;
    Border border = {lo, hi}; std::stack<Border> S; S.push(border);
    while (!S.empty()) {
        border = S.top(); S.pop();
        size_t p = partition(A, border.first, border.second);
        if (border.second - p > 2)
            S.push({p+1, border.second});
        if (p - border.first > 1)
            S.push({border.first, p});
        //printf("border[%d, %d):%d(%d), lc[%d, %d), rc[%d, %d)\n", border.first, border.second, p, A[p], border.first, p, p+1, border.second);
    }
}
