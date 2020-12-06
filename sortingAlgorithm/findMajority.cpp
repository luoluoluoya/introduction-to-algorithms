//
// Created by 47302 on 2020/12/5.
//

/*
  众数：一个长度为len的数组，其中有个数出现的次数大于len/2，如何找出这个数。
  分析：
    对于给定的输入序列 L； 将其拆分为前缀 A 和后缀 L-A; 设 |A|=2m(m为任意自然数),其其中存在一元素x的数量为|m|;
    [A] [     L-A     ]
    当L中存在众数时，L-A 中必定存在众数：
        1. x为众数： 则 L-A 中非众数减少的数量等于众数较少的数量
        2. x为非众数，则 L-A 中非众数减少的数量大于众数较少的数量
 */

template<typename V>
V findMajority(V arr[], int s) {
    V majority;
    for (int i = 0, c = 0; i < s; ++i) {
        if (c == 0) {
            majority = arr[i]; c = 1;
        } else {
            majority == arr[i] ? c++ : c--;
        }
    }
    return majority;
}