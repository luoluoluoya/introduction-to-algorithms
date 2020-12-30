//
// Created by 张锐 on 2020/12/29.
//

#ifndef INTRODUCTION_TO_ALGORITHMS_AC_MATCING_H
#define INTRODUCTION_TO_ALGORITHMS_AC_MATCING_H

/*
 * AC算法是Alfred V.Aho（《编译原理》（龙书）的作者），和Margaret J.Corasick于1974年提出（与KMP算法同年）的一个经典的多模式匹配算法，
 * 可以保证对于给定的长度为n的文本，和模式集合P{p1,p2,...pm}，在O(n)时间复杂度内，找到文本中的所有目标模式，而与模式集合的规模m无关。
 *
 * 经典的AC算法由三部分构成，goto表，fail表和output表，goto表是由模式集合P中的所有模式构成的状态转移自动机。
 *
 * 多模式串匹配的算法执行过程为在自动机上依次输入字符，执行状态转换，若达到接受状态则保存输出状态所对应的output表信息。
 *
 * 自动机为五元祖：Z = {Q(所有状态集合), q0(初始状态), A(可接受状态), M(有限输入字符集), &(状态转移函数)};
 *
 * 伪代码实现：
 * ac_matching(text, patterns):
 *      build the auto machine;
 *      q = 0; i = 0;
 *      while(i != text.len):
 *          if (q in A):            // A为可接收状态
 *              output(q.output)    // 记录输出
 *          if q == 0:              // 不存在可行的状态迁移，查看fail表
 *              q = q.fail;
 *              while (q != 0 && &(q, text[i]) == 0):   // 在fail表中移动，直至回到状态0或者存在可接受输入
 *                  q = q.fail;
 *              if q == 0:
 *                  if (&(0, text[i])) == 0):
 *                      i++;
 *                  continue;
 *          q = &(q, text[i]);
 *          ++i;
 *
 * dfa中自动机如何构建：在dfa算法中，自动机的所有状态集合为0～模式串的长度m. 初始状态为0， 可接受状态为m，状态转移函数 &(q, a) = f(Pqa); （当读取文本串T[i]字符时模式串 P 的前缀与文本串 T[0,i) 的后缀的最长匹配长度为m时实现一个匹配）
 * 此处如何构建自动机：
 *
 * 如何构造失配指针
 *  进一步的话，其实失配指针代表的是子串之间后缀和前缀之间的关系。对于字符串bca，它的严格后缀（我理解是不包括自己的后缀）是ca,a,None，前缀是bca,bc,b,None；对于另外一个字符串caa，
 *  它的前缀是caa,ca,c,None，我们发现bca的后缀其实出现在caa的前缀中，因此bca在匹配下一个字符失败的时候，我们可以跳到caa的第一个a节点上继续匹配下一个字符，因为ca已经匹配过了。
 *  节点i失配指针指向的节点j代表的意思是到节点i为止的字符串最长的严格后缀等于到节点j为止的字符串，对于上面的bca的例子，如果trie树中存在ca字符串，
 *  那么失配节点指向的就是ca的a节点；如果trie树中只有a，那么就是a节点了；如果都不存在，那么就是root节点，我们要从头开始匹配。
 *  注意这里提到的是最长的严格后缀，大家可以想想为什么一定要最长？因为我们匹配的时候是从左到右一个一个字符匹配的，如果不是最长的话我们就丢失了匹配的信息了，
 *  举例来说有bcacay字符串待匹配，有子串bcacax,cacay，如果不是最长的话bcaca就可能会指向cacay的第一个ca了，那么就丢掉了匹配到的caca信息，造成匹配失败。
 * 关于如何构造失配指针，其实是一个BFS的算法，按照层序遍历的方法构建：
 *  首先root节点不管，root节点的孩子肯定都是指向root节点的，因为他们的后缀都是空
 *  假设我们已经有了节点x的失配指针，那么我们如何构造他们孩子child的失配指针呢？因为失配指针保证的是最大后缀，因此他肯定保证了x之前的字符都是匹配的。我们知道x的失配指针指向的是节点x的最大后缀y，因此我们只要看看节点y的孩子节点中是不是有child节点对应的字符，如果有的话那很好，child的失配指针就是y的那个孩子
 *  那如果没有呢，那我们就继续看y节点的失配指针了，因为他也指向y节点的最大后缀，也保证了跟x字符是匹配的。这样一直下去直到相应的节点，或者直到根节点
 *  这个最关键的就是构建失配指针。为什么要构建失配指针？
 */

#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

#define ALPHABET_SIZE  26
#define MAXIUM_STATES 100

int _goto[MAXIUM_STATES][ALPHABET_SIZE];
int _fail[MAXIUM_STATES];
set<string> _out[MAXIUM_STATES];//使用set是因为在生成fail表，同时更新out表过程中，有可能向同一位置多次插入同一个模式串



inline void BuildGoto(const vector<string> &patterns) {
    unsigned int used_states;
    unsigned int t;

    vector<string>::const_iterator vit;
    string::const_iterator sit;

    for (vit = patterns.begin(), used_states = 0; vit != patterns.end(); ++vit) {
        for (sit = vit->begin(), t = 0; sit != vit->end(); ++sit) {
            if (_goto[t][(*sit) - 'a'] == 0) {
                _goto[t][(*sit) - 'a'] = ++used_states;
                t = used_states;
            } else {
                t = _goto[t][(*sit) - 'a'];
            }
        }
        _out[t].insert(*vit);
    }
}


inline void BuildFail(const vector<string> &patterns) {
    unsigned int t, m, last_state;
    unsigned int s[20];

    vector<string>::const_iterator vit;
    string::const_iterator sit1, sit2, sit3;

    for (vit = patterns.begin(); vit != patterns.end(); ++vit) {
        //先要找到输入的单词的各字母对应的状态转移表的状态号，由于状态转移表没有
        //记录各状态的前驱状态信息，该步暂时无法掠过
        t = 0;
        m = 0;
        sit1 = vit->begin();

        while (sit1 != vit->end() && _goto[t][*sit1 - 'a'] != 0) {
            t = _goto[t][*sit1 - 'a'];
            ++sit1;
            s[m++] = t;
        }

        for (sit1 = vit->begin() + 1; sit1 != vit->end(); ++sit1) {
            //此时的[sit2, sit1+1)就是当前模式的一个非前缀子串
            for (sit2 = vit->begin() + 1; sit2 != sit1 + 1; ++sit2) {
                t = 0;
                sit3 = sit2;

                //对该子串在goto表中执行状态转移
                while (sit3 != sit1 + 1 && _goto[t][*sit3 - 'a'] != 0) {
                    t = _goto[t][*sit3 - 'a'];
                    ++sit3;
                }

                //当前子串可以使goto表转移到一个非0位置
                if (sit3 == sit1 + 1) {
                    //求出输入当前子串在goto表中所转移到的位置
                    last_state = s[sit3 - vit->begin() - 1];

                    //更新该位置的fail值，如果改为值得fail值为0，则用t值替换，因为对于sit1而言，是按照以其为末尾元素的非前缀
                    //子串的由长到短的顺寻在goto表中寻找非0状态转移的，而满足条件的t是这里免得最长子串
                    if (_fail[last_state] == 0) {
                        _fail[last_state] = t;
                    }

                    //如果两者都标识完整的模式串
                    if (_out[last_state].size() > 0 && _out[t].size() > 0) {
                        //将out[t]内的模式串全部加入out[last_state]中
                        for (set<string>::const_iterator cit = _out[t].begin(); cit != _out[t].end(); ++cit) {
                            _out[last_state].insert(*cit);
                        }
                    }
                }
            }
        }
    }
}


void AC(const string &text, const vector<string> &patterns) {
    unsigned int t = 0;
    string::const_iterator sit = text.begin();

    BuildGoto(patterns);
    BuildFail(patterns);

    //每次循环中，t都是*sit的前置状态
    while (sit != text.end()) {
        //检查是否发现了匹配模式，如果有，将匹配输出
        if (_out[t].size() > 0) {
            cout << (sit - text.begin() - 1) << ": ";

            for (set<string>::const_iterator cit = _out[t].begin(); cit != _out[t].end(); ++cit) {
                cout << (*cit) << ", ";
            }

            cout << '\n';
        }

        if (_goto[t][*sit - 'a'] == 0) {
            t = _fail[t];

            //找到可以实现非0跳转的fail状态转移
            while (t != 0 && _goto[t][*sit - 'a'] == 0) {
                t = _fail[t];
            }

            if (t == 0) {
                //跳过那些在初始状态不能实现非0状态跳转的字母输入
                if (_goto[0][*sit - 'a'] == 0) {
                    ++sit;
                }

                continue;
            }
        }

        t = _goto[t][*sit - 'a'];
        ++sit;
    }
}


#endif //INTRODUCTION_TO_ALGORITHMS_AC_MATCING_H
