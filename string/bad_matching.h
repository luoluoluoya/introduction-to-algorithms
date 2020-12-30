//
// Created by 张锐 on 2020/12/29.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_BAD_MATCHING_H
#define INTRODUCTION_TO_ALGORITHMS_BAD_MATCHING_H

#include <string>
#include <cassert>

/*
 * 蛮力算法: 模式串依次对齐文本串中每个可能的位置执行 m 次对比， 判断当前对齐位置是否完全匹配
 * text:    t1 t2 ... ti ti+1 ...t(i+j)........ tn
 * patt:              p1 p2 .....pj... pm
 */
int bad_matching(std::string text, std::string pattern) {
    if (text.size() < pattern.size() || pattern.size() == 0)
        return -1;
    for (int i = 0; i <= text.size() - pattern.size(); ++i) {
        int j;
        for (j = 0; j < pattern.size(); ++j) {
            if (pattern[j] != text[i+j])
                break;
        }
        if (j == pattern.size() && pattern.size() != 0)
            return i;
    }
    return -1;
}

#endif //INTRODUCTION_TO_ALGORITHMS_BAD_MATCHING_H
