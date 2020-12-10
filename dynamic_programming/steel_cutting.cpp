//
// Created by 张锐 on 2020/12/10.
//


/**
钢条切割问题
切割问题是这样的：给定一段长度为n英寸的钢条和一个价格表 $p_i(i=1,2,3,...,n)$, 求切割钢条方案，使得销售收益 $r_n$ 最大。注意，如果长度为 n 英寸的钢条的价格 $A_n$ 足够大，最优解可能就是完全不需要切割。
一般地，对于$r_n = max(p_n, r1+r_{n-1}, r2+r_{n-2}, ..., r{n-1}+r_1) $, 我们可以用更短的钢条的最优切割收益来描述它：
第一个参数$p_n$对应不切割，直接出售长度为n英寸的钢条的方案。其他 n一1 个参数对应另外 n-1 种方案：对每个$r_i = p_i + p_{n-i}$, 首先将钢条切割为
长度为 pi 和 p{n-i} 的两段，接着 解这两段的最优切割收益切割方案,（每种方案的最优收益为两段的最优收益之和）。由于无法预知哪种方案会获得最优收益，
我们必须考察所有可能的 i ，选取其中收益最大者。如果直接出售原钢条会获得最大收益，我们当然可以选择不做任何切割。
注意到，为了求解规模为n的原问题，我们先求解形式完全一样，但规模更小的子问题。即当完成首次切割后，我们将两段钢条看成两个独立的钢条切割问题实例。我们通过组合两个相关子问题的最优解，并**在所有可能的两段切割方案中选取组合收益最大者，构成原问题的最优解**。
我们称钢条切割问题满足最优子结构(optimal substructure)性质：问题的最优解由相关子向题的最优解组合而成，而这些子问题可以独立求解。

除了上述求解方法外，钢条切割问题还存在一种相似的但更为简单的递归求解方法：我们将钢条从左边切割下长度为 i 的一段，只对右边剩下的长度为 n-i 的一段继续进行切割(递归求解)，
对左边的一段则不再进行切割。即问题分解的方式为：将长度为n的钢条分解为左边开始一段， 以及剩余部分继续分解的结果。这样，不做任何切割的方案就可以描述为：第一段的长度为n，收益为$p_n$，剩余部分长度为0,对应的收益为0。于是我们可以得到公式的简化版本：
        r(n) = max( p(i) + r(n-i) ); ( i in [0, n) )
        在此公式中，原问题的最优解只包含一个相关子问题(右端剩余部分)的解，而不是两个。
伪代码
```
 cutRod(p:价格表， n:钢条长度):
    if ( n<=0 ) return 0;
    q = INT_MIN;
    for i = 0 1 to n:
        q = std::max( q, p(i) + curRod(p, n-i) );
    return q;
```

CUT-ROD反复地用相同的参数值对自身进行 递归调用，即它反复求解相同的子间题。
对于长度为n的钢条，CUT-ROD显然考察了所有$2^{n-1}$种可能的切割方案。递归调用树中共有$2^{n-1}$个叶结点，每个叶结点对应一种可能的钢条切割方案。
对每条从根到叶的路径，路径上的标号给出了每次切割前右边剩余部分的长度(子问题的规模)。也就是说，标号给出了对应的切割点(从钢条右端测量)。
动态规划方法的思想如下所述。我们已经看到，朴素递归算法之所以效率很低，是因为它反复求解相同的子问题。因此，动态规划方法仔细安排求解顺序，对每个子问题只求解一次，
并将结果保存下来。如果随后再次需要此子问题的解，只需査找保存的结果，而不必重新计算。因 此，动态规划方法是付出额外的内存空间来节省计算时间，是典型的时空权衡(timomemory tradeoff)的例子。
而时间上的节省可能是非常巨大的：可能将一个指数时间的解转化为一个多 项式时间的解。如果子问题的数量是输入规模的多项式函数，而我们可以在多项式时间内求解出每个子问题，那么动态规划方法的总运行时间就是多项式阶的

自顶向下CUT-ROD过程的伪代码，加入了备忘机制
MEMOIZED-CUT-ROD(p:价格表, n:钢条长度)
    let r[0...n] be a new array
    for i = 0 to n
        r[i] = INT_MIN
    return MEMOIZED-CUT-ROD-AUX(p, n, r)

MEMOIZED-CUT-ROD-AUX(p:价格表, n:钢条长度, r:备忘表)
    if ( r[n] >= 0 )
        return r[n]
    if ( n == 0 )
        q = 0;
    else
        q = INT_MIN
    for i = 1 to n
        q = max ( q, p[i] + MEMOIZED-CUT-ROD-AUX(p, n-i, r) )
    r[n] = q
    return q

自底向上算法
BUTTOM-UP-CUT-ROD(p:价格表, n:钢条长度)
    let r[0...n] be a new array
            r[0] = 0
    for j = 1 to n
        q = INT_MIN
        for i = 1 to j
            q = max( q, p[i] + r[j-i] )
        r[j] = q
    retrun r[n]
 复杂度， 皆为$O(n^2)$

重构最优解：
EXTENDED-BUTTOM-UP-CUT-ROD(p:价格表, n:钢条长度)
    let r[0...n] and s[0...n] be new arrays
    r[0] = 0
    for j = 1 to n
        q = INT_MIN
        for i = 1 to j
            if q < p[i] + r[j-i]
                q = p[i] + r[j-i]
                s[j] = i
        r[j] = q
    retrun r and s

在求解规模为 j 的子问题时将第一段钢条的最优切割长度 i 保存在 s[j] 中
  PRINT-CUT-ROD-SOLUTION(p:价格表, n:钢条长度)
  	(r, s) = EXTENDED-BUTTOM-UP-CUT-ROD(p, n)
  	while n > 0
  		print s[n]
  		n - n-s[n]
*/


#include <vector>
#include <cassert>
#include <algorithm>

/*
    算法接受价格表 priceList 和长度length，长度为i的钢条的对应价格为: priceList[i-1];
    算法返回最大的拆分价格和位置记录信息

 */


// 普通分治算法
double cutRod(const std::vector<double>& priceList, const int& length) {
    assert(priceList.size() >= length);
    if (length <= 0)
        return 0;
    std::vector<int> places; places.resize(length+1);
    double q = INT_MIN;
    for (int i = 1; i <= length; ++i) {
        if ( q < priceList[i-1] + cutRod(priceList, length-i) ) {
            q = priceList[i-1] + cutRod(priceList, length-i);
            places[i-1] = i;
        }
    }
    return q;
}

// 自顶向下过程，加入了备忘机制
double memoizedCutRodAux(const std::vector<double>& priceList, std::vector<double>& memo, const int& length) {
    if (memo[length] >= 0)
        return memo[length];
    double q = (length > 0) ? INT_MIN : 0;
    for (int i = 1; i <= length; ++i) {
        q = std::max(q, priceList[i-1] + memoizedCutRodAux(priceList, memo, length-i));
    }
    memo[length] = q;
    return q;
}

double memoizedCutRod(const std::vector<double>& priceList, const int& length) {
    assert(priceList.size() >= length);
    std::vector<double> memo;
    memo.resize(length+1);
    for (int i = 0; i < length+1; ++i)
        memo[i] = INT_MIN;
    return memoizedCutRodAux(priceList, memo, length);
}

static void printCuttingPoint(const std::vector<int>& places, int length) {
    while (length > 0) {
        printf("%d ", places[length-1])   ;
        length = length - places[length-1];
    }
    printf("\n");
}

// 自底向上算法
double buttonCutRod(std::vector<double> priceList, const int& length) {
    assert(priceList.size() >= length);
    // 制表
    std::vector<double> memo;
    memo.resize(length+1);
    for (int i = 1; i < length+1; ++i)
        memo[i] = INT_MIN;
    memo[0] = 0;
    // 位置
    std::vector<int> places; places.resize(length);;
    // 求解
    for (int i = 1; i <= length; ++i) {
        double q = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            if ( q < priceList[i-1] + memo[i-j] ) {
                q = priceList[i-1] + memo[i-j];
                places[i-1] = j;
            }
        }
        memo[i] = q;
    }
    printCuttingPoint(places, length);
    return memo[length];
}

