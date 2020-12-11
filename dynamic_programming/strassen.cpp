//
// Created by 张锐 on 2020/12/10.
//

/*
矩阵链乘法
给定一个n个矩阵的序列(矩阵链) {A1,A2,A3...An}，我们希望计算它们的乘积 A1A2A3...An
为了计算表达式,我们可以先用括号明确计算次序，然后利用标准的矩阵相乘算法进行计算。由于矩阵乘法满足结合律，因此任何加括号的方法都会得到相同的计算结果。
我们称有如下性质的矩阵乘积链为完全括号化的(fully parenthesized)：它是单一矩阵，或者是两个完全括号化的矩阵乘积链的积，且已外加括号。对矩阵链加括号的方式会对乘积运算的代价产生巨大影响。

两个矩阵相乘伪码：
    MATRIX-MULTIPLY(A, B)
        if A.columns != B.rows
            throw error 'xx'
        else
            let c be a new A.rows B.columns matrix
            for i = 1 to A.rows
                for j = 1 to B.columns
                    c_ij = 0
                    for k = 1 to A.columns
                        c_ij = c_ij + A_ik*B_kj
        return c
复杂度：O(pqr)
    两个矩阵A和B只有相容(compatible),即A的列数等于B的行数时，才能相乘。如果A 是p*q的矩阵，B是q*r的矩阵，那么乘积C是p*r的矩阵。计算C所需时间即pqr.

矩阵链乘法问题(matrix-chain multiplication problem)可描述如下：给定 n 个矩阵的链 {A1,A2,A3...An}，矩阵Ai的规模为p_{i-1}*p_{i},求完全括号化方案，使得计算乘积 A1A2A3...An, 所需标量乘法次数最少。
注意，求解矩阵链乘法问题并不是要真正进行矩阵相乘运算，我们的目标只是确定代价最低的计算顺序。确定最优计算顺序所花费的时间通常要比随后真正进行矩阵相乘所节省的时间要少。

计算括号化方案的数量
在用动态规划方法求解矩阵链乘法问题之前，我们先来说服自己——穷举所有可能的括号化方案不会产生一个高效的算法。对一个n个矩阵的链，令P(n) 表示可供选择的括号化方案的数量。
当n=1时，由于只有一个矩阵，因此只有一种完全括号化方案。当 n >= 2 时，完全括号化的矩阵乘积可描述为两个完全括号化的部分积相乘的形式，
而两个部分积的划分点在第k个矩阵和第 k + 1 个矩阵之间，K为中 1 ~ n 的任意一个值。因此，我们可以得到如下递归公式：
    P(n) = min(P(k)P(n-k)) (n > 1, k=1 to n)
    P(n) = 1 (n = 1);

括号化方案的数量与 n 呈指数关系，通过暴力搜索穷尽所有可能的括号化方案来寻找最优方案，是一个糟糕的策略。

应用动态规划方法
步骤1：最优括号化方案的结构特征
动态规划方法的第一步是寻找最优子结构，然后就可以利用这种子结构从子问题的最优解构造出原问题的最优解。在矩阵链乘法问题中，此步骤的做法如下所述。
如果问题是非平凡的，即那么 为了对{A1,A2,A3...An}进行括号化，我们就必须在某个A1和An之间将矩阵链划分开， 并考察各种划分策略所能得到的最优解。
将给定矩阵 S = {A1,A2,A3...An} 以任意 k（k = 1 to n） 进行划分之后，我们得到两个子问题 S1 = {A1A2...Ak}, S2 = {Ak+1, Ak+2...An}
利用粘贴-剪切技术可证明，原问题划分所得的子问题必定为原问题进行独立求解时的最优解。故矩阵链乘法问题具有最优子结构且子问题可以独立求解。

步骤2：一个递归求解方案
    定义 E(i, j) 为对矩阵 {Ai, Ai+1 ... Aj} 的矩阵链乘最小代价值; 矩阵Ai的规模为p(i-1)×pi(i=1,2,...,n)
    E(1, n) = O(1); (n=1)
    E(1, n) = E(1, k) + E(k+1, n) + p{0}p{k}p{n}; (n>1)

步骤3：求解最优解值
    // 输入是一个序列p=<p0,p1,...,pn>，其长度为p.length=n+1。过程用一个辅助表m[1..n,1..n]来保存代价m[i,j]，用另一个辅助表s[1..n-1,2..n](s[1,2]..s[n-1,n]这里i<j)记录最优值m[i,j]对应的分割点k
    // 对于矩阵A(i)A(i+1)...A(j)最优括号化的子问题，我们认为其规模为链的长度j-i+1。因为j-i+1个矩阵链相乘的最优计算代价m[i,j]只依赖于那么少于j-i+1个矩阵链相乘的最优计算代价。因此，算法应该按长度递增的顺序求解矩阵链括号化问题，并按对应的顺序填写表m
    MATRIX_CHAIN_ORDER(int *p,int Length,int m[][M],int s[][M]):
        for l=1 to n:       //  长度为 l 的矩阵链
            for i=1 to n:   //  考察所有子问题 A[i, j]
                j = i+l-1;
                m[i][j] = INT_MIN;
                for k=i to j:   // 考察子问题的所有选择， 取最优者; 并更新当前问题的括号选择位置和更优解值
                    q = m[i][k] + m[k][j] + p[i-1]p[k]p[j]
                    if (m[i][j] < q)
                        m[i][j] = q;
                        s[i][j] = k;
        return m[1][n];

步骤4：构造最优解
虽然MATRIX_CHAIN_ORDER求出了计算矩阵链乘积所需的最少标量乘法运算次数，但它并未直接指出如何进行这种最优代价的矩阵链乘法计算。表s[i,j]记录了一个k值，指出A(i)A(i+1)...A(j)的最优括号化方案的分割点应在A(k)和A(k+1)之间。
因此，我们A(1..n)的最优计算方案中最后一次矩阵乘法运算应该是以s[1,n]为分界的A(1..s[1,n])*A(s[1,n]+1..n)。我们可以用相同的方法递归地求出更早的矩阵乘法的具体计算过程，因为s[1,s[1,n]]指出了计算A(1..s[1,n])时应进行的最后一次矩阵乘法运行；
s[s[1,n]+1,n]指出了计算A(s[1,n]+1..n)时应进行的最后一次矩阵乘法运算。下面给出的递归过程可以输出<A(i),A(i+1),...,A(j)>的最优括号化方案。
    PRINT_OPTIMAL_PARENS(int s[][M], int i, int j):
        if (i==j)
            print Ai;
        printf (;
        PRINT_OPTIMAL_PARENS(int s[][M], i, s[i][j]);
        PRINT_OPTIMAL_PARENS(int s[][M], s[i][j]+1, j);
        printf );
*/

const int M = 7;// M等于矩阵链的长度
/*
    问题输入：
        int * matrixes: 输入矩阵链，第 i 个矩阵的大小为 matrixes[i-1]*matrixes[i];  (故: matrixes.size() = length + 1)
        length: matrixes元素个数
        m: 保存矩阵链[i, j]的最少乘法数；   len(i, j) = j-i+1
        s: 保存矩阵链[i, j]的括号切分位置;
    输出：
        当前矩阵的最少乘法数
*/

// 带备忘录的自顶向下递归求解
int doRecursive(int *matrixes, int p, int q, int m[][M], int s[][M]) {    // 求解矩阵链A[p,q]
    assert(p <= q);
    if (m[p][q] >= 0)   // 备忘录
        return m[p][q];
    m[p][q] = INT_MAX;
    for (int i = p; i < q; ++i) {
        int v = doRecursive(matrixes, p, i, m, s) + doRecursive(matrixes, i+1, q, m, s) + matrixes[p-1]*matrixes[i]*matrixes[q];
        if (v < m[p][q]) {
            m[p][q] = v;
            s[p][q] = i;
        }
    }
    return m[p][q];
}
void matrixChainOrderRecursive(int *matrixes, int length, int m[][M], int s[][M]) {
    int len = length-1; // 矩阵个数为 matrixes.size()-1
    for (int i = 1; i <= len; ++i) {
        for (int j = 0; j <= len; ++j)
            m[i][j] = INT_MIN;
        m[i][i] = 0;
    }
    doRecursive(matrixes, 1, len, m, s);
}

// 自底向上求解策略
void matrixChainOrder(int *matrixes, int length, int m[][M], int s[][M]) {
    int len = length-1;                          // 矩阵个数为 matrixes.size()-1
    for (int x = 1; x <= len; ++x) m[x][x] = 0;  // 长度为1的矩阵链乘：0
    for (int l = 2; l <= len; ++l) {             // 长度从 2 到 length-1 进行考察
        for (int i = 1; i <= len-l+1; ++i) {     // 考虑长度为l的A[i, j]， 个数为 length-l+1;
            int j = i+l-1;                       // eg: l=2,i=1,j=2,A[1,2];  l=length-1,i=1,j=length-1,A[1,length-1]
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k+1][j] + matrixes[i-1]*matrixes[k]*matrixes[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// 重构最优解
void printOptimalParens(int s[][M], int i, int j) {
    if (i==j)
        std::cout << "A" << i;
    else {
        std::cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j]+1, j);
        std::cout << ")";
    }
}
