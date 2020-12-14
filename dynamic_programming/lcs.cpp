//
// Created by 张锐 on 2020/12/14.
//

/*
最长公共子序列，英文缩写为LCS（Longest Common Subsequence）。其定义是，一个序列 S ，如果分别是两个或多个已知序列的子序列，且是所有符合此条件序列中最长的，则 S 称为已知序列的最长公共子序列。
最长公共子序列（LCS）是一个在一个序列集合中（通常为两个序列）用来查找所有序列中最长子序列的问题。这与查找最长公共子串的问题不同的地方是：子序列不需要在原序列中占用连续的位置。而最长公共子串（要求连续）和最长公共子序列是不同的。
在计算机科学中，最长递增子序列是指，在一个给定的数值序列中，找到一个子序列，使得这个子序列元素的数值依次递增，并且这个子序列的长度尽可能地大。最长递增子序列中的元素在原序列中不一定是连续的。
    最长公共子串：在两个字符串中找到一个最长的公共子串，要求子串在原串中是连续的。
    最长公共子序列：在两个字符串中找到一个最长的公共子串，不要求子串在原串中是连续的。

输入：序列 X = {x1,x2,x3,....,xn}, 序列 Y = {y1,y2,y3 ..., ym};
输出：序列 R = {r1, r2 ... r_m}。 序列 R 为序列X，Y的最长公共子序列， 序列长度为 R.length;
蛮力算法
    算法描述：穷举X的所有子序列， 依据长度倒叙排列， 并在Y中依次查找子序列 Xi 是否为 Y 的子序列， 找到时终止并返回
    正确性：算法必定终止于某一公共子序列或不存在子序列时。对于找到的公共子序列，不可能存在更长者
    复杂度：O(2^n * m)
动态规划策略
步骤一：刻画最优解的结构特征
   1. 对于序列 X， Y， 若其末尾元素 X[n] == Y[m] 时:
    原问题分解为求解 LCS(X-X[n], Y-Y[m])
    LCS(X, Y) = LCS(X-X[n], Y-Y[m]) + 1; （最长公共子序列中必定存在两者的末元素）
   2. 对于序列 X， Y， 若其末尾元素 X[n] != Y[m] 时：
    原问题分解为 LCS(X, Y-Y[m])， LCS(X-X[n], Y) 两个具有共同性质的子问题
    LCS(X, Y) = max(LCS(X, Y-Y[m])， LCS(X-X[n], Y));（最长公共子序列中中末元素只可能从两者中选取一位进行考察）
   上述两种情况下，求解原问题最优解时分解而成的子问题的解必定为单独求解该子问题的时的最优解。若不是，可用剪切-粘贴法证明，原问题具有更优解。
步骤二：递归的定义最优解的值
    LCS(X, Y) = LCS(X-X[n], Y-Y[m]) + 1                 (X[n] == Y[m], n = |X|, m = |Y|)
              = max(LCS(X-X[n], Y), LCS(X, Y-Y[m]))     (X[n] != Y[m], n = |X|, m = |Y|)
步骤三：求解最优解值
自顶向下的伪代码实现
    LCS(X, Y, n, m, MEMO&, R&):   // 输入： X,Y：输入序列；n,m:|X|,|Y|,子序列长度； MEMO：备忘录（子问题的解）; R：选择路径信息； 输出： 当前子序列的最长公共子序列长度
        // 使用备忘录
        if (MEMO[n,m] >= 0)
            return R[n,m];
        if (n < 1 || m < 1) // 基本情况
            MEMO[n][m] = 0;
        else                // 递归情况
            if (X[n] == Y[m])
                R[n, m] = '左上';
                len =  LCS(X, Y, n-1, m-1, R);
            else
                len1 = LCS(X, Y, n-1, m, R);
                len2 = LCS(X, Y, n, m-1, R);
                if(len1 >= len2)
                    R[n,m] = '左';
                    len = len1;
                else
                    R[n,m] = '上';
                    len = len2;
            MEMO[n,m] = len;
        return len;
自底向上的伪码实现：
    LCS(X,Y,n,m, MEMO&, R&):
        for i = 1 to n:
            for j = 1 to n:         // 注意初始化备忘录中[0][y], [x][0]的值
                if (X[i] == Y[j])
                    R[i,j] = '左上';
                    len = MEMO[i-1, j-1] + 1;
                else
                    if (MEMO[i-1, j] >= MEMO[i, j-1])
                        R[i,j] = '左';
                        len = MEMO[i-1, j];
                    else
                        R[i,j] = '上';
                        len = MEMO[i, j-1];
                MEMO[i,j] = len;
        return MEMO[n,m];
步骤四：根据获取的信息重构最优解
    SEQ(R, X, Y, n, m):
        //基础情况
        if (n < 1 || m < 1)
        //递归情况
        if (R[n,m] = '左上'):
            SEQ(R, X, Y, n-1, m-1);
            printf(X[n]);
        elseif (R[n,m] = '左'):
            SEQ(R, X, Y, n-1, m);
        else:
            SEQ(R, X, Y, n, m-1);
*/

#define STR1LEN 6
#define STR2LEN 7
int MEMO[STR1LEN+1][STR2LEN+1];
char PATH[STR1LEN+1][STR2LEN+1];

int LCSR(const char* X, const char* Y, int n, int m) {
    // 使用备忘录
//    if (MEMO[n][m] >=0)
//        return MEMO[n][m];
    if (n < 1 || m < 1)     // 平凡的情况
        return MEMO[n][m] = 0;

    // 递归的情况
    if (X[n-1] == Y[m-1])  {
        PATH[n][m] = '\\';
        MEMO[n][m] = LCSR(X, Y, n-1, m-1) + 1;
    } else {
        int len1 = LCSR(X, Y, n-1, m);
        int len2 = LCSR(X, Y, n, m-1);
        if (len1 >= len2) {
            PATH[n][m] = '|';
            MEMO[n][m] = len1;
        } else {
            PATH[n][m] = '-';
            MEMO[n][m] = len2;
        }
    }
    return MEMO[n][m];
}

int LCS(const char* X, const char* Y, int n, int m) {
    for (int i = 1; i < n; ++i)
        MEMO[i][0] = 0;
    for (int i = 1; i < m; ++i)
        MEMO[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (X[i-1] == Y[j-1]) {
                MEMO[i][j] = MEMO[i-1][j-1] + 1;
                PATH[i][j] = '\\';
            } else if (MEMO[i-1][j] >= MEMO[i][j-1]) {
                MEMO[i][j] = MEMO[i-1][j];
                PATH[i][j] = '|';
            } else {
                MEMO[i][j] = MEMO[i][j-1];
                PATH[i][j] = '-';
            }
        }
    }
    return MEMO[n][m];
}

void printLCS(const char *X, int n, int m) {
    if (n < 1 || m < 1)
        return ;
    if (PATH[n][m] == '\\') {
        printLCS( X, n-1, m-1);
        std::cout << X[n-1] << " ";
    } else if (PATH[n][m] == '|')
        printLCS(X, n-1, m);
    else
        printLCS(X, n, m-1);
}
