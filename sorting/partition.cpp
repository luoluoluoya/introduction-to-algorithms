//
// Created by 张锐 on 2020/12/18.
//

/*
 * 元素划分子算法
 *  取轴点元素A[i], 将其就位于A的有序排列的正确位置
 */

// 策略：选择主元p，设置指针i，j分别指向不小于和不大于主元p的位置。当i=j时，主元p就位
template<typename T>
size_t partition_2(T A[], size_t b, size_t e) {
    size_t i = b, j = e-1; T p = A[i];      // 选取主元和首位指针
    while (j-i > 0) {
        while (i < j && p <= A[j]) --j;     // 此处策略存在的问题：元素相等时对输入序列的切分存在问题 (e-b-1) (0)
            if (i < j) A[i++] = A[j];
        while (i < j && A[i] <= p) ++i;
        if (i < j) A[j--] = A[i];
    }
    A[i] = p;
    return i;
}

template<typename T>
size_t partition_1(T A[], size_t b, size_t e) {
    size_t i = b, j = e-1; T p = A[i];
    while (j-i > 0) {
        while (i < j && p < A[j]) --j;
        if (i < j) A[i++] = A[j];
        while (i < j && A[i] < p) ++i;
        if (i < j) A[j--] = A[i];
    }
    A[i] = p;
    return i;
}

template<typename T>
size_t partition(T A[], size_t b, size_t e) {
    T r = A[e-1]; int j = b-1;
    for (int i = b; i < e-1; ++i) {
        if (A[i] <= r)
            std::swap(A[i], A[++j]);
    }
    std::swap(A[++j], A[e-1]);
    return j;
}

template<typename T>
size_t random_partition(T A[], size_t b, size_t e) {
    size_t r = b+random() % (e-b);
    std::swap(A[e-1], A[r]);
    return partition(A, b, e);
}
