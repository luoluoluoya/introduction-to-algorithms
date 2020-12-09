//
// Created by 张锐 on 2020/12/9.
//

#ifndef ALGORITHM_LARGEST_SUBARRAY_H
#define ALGORITHM_LARGEST_SUBARRAY_H

#include <cassert>

template<typename T>
struct result {
    size_t lp, rp; T sum;
    result(size_t l, size_t r, T s):lp(l), rp(r), sum(s) {}
};

template<typename T>
result<T> maxSubArray(T input[], size_t s);

#endif //ALGORITHM_LARGEST_SUBARRAY_H
