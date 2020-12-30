//
// Created by 张锐 on 2020/12/29.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_BM_MATCHING_H
#define INTRODUCTION_TO_ALGORITHMS_BM_MATCHING_H

/*
 * BM算法
 *
 * 后缀匹配，是指模式串的比较从右到左，模式串的移动也是从左到右的匹配过程，经典的BM算法其实是对后缀蛮力匹配算法的改进。为了实现更快移动模式串，BM算法定义了两个规则，好后缀规则和坏字符规则
 *
 * 基于坏字符的匹配
 *  1. 改变每个对齐位置的匹配策略，基于对齐位置 i 的匹配从后往前进行 j=m to 0;
 *  2. 当本次对齐失配于 j 时, P[j] != T[i+j]; 在文本串中寻找 T[i+j] 最后出现位置来与此处进行重新匹配（新位置不能导致模式串的左移）
 *      t0 t1 t2 t3 .... ti ti+1 ..ti+j.. tn
 *                      p0 p1 p2 .pj.....pm
 *      当 ti+j != pj 时，根据坏字符提供的教训。寻找P中ti+j最后出现的位置，并进行对齐， 移动量 std::max(1, j - bc[text[i+j]]) (保证最后出现字符在j之后时，字符串不左移。字符串不存在时，移动 j+1)；
 *
 * 基于好后缀的匹配
 *      t0 t1 t2 t3 .... ti ti+1 ..ti+j.. tn
 *                      p0 p1 p2 .pj.....pm
 *      当 ti+j != pj 时，可得知 P(j, m] = T(i+j, i+m]，根据好后缀提供的经验，对字符串进行大量移动。
 *          若在P[0, j)中存在P[r]可与T[i+j]进行匹配时：
 *              P(r, r+m-j] = P(j, m] = T(i+j, i+m] 且 P[r] = T[i+j] != P[j];
 *          若在P[0, j)中不存在可与T[i+j]进行匹配的位置时,令对齐位置越过 i+j;
 */

#include <string>

// 获取坏字符表
int *buildBC(const std::string &p) {
    int *bc = new int[256];
    for (int i = 0; i < 256; ++i) {
        bc[i] = -1;
    }
    for (int j = 0; j < p.size(); ++j) {
        bc[p[j]] = j;
    }
    return bc;
}

// suffixes(i) 与 pattern 的最长公共后缀
int *suffixes(const std::string &pattern) {
    int m = pattern.size();
    int *suffix = new int[m];
    suffix[m - 1] = m;
    for (int i = m - 2; i > -1; --i) {
        int q = i;
        while (q >= 0 && pattern[q] == pattern[m - 1 - i + q]) {
            q--;
        }
        suffix[i] = i - q;
    }
    return suffix;
}

// 构造gs表
int *buildGs(const std::string &pattern) {
    int m = pattern.size();
    int *gs = new int[m];
    int *suffix = suffixes(pattern);
    // i的前缀中不存在与模式串P[i, m]后缀匹配时
    for (int i = 0; i < m; ++i) {
        gs[i] = m;
    }
    // 存在前缀与后缀的匹配
    for (int i = m - 1, j = 0; i > 0; --i) {
        if (suffix[i] == i + 1) { //若P[0, i] = P[m - i - 1, m)，则对于P[m - i - 1]左侧的每个字符P[i]而言m - i - 1都是gs[i]的一种选择
            while (j < m - i - 1)
                gs[j++] = m - i - 1;
        }
    }
    // 存在完全匹配匹配
    for (int i = 0; i < m - 2; ++i) {
        gs[m - 1 - suffix[i]] = m - 1 - i;
    }
    delete suffix;
    return gs;
}

// 依据坏字符进行字符串匹配
int bm_bc_mapping(const std::string &text, const std::string &pattern) {
    if (text.size() < pattern.size() || pattern.size() == 0)
        return -1;
    int *bc = buildBC(pattern);
    int n = text.size(), m = pattern.size(), i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (text[i + j] == pattern[j]) {
            if (--j < 0)
                break;
        }
        if (j < 0) {
            break;
        } else {
            i += std::max(1, j - bc[text[i + j]]);
        }
    }
    delete[] bc;
    return i <= n - m ? i : -1;
}

// 依据坏字符和好后缀的字符串匹配
int bm_mapping(const std::string &text, const std::string &pattern) {
    int i = 0, n = text.size(), m = pattern.size();
    if (n < m || m == 0)
        return -1;
    int *gs = buildGs(pattern);
    int *bc = buildBC(pattern);
    while (i <= n - m) {
        int j;
        for (j = m - 1; j > -1 && text[i + j] == pattern[j]; --j);
        if (j < 0)
            break;
        else
            i += std::max(gs[j], std::max(1, j - bc[text[i + j]]));
    }
    delete gs;
    delete bc;
    return i > n - m ? -1 : i;
}


#endif //INTRODUCTION_TO_ALGORITHMS_BM_MATCHING_H
