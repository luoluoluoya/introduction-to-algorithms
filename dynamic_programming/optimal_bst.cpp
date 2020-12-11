//
// Created by 张锐 on 2020/12/11.
//

/**
二叉搜索树
    二叉搜索树满足如下性质：假设x是二叉搜索树中的一个结点。如果lr是x的左子树的一个结点，那么lr.key ≤ x.key。如果rc是x的右子树的一个结点，那么r.key ≥ x.key。
也就是说，二叉搜索树中的任意一个结点，它的左子树中的所有结点都不大于它，它的右子树中的所有结点都不小于它。
    如果在二叉树中查找元素不考虑概率及查找不成功的情况下，可以采用红黑树或者平衡二叉树来搜索，这样可以在O(lgn)时间内完成。而现实生活中，查找的关键字是有一定的概率的，
就是说有的关键字可能经常被搜索，而有的很少被搜索，而且搜索的关键字可能不存在，为此需要根据关键字出现的概率构建一个二叉树。比如中文输入法字库中各词条（单字、词组等）
的先验概率，针对用户习惯可以自动调整词频，以减少用户翻查次数，使得经常用的词汇被放置在前面，这样就能有效地加快查找速度。这就是最优二叉树所要解决的问题。

最优二叉搜索树
问题描述
    给定一个由n个互异的关键字组成的有序序列K={k1<k2<k3<,……,<kn}和它们被查询的概率P={p1,p2,p3,……,pn}，要求构造一棵二叉查找树T，使得查询所有元素的总的代价最小。
对于一个搜索树，当搜索的元素在树内时，表示搜索成功。当不在树内时，表示搜索失败，用一个“虚叶子节点”来标示搜索失败的情况，因此需要n+1个虚叶子节点{d0<d1<……<dn}，
对于应di的概率序列是Q={q0,q1,……,qn}。其中d0表示搜索元素小于k1的失败结果，dn表示搜索元素大于kn的失败情况。di（0<i<n）表示搜索节点在ki和k(i+1)之间时的失败情况。因此有如下公式：
    SUM(Pi) + SUM(Qj) = 1 ( for i=1 to n; for j=0 to n);  （关键字要么查找失败要么查找成功）

由每个关键字和每个虚拟键被搜索的概率，可以确定在一棵给定的二叉查找树T内一次搜索的期望代价。设一次搜索的实际代价为检查的节点个数，即在T内搜索所发现的节点的深度加上1。所以在T内一次搜索的期望代价为：
    E(T) = (dep(i) + 1)*Pi + (dep(j)+1)*Qj; ( for i=1 to n; for j=0 to n);
         = dep(i)Pi + dep(j) + 1;    ( for i=1 to n; for j=0 to n);
需要注意的是：一棵最优二叉查找树不一定是一棵整体高度最小的树，也不一定总是把最大概率的关键字放在根部。

蛮力策略求解：
    考察 n 个关键字所组成的所有树结构并进行求解， 返回搜索效率最高的树结构

动态规划策略求解：
步骤1：刻画一个最优解的结构特征
    如果一棵最优二叉查找树T有一棵包含关键字ki，……，kj的子树T'，那么这棵子树T’对于对于关键字ki，……kj和虚拟键di-1，……，dj的子问题也必定是最优的。
    若T中的子树T'不是最优二叉搜索树，则可以将T'的另一颗更优二叉搜索树T''对T'进行替换。使T的搜索效率更高，这与T是最优二叉搜索树是矛盾的，故T'是最优的
步骤2：递归地定义最优解的值
    定义 E[i,j] 为对关键字 Ki ~ Kj 构成的最优二叉搜索树的查找效率。
    定义 W[i,j] 为对关键字 Ki ~ Kj 的查找概率之和。 W[i, j] = (Pi+..+Pj)+(Qi-1 + Qi + Qj); (成功与失败的概率之和)
    E[1,n] = 1; (n=1);
    E[1,n] = Pk + ( E[1, k-1] + W[1, k-1] ) + (E[k+1, n] + w[k, n]); (n>1); // 考察所有的k
           = E[1,k-1] + E[k+1,n] + w[1, n];
   一般化定义子问题 i，j
   E[i,j] = min(E[i,k-1]+E[k+1,j]+W[i,j]); //考察以所有合法的r作为跟节点时的最小值
步骤3：计算最优解的值
    将E[i,j]的值保存到一个二维数组E[1..1+n,0..n]中，用root[i,j]来记录关键字ki，……，kj的子树的根，采用二维数组root[1..n,1..n]来表示。为了提高效率，防止重复计算，需要个二维数组W[1..n+1,0...n]来保存w(i,j)的值，其中W[i,j] = W[i,j-1]+pj+qj。
    计算过程的伪代码：
    OPTIMAL_BST(p,q,n): // p：关键字及其概率， q：失败位置及其概率， n：关键字个数；(p.size = n = q.size-1)
        for i=1 to n+1:
            E[i,i-1] = qi-1;
            W[i,i-1] = qi-1;
        for l=1 to n:
            for i=1 to n-l+1:
                j = i+l-1;
                W[i,j] = W[i,j-1]+pj+qj;
                E[i, j] = INT_MAX;
                for k=i to j:
                    q = E[i, k-1] + E[k+1,j] + w[i,j]
                    if (q < E[i, j])
                        E[i,j] = q;
                        root[i,j] = k;
 步骤4：利用计算出的信息构造一个最优解
    PRINT_BST(root, i, j):
        if (i==j)   // 基本情况
            return;
        else       // 递归情况
            PRINT_BST(root, i, root[i, j]-1)  // 打印左子树
            print root[i, j]
            PRINT_BST(root, root[i, j]+1,j)  // 打印右子树
 */

#include <cassert>
#include <iostream>
const int N = 5; // todo N等于关键字的个数
double e[N+2][N+1];
int root[N+1][N+1];
int w[N+2][N+1];

// 构造一个简单的二叉树
template <typename T>
struct binNode {
    typedef binNode* NodePointer;
    T data;
    double freq;
    NodePointer lc, rc, parent;
    binNode(T d = T(), double f = 0):data(d),freq(f) { }
};
template <typename T>
struct OptimalBst {
};


/**
 * @param p         节点出现频率：前置补0， 故第i个节点的概率为 p[i]; 故 p.size = q.size
 * @param q         第i个节点左侧概率为q[i-1]， 右侧为q[i]
 * @param num       节点个数: num+1 =p.size=q.size
 * @param e         e[i,j]即包含节点[i~j]的最优二叉搜索树； 考虑E需要保存左右子树为空的情况，故行比列多1: (1,0),(n+1, n)
 * @param root      root[i,j]即包含节点[i~j]的最优二叉搜索树的根节点
 */
void analyzeOptimalBst(float p[], float q[], int num) {
    assert(num == N);

    for (int i = 1; i <= num+1; ++i) {         //左子树为空的初始化
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    // 考察长度 l 为 1 ～ n 的 num-l+1 个元素 A[i, j], 取最优解
    for (int l = 1; l <= num; ++l) {
        for (int i = 1; i <= num-l+1; ++i) {
            int j = i+l-1;
            e[i][j] = INT_MAX;
            auto tw = w[i][j-1]+p[j]+q[j];
            w[i][j] = tw;
            for (int r = i; r <= j; ++r) {
                double m = e[i][r-1] + e[r+1][j] + w[i][j];
                if (m < e[i][j]) {
                    e[i][j] = m;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printOptimalBst(int i, int j) {
    if(i==1 && j==N)
        std::cout<<"root is "<<root[i][j]<<std::endl;
    if(i<j) {
        int r=root[i][j];
        if(i!=r)
            std::cout<<"left child root "<<root[i][r-1]<<std::endl;
        if(j!=r)
            std::cout<<"right child root "<<root[r+1][j]<<std::endl;
    }
}
