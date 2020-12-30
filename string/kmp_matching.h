//
// Created by 张锐 on 2020/12/29.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_KMP_MATCHING_H
#define INTRODUCTION_TO_ALGORITHMS_KMP_MATCHING_H

/*
 * KMP字符串匹配算法
 *
 * 蛮力算法为何效率如此之差：回溯, 每次失败的比对都会回溯之前所有成功的比对。
 *
 * 能否从成功的比对中吸收 `经验`.
 *
 * 对于给定输入字符T,|T|=n; P,|P|=m; m <= n;, i指向当前串对齐位置，j指向当前P[j]执行比较的位置。
 * 当P[j] != T[i+j] 时：我们可以知道 P[1,j) = T[i,i+j);
 *  平凡若j=0时，则++i，j不变即可
 *  j > 0 时， 假设存在一个元素P[l]，令P[l]重新与T[i+j]执行下一次比较时： P[l] = T[i+j] != P[j];
 *      1. -1 < l < m 时: 0～m中存在前缀位为以[m]结尾的子串的后缀的字符串
 *          P[0, l] = P[m-l, m]; 此时相当于指针i前后j-l位。
 *      2. l < 0 时：0～m中不存在元素可与T[i+j]进行匹配，则直接跳过当前元素,
 *          令 P[0] 与 T[i+j]进行匹配, 文本串向后移动j位
 *
 * 如何获取在P[j](0 <= j < m)处匹配失败时的 l值：
 *  l = max length of prefix(P) is suffix(P[0, j])
 *
 * 归纳假设：假设当前已经知道在 m-2 处匹配失败时的 next[m-2] = l。
 *  若 P[m-1] = l+1; (P[m-1]=P[next[m-2]+1])
 *            = next[next[m-2]] + 1; (while m1)
 */

#include <vector>
#include <string>
#include <algorithm>

// 构造next表
int *buildNext(const std::string &pattern) {
    int *next = new int[pattern.size()];
    int j = 0, t = next[0] = -1;
    while (j < pattern.size() - 1) {
        if (0 > t || pattern[j] == pattern[t]) {
            next[++j] = ++t;
        } else {
            j = next[t];
        }
    }
    return next;
}

// 执行算法
int kmp_matching(const std::string &text, const std::string &pattern) {
    if (text.size() < pattern.size() || pattern.size() == 0)
        return -1;
    int *next = buildNext(pattern);
    int i = 0, j = 0, n = text.size(), m = pattern.size();
    while (i < n && j < m) {
        if (0 > j || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    delete[]next;
    return j < pattern.size() ? -1 : i - j;
}

#endif //INTRODUCTION_TO_ALGORITHMS_KMP_MATCHING_H
