//
// Created by 张锐 on 2020/12/30.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_SUNDAY_MATCHING_H
#define INTRODUCTION_TO_ALGORITHMS_SUNDAY_MATCHING_H

/*
 * sunday 字符串匹配算法
 */

#include <string>
#include <map>

int sunday_matching(const std::string &text, const std::string &pattern) {
    int n = text.size(), m = pattern.size();
    std::map<char, size_t> local;
    for (int i = 0; i < m; ++i) {
        local[pattern[i]] = i;
    }
    int i = 0;
    while (i <= n - m) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) j++;
        if (j == m) {
            return i;
        } else {
            i += i + m == n ? 1 : local.find(text[i + m]) == local.end() ? m + 1 : m - local[text[i + m]];
        }
    }
    return -1;
}

#endif //INTRODUCTION_TO_ALGORITHMS_SUNDAY_MATCHING_H
