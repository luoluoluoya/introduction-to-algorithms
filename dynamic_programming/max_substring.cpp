//
// Created by 张锐 on 2020/12/15.
//

/*
最大公共子串 (串一定是连续的，序列可以是不连续的)
有两个字符串，这两个字符串可能会存在公共的部分.最大公共子串需要求解其子串中最长的部分。

求解思路：
 对于给定的字符串 X,Y, 将其元素组成二维矩阵，如果两个子串相同，那么矩阵的对角线全都是1。
 如字符串"abcdef" 和字符串"defg",这两个字符串之间有共同的字符串，“d”,“e”,“f”,“de”,“ef”,“def” 等。最长的公共子串就是"def"。
        a b c d e f
     d  0 0 0 1 0 0
     e  0 0 0 0 1 0
     f  0 0 0 0 0 1
     g  0 0 0 0 0 0
蛮力求解：查看所有的对角线，找出其中连续为1的长度最长者。
    1。构造如上矩阵
    2。遍历矩阵，获取对角线最长者
动态规划策略
    设 dp[i,j] 表示以X[i],Y[j]结尾的最大公共子串。 则对X，Y的最大公共子串求解问题则子需要考虑所有的i，j，选取其中最大者。
步骤1：刻画一个最优解的结构特征
    dp[i, j]的解取决于 X[i]是否等于Y[j],以及dp[i-1,j-1]的值。若X[i]!= Y[j]时，dp[i,j]=0. 若X[i]== Y[j]时, 原问题分解为一个性质相同的子问题dp[i-1,j-1],且该问题的解为对其进行单独求解时的最优解。（剪切-粘贴法）
    故dp[i,j]问题具有最优子结构且子问题可独立求解
步骤2：递归地定义最优解的值
    递推公式：
        dp[i,j] = 0 (A[i] != A[j])
                = dp[i-1, j-1]+1 (A[i] == A[j])
        将上述矩阵进行转化。
            a b c d e f
         d  0 0 0 1 0 0
         e  0 0 0 0 2 0
         f  0 0 0 0 0 3
         g  0 0 0 0 0 0
步骤3：计算最优解的值
伪代码实现：
    maxSub(X, Y， Memo&):
        for k=1 to n:
            Memo[k][0] = 0;
        for k=1 to m:
            Memo[0][k] = 0;
        n = |X|; m = |Y|;
        for i=0 to n:
            for j=0 to m:
                if (X[i]==Y[j])
                    Memo[i,j] = Memo[i,j]+1;
                else
                    Memo[i,j] = 0;
复杂度：O(n*m)
 */

#include <utility>

int maxSub(const char* X, const char* Y, size_t n, size_t m) {
    int memo[n+1][m+1];                         // Memo可以只保存两行即可. 此处未记录出
    std::pair<int, int> end = {0, 0};   // 记录最大公共子串匹配的位置
    for (int i = 0; i < n+1; ++i)
        memo[i][0] = 0;
    for (int i = 1; i < m+1; ++i)
        memo[0][i] = 0;
    int max = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            memo[i][j] = X[i-1] == Y[j-1] ? memo[i][j] = memo[i-1][j-1] + 1 : memo[i][j] = 0;
            if (memo[i][j] > max) {
                max = memo[i][j];
                end = {i, j};
            }
        }
    return max;
}

//    const char* str1 = "acbcbcef";
//    const char* str2 = "abcbced";
// MEMO:
//0 0 0 0 0 0 0 0
//0 1 0 0 0 0 0 0
//0 0 0 1 0 1 0 0
//0 0 1 0 2 0 0 0
//0 0 0 2 0 3 0 0
//0 0 1 0 3 0 0 0
//0 0 0 2 0 4 0 0
//0 0 0 0 0 0 5 0
//0 0 0 0 0 0 0 0
//maxSub: e c b c b
//output: 5
