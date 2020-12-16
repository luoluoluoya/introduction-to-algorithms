//
// Created by 张锐 on 2020/12/16.
//


/*
 * 基数排序(Radix sort)
 *
 * 基数排序是一种非比较型整数排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。
 * 基数排序时对每一维进行调用子排序算法时要求这个子排序算法必须是稳定的。
 * 基数排序与直觉相反：它是按照从底位到高位的顺序排序的。
 *
 * 伪代码实现：
 *  radixCountingSort(A, d):
 *      for i=1 to d:
 *          do use a stable sort to sort array A on digit i.
 *
 * 复杂度分析：
 *  给定n个d位数，每一个数位可以取k种可能的值，如果所用计数排序作为底层排序，每次需要Θ(n+k)时间，一共需处理d遍，基数排序能以Θ(d(n+k))的时间完成。
 *
 * 若将关键字分成若干位方面，可以有一定的灵活性。
 *  给定n个b位数和任何正整数r<=b，如果采用的稳定排序需要Θ(d(n+k))时间，则radixCountingSort能在Θ((b/r)(n+2^r))时间内正确地对这些数进行排序。 (r将b位的数划分为 b/r 组，每组 r 位， 每组的可能取值位 2^r (设b可被r整除))
 *
 * 对于给定的n值和b值，如何选择r值使得最小化表达式(b/r)(n+2r)。如果 b< lgn，对于任何r<=b的值，都有(n+2^r)=Θ(n)，于是选择r=b，使计数排序的时间为Θ((b/b)(n+2b)) = Θ(n)。
 * 如果b>lgn，则选择r=lgn，可以给出在某一常数因子内的最佳时间：当r=lgn时，算法复杂度为Θ(bn/lgn)，当r增大到lgn以上时，分子 增大比分母r快，于是运行时间复杂度为Ω(bn/lgn)；反之当r减小到lgn以下的时候，b/r增大，而 n+ 仍然是Θ(n)。
 */

// 获取最大位数
int maxBit(int input[], size_t size) {
    int d = 1;
    for (int i = 0; i < size; ++i) {
        int c = 1;
        int v = input[i];
        while ((v = v/10))
            c++;
        if (c > d)
            d = c;
    }
    return d;
}

// 基数排序
void radixSort(int input[], const size_t& size) {
    int d = maxBit(input, size);
    int tmp[size], count[10];
    for (int i = 0, r=1; i < d; ++i, r*=10) {
        for (int l = 0; l < 10; ++l)            // 清空桶
            count[l] = 0;
        printf("\n");
        for (int j = 0; j < size; ++j) {        // 从低至高取第i位。并将其放入桶中
            int m = (input[j]/r) % 10;
            printf("%d, %d, %d |", input[j], r, m);
            count[m]++;
        }
        printf("\n");
        printf("\nstart printf the count: \n");
        for (int i1 = 0; i1 < 10; ++i1) {
            printf("%d ", count[i1]);
        }
        printf("\n");
        for (int k = 1; k < 10; ++k)            // 桶计数
            count[k]+=count[k-1];

        for (int n = size-1; n >= 0; --n) {     // 计数排序(稳定性至关重要)
            int p = (input[n]/r) % 10;
            tmp[count[p]-1] = input[n];
            count[p]--;
        }
        for (int c = 0; c  < size; ++c )        // 拷贝当前结果
            input[c] = tmp[c];
    }
}
