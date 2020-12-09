//
// Created by 张锐 on 2020/12/9.
//

#include "largest_subarray.h"
#include <random>

// 蛮力
template<typename T>
result<T> maxSubArray1(T input[], size_t s) {
    T max = INT_MIN; size_t lp = 0, rp = 0;
    for (int i = 0; i < s; ++i) {
        T tmp = input[i];
        for (int j = i+1; j < s; ++j) {
            tmp+=input[j];
            if (max < tmp) {
                max = tmp;
                lp = i; rp = j;
            }
        }
    }
    return result<T>(lp, rp, max);
}

// 分治
template<typename T>
result<T> static maxCrossMidSubArray(T input[], size_t lo, size_t mid, size_t hi) {
    T lSum = 0, lPos = mid;
    T rSum = 0, rPos = mid;
    T tmp;
    for (int i = mid-1, tmp = input[i]; i > -1; --i, tmp+=input[i]) {
        if (lSum < tmp) {
            lSum = tmp; lPos = i;
        }
    }
    for (int i = mid+1, tmp = input[i]; i < hi; ++i, tmp+=input[i]) {
        if (rSum < tmp) {
            rSum = tmp; rPos = i;
        }
    }
    return result<T>(lPos, rPos, lSum+rSum+input[mid]);
}

template<typename T>
result<T> biggest(result<T> L, result<T> R, result<T> C) {
    result<T> tmp = C.sum > R.sum ? C : R;
    return tmp.sum > L.sum ? tmp : L;
}

template<typename T>
result<T> static maxSubArray2(T input[], size_t lo, size_t hi) {
    if (hi-lo < 2)
        return result<T>(lo, hi, input[lo]);
    size_t mid = (lo+hi) >> 1;
    result<T> L = maxSubArray2(input, lo, mid-1);
    result<T> R = maxSubArray2(input, mid+1, hi);
    result<T> C = maxCrossMidSubArray(input, lo, mid, hi);
    return biggest(L, R, C);
}

// 迭代
template<typename T>
result<T> maxSubArray3(T input[], size_t s) {
    size_t lPos = 0, rPos = 0, lPerfix = 0;     // [lPos, rPos)标示 input[0, i) 的最大连续子数组； lPrefix: 标示 input[0, i) 以i结尾的最大后缀的左端位置
    T max = INT_MIN, prefix = 0;                // max：数组input[0,i)的最大连续子数组和；prefix: A[0,i)的最大后缀和(小于0时丢弃);
    for (int i = 0; i < s; ++i) {
        // A[0, i)的最大连续子数组 < 以i结尾的连续子数组
        if (max < prefix+input[i]) {
            max = prefix+input[i];
            lPos = lPerfix; rPos = i;
        }
        // 更新input[0, i+1) 的最大后缀和
        if (prefix+input[i] < 0) {
            prefix = 0; lPerfix = i+1;
        } else
            prefix+=+input[i];
    }
    return result<T>(lPos, rPos, max);
}

// 动态规划
template<typename T>
result<T> maxSubArray4(T input[], size_t s) {
    T dp0 = input[0], max = dp0, dp1;   // dp0, dp1: 以前后指针来替换制表，标示dp[i-1],dp[i]; max：最大子序列和
    for (int i = 1; i < s; ++i) {
        dp1 = std::max( input[i], input[i]+dp0 );
        max = std::max( max, dp1 );
        dp0 = dp1;
    }
    return result<T>(0, 0, max);  // todo 此处未求最大子序列的位置
}

template<typename T>
result<T> maxSubArray(T input[], size_t s) {
    assert( s > 0 );
    int i = rand() % 4;
    switch(i) {
        case 0: return maxSubArray1(input, s); break;
        case 1: return maxSubArray2(input, 0, s); break;
        case 2: return maxSubArray2(input, 0, s); break;
        default: return maxSubArray4(input, s); break;
    }
}
