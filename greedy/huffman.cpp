//
// Created by 张锐 on 2020/12/18.
//

/*
 * 前缀码：对每一个字符规定一个0,1串作为其代码，并要求任一字符的代码都不是其他字符代码的前缀。这种编码称为前缀码。编码的前缀性质可以使译码方法非常简单；
 *  例如001011101可以唯一的分解为0,0,101,1101，因而其译码为aabe。译码过程需要方便的取出编码的前缀，因此需要表示前缀码的合适的数据结构。为此，
 *  可以用二叉树作为前缀码的数据结构：树叶表示给定字符；从树根到树叶的路径当作该字符的前缀码；代码中每一位的0或1分别作为指示某节点到左儿子或右儿子的“路标”。
 * 为什么使用前缀码：
 *  前缀吗可以有效的提高解码效率，编码串可从头至尾进行解码。避免出现歧义和回溯的情况。
 * 构造哈夫曼编码：
 *  哈夫曼提出构造最优前缀码的贪心算法，由此产生的编码方案称为哈夫曼编码。其构造步骤如下：
 *  (1)哈夫曼算法以自底向上的方式构造表示最优前缀码的二叉树T。
 *  (2)算法以|C|个叶结点开始，执行|C|－1次的“合并”运算后产生最终所要求的树T。
 *  (3)假设编码字符集中每一字符c的频率是f(c)。以f为键值的优先队列Q用在贪心选择时有效地确定算法当前要合并的2棵具有最小频率的树。一旦2棵具有最小频率的树合并后，产生一棵新的树，其频率为合并的2棵树的频率之和，并将新树插入优先队列Q。经过n－1次的合并后，优先队列中只剩下一棵树，即所要求的树T。
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>

// Huffman 超字符
template<typename T>
struct HuffChar {
    T data;
    size_t freq;
    HuffChar(T d = T(), size_t f = 0):data(d),freq(f) {}
    friend bool &operator==(const HuffChar<T>& hc, const T& t);
};
template<typename T>
bool &operator==(const HuffChar<T>& hc, const T& t) {
    return hc.data == t;
}

// HuffmanTree 的节点； //todo 此处未实现完整的树结构
template<typename T>
struct HuffNode {
    HuffChar<T> data;
    typedef HuffNode<T>* Pointer;
    Pointer parent, lc, rc;
    HuffNode(HuffChar<T> d, Pointer p = nullptr, Pointer l = nullptr, Pointer r = nullptr):data(d), parent(p),lc(l),rc(r) {}
    bool operator<=(HuffNode o) const { return data->freq <= o.data->freq; }
};

// 利用vector实现HuffForest; (可更换为优先级队列)
template<typename T>
using HuffForest = std::vector<HuffNode<T>*>;

// 利用贪心算法构造HuffmanTree
template <typename T>
HuffNode<T>* buildHuffmanTree(HuffForest<T> &forest) {
    while (forest.size() > 1) {
        std::sort(forest.begin(),forest.end());
        HuffNode<T>* t1 = forest[0]; HuffNode<T>* t2 = forest[1];
        HuffNode<T>* nt = new HuffNode<T>(HuffChar<T>('^', t1->data.freq + t2->data.freq), nullptr, t1, t2);
        t1->parent = nt; t2->parent = nt;
        typename std::vector<HuffNode<T>*>::iterator iter = forest.erase(forest.begin(), forest.begin()+2);
        forest.push_back(nt);
    }
    return forest[0];
}

// 用字符串生成编码树
template <typename T>
HuffNode<T>* buildHuffmanTree(const std::string& text) {
    std::map<char, int> count;
    for (int i = 0; i < text.size(); ++i)
        ++count[text[i]];
    HuffForest<T> forest;
    for (const auto& b : count)
        forest.insert(forest.end(), new HuffNode<T>(HuffChar<T>(b.first, b.second)));
    return buildHuffmanTree(forest);
}

// 通过HuffManTree构造编码表
template <typename T>
void buildEncodeTable(const HuffNode<T>* node, std::map<T, std::string> &table, std::string code = "") {
    if (!node->lc) {
        table[node->data.data] = code;
    } else {
        code.push_back('0');
        buildEncodeTable(node->lc, table, code);
        code.pop_back(); code.push_back('1');
        buildEncodeTable(node->rc, table, code);
        code.pop_back();
    }
}

// 打印HuffmanTree
template<typename T>
void printHuffTree(const HuffNode<T>* node, std::string code = "") {
    if (!node->lc) {
        std::cout << "节点`" << node->data.data << "`出现次数为:" << node->data.freq << "; 编码串为:" << code << std::endl;
    } else {
        code.push_back('0');
        printHuffTree(node->lc, code);
        code.pop_back(); code.push_back('1');
        printHuffTree(node->rc, code);
        code.pop_back();
    }
}

// 对字符串进行解码
template <typename T>
std::string decode(const HuffNode<T>* root, std::string encodedString) {
    std::string str;
    const HuffNode<T>* p = root;
    for (int i = 0; i <= encodedString.size(); ++i) {
        if (!p->lc) {                           // 不存在子树，表明达到了也节点，直接打印; 并重置到跟节点
            str.push_back(p->data.data); p = root;
        }
        if (encodedString[i] == '1') {          // 1: 进入右子树
            p = p->rc;
        } else {                                // 0: 进入左子树
            p = p->lc;
        }
    }
    return str;
}

// 对字符串进行编码
std::pair<std::string, std::string> encode(const std::string& text) {
    std::string code;
    HuffNode<char>* tree = buildHuffmanTree<char>(text);
    //printHuffTree<char>(tree);
    std::map<char, std::string> table;
    buildEncodeTable(tree, table);
    for (int i = 0; i < text.size(); ++i)
        code.append(table[text[i]]);
    std::string deStr = decode(tree, code);
    return std::make_pair(code, deStr);
}
