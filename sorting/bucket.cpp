//
// Created by 张锐 on 2020/12/16.
//

/*
 * 桶排序
 * 桶排序假设输入数据服从均匀分布，平均情况下它的时间代价为O(n),与计数排序类似，因为对输入数据作了某种假设，桶排序的速度也很快。
 * 具体来说，计数排序假设输入数据都属于一个小区间内的整数，而桶排序则假设输入是由一个随机过程产生，该过程将元素均匀、独立地分布在 [0，1) 区间上。
 *
 * 算法思路
 *  1. 桶排序将 [0，1) 区间划分为 n 个相同大小的子区间，称之为桶。然后将输入序列中的n个元素映射到桶中， 因为假设输入数据服从均匀分布，故不会存在很多元素位于一个桶。
 *  2. 对各桶中元素执行排序
 *  3. 依次输出桶中元素
 *
 * 伪代码实现
 *  bucketSort(A, size):
 *      buckets[size];
 *      for i=0 to size:
 *          初始化 buckets[i] 为空链表
 *      for i=0 to size:
 *          buckets[ 下整(n*A[i]) ].insert( A[i] );
 *      for i=0 to size:
 *          排序 buckets[i]
 *      依次输出 buckets[0 ~ size] 中的元素
 */

#include<malloc/malloc.h>

typedef struct node {
    int data;
    struct node *next;
    node(int d = INT_MIN, node *n = nullptr) : data(d), next(n) {}
} KeyNode;

void bucketSort(int input[], int size, int bucketSize, int divisor) {
    KeyNode **bucket = (KeyNode **) malloc(bucketSize * sizeof(KeyNode *));
    for (int i = 0; i < bucketSize; i++) {
        bucket[i] = (KeyNode *) malloc(sizeof(KeyNode));
        bucket[i]->data = 0;
        bucket[i]->next = NULL;
    }
    for (int j = 0; j < size; j++) {
        KeyNode *node = (KeyNode *) malloc(sizeof(KeyNode));
        node->data = input[j];
        node->next = NULL;
        int index = input[j] / divisor;
        KeyNode *p = bucket[index];
        if (p->data == 0)
            bucket[index]->next = node;
        else {
            while ((p->next != NULL) && (p->next->data <= node->data))
                p = p->next;
            node->next = p->next;
            p->next = node;
        }
        (bucket[index]->data)++;
    }
    for (int i = 0, j=0; i < bucketSize; i++) {
        for (KeyNode *k = bucket[i]->next; k != NULL; k = k->next)
            input[j++] = k->data;
    }
    free(bucket);
}
