//
// Created by 张锐 on 2020/12/17.
//

/*
 * 归并排序的归并策略为从左自右，分别对间隔为L的元素序列进行归并：L = 1 ~ n；
 *  L = 1; 也节点合并操作（最后一层节点合并）
 *  L = 2；（倒数第二节点合并）
 *  : : :
 *  : : :
 *
 * 假设初始序列含有n个元素，则可看成以各个元素为单位是n个有序子序列，每个子序列长度为1，然后两两归并，n个有序子序列就变成了n/2个有序子序列，再两两归并，...，如此重复，直到得到一个长度为n的有序序列为止。
 *
 * note1分析：
 *  循环终止时：
 *      lo >= size-2*step （剩余的元素不足以执行一次完整的合并）
 *
 * step 为上一次归并完成的步长。 已step为间隔的元素必定业已有序。
 *
 *      b         size-step     e
 *      [-----------｜----------)    ( 此区间的元素不足以执行一次完整的 [lo,lo+step),[lo+step, lo+2*step)的归并 )
 *  size-2*step     m         size
 *
 *  上图中:
 *      b 节点为当前归并时一次完成归并需要的起始位置
 *      m 节点到 e节点标记的元素为上轮归并中业已有序的位置
 *
 * 若 lo 节点处于 [b, m) 之间时，证明当前迭代有部分元素未就绪且并未在上轮迭代中就绪。 故将 [lo, size-step) [size-step, size)执行归并
 * 若 lo 节点处于 [m, e) 之间时，证明当前迭代有部分元素未就绪，但这部分元素在上轮迭代中已就绪。故直接跳过
 */

#include "merge_subroutine.cpp"

template<typename T>
void mergeSortIter(T input[], size_t size) {
    for (int step = 1; step < size; step*=2) {
        size_t lo = 0;
        while (lo+2*step <= size) {
            merge(input, lo, lo+step, lo+2*step);
            lo+=2*step;
        }
        if (lo < size - step)
            merge(input, lo, lo + step, size);
    }
}
