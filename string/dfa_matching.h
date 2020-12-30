//
// Created by 张锐 on 2020/12/29.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_DFA_MATCHING_H
#define INTRODUCTION_TO_ALGORITHMS_DFA_MATCHING_H

/*
 * 基于有限自动机的字符串匹配
 *
 * 有限自动机 Z = {Q, q0, A, M, &};
 *  所有状态集合，初始状态， 可接受的状态， 有限输入字符集， 状态转移函数;
 *  eg: qx状态时输入 a => q=&(qx, a);
 * 终态函数： g(s) = q; 自动机处理完整个字符串之后所处的状态
 *
 * 后缀函数f(x): x的后缀P的最长前缀的长度。
 * 记录已得到的与模式串P匹配的文本串T的最长前缀。
 * 设计状态转移函数，使得自动机的状态数q为在读取文本串T[i]字符时记录模式串 P 的前缀与文本串 T[0,i) 的后缀的最长匹配长度。
 * &(q, a) = f(Qqa);
 * 对于所有的q=m时，模式串长m的前缀与文本串的某一个 T[0,i)匹配， 则得到一个完全匹配。
 *
 * q1 = &(q0, T[i])  => q1 = f(PqoT[i])
 * 123  ... 123...; q = 3;
 * 123x ... 123a..;
 * a = T[q+1] 时 f(PqT[i]) = q+1;
 * a != T[q+1] 时，为了继续寻找模式串 P 的前缀与文本串 T[0,i) 的后缀的最长匹配。则需要将范围 f(Pqa)
 *
 * automaton-machine(T, &, m) {
 *      n = T.length;
 *      q = 0;
 *      for i = 1 to n:
 *          q = &(q, T[i]);
 *          if (q == m)
 *              printf("matching at i-m");
 * }
 *
 * transition-function(P, M) {
 *      m = P.length;
 *      for q=0 to m:
 *          for a in M:
 *              k = q+1;
 *              while (Pk 不是 Pqa的后缀) k--;
 *              &(q, a) = k;
 *      return &;
 * }
 */

#include <string>
#include <vector>
#include <set>

/*
   a b c
0| 1 0 0 a
1| 1 2 0 b
2| 3 0 0 a
3| 1 4 0 b
4| 5 0 0 a
5| 1 4 6 c
6| 7 0 0 a
7| 1 2 0
 */
// 判定P[0, k] 是否为 P[0, q)a 的后缀
bool isSuffix(const std::string &pattern, int k, int q, char a) {
    if (pattern[k--] != a)
        return false;
    --q;
    while (k >= 0 && pattern[k] == pattern[q]) {
        k--;
        q--;
    }
    return k == -1;
}

int **transitionFunction(const std::string &pattern, const std::vector<char> &characterSet) {
    int m = pattern.size();
    int **t = new int *[m + 1];                 // 保存前缀的长度
    for (int i = 0; i <= m; ++i) {
        t[i] = new int[characterSet.size()];
    }
    for (int q = 0; q <= m; ++q) {              // 模式串的最长前缀是文本串的后缀的长度； 长度为q的前缀P[0, q);
        for (int i = 0; i < characterSet.size(); i++) {
            int k = q;                          // 从P[0, q]进行一次判定
            while (k >= 0 && !isSuffix(pattern, k, q, characterSet[i])) k--;
            t[q][i] = k + 1;
        }
    }
    return t;
}

int charPos(const std::vector<char> &characterSet, char c) {
    for (int i = 0; i < characterSet.size(); ++i) {
        if (characterSet[i] == c)
            return i;
    }
    return -1;
}

int automatonMachine(const std::string &text, const std::string &pattern) {
    std::vector<char> charset = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                               'J', 'K', 'L', 'M', 'N', 'Y', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                               ' ', ',', '!'};
    int n = text.size(), m = pattern.size(), q = 0;
//    std::vector<char> charset = {'a', 'b', 'c'};
    int **t = transitionFunction(pattern, charset);
    for (int i = 0; i < n; ++i) {
        int pos = charPos(charset, text[i]);
        if (pos == -1)
            throw std::logic_error("存在不在字符集中的字符");
        q = t[q][pos];
        if (q == m)
            return i - m + 1;
    }
    return -1;
}


#endif //INTRODUCTION_TO_ALGORITHMS_DFA_MATCHING_H
