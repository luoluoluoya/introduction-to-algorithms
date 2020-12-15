//
// Created by 张锐 on 2020/12/15.
//

/*
活动选择问题：
假定一个有n个活动(activity)的集合S={a1,a2,....,an}，这些活动使用同一个资源（例如同一个阶梯教室），而这个资源在某个时刻只能供一个活动使用。每个活动ai都有一个
开始时间si和一个结束时间fi，其中0<=si<fi<正无穷。如果被选中，任务ai发生在半开时间区间[si,fi)期间。如果两个活动ai和aj满足[si,fi)和[sj,fj)不重叠，
则称它们是兼容的。也就说，若si>=fj或sj>=fi，则ai和aj是兼容的。在活动选择问题中，我们希望选出一个最大兼容活动集。

动态规划策略
步骤一：刻画最优解的结构特征
    Sij表示在ai结束之后，在aj开始之前的活动的集合。Aij表示Sij的一个最大相互兼容的活动子集。那么只要Sij非空，则Aij至少会包含一个活动，假设为ak。那么可以将Aij分解为：
        Aij = Aik+ak+Akj。假设Cij为Aij的大小，那么有Cij=cik+ckj+1。
    此时，我们只需要考察所有可能的k，以取得当前活动的最大兼容的活动集。
    当选择某一活动 ak 进行考察时： 原问题分解为两个性质相同的子问题，依据剪切粘贴策略可知，子问题必定为最优解。故原问题的最优解依赖于子问题的最优解，且子问题可独立求解。
步骤二：递归的定义最优解的值
    Aij = max(Aik + ak + Akj),(k=i to j); (Sij不为空)
        = 0; (Sij为空)
步骤三：求解最优解值
 自顶向下
    ActivitySelector(S, i, j, MEMO, Path):
        if (MEMO[i, j] >= 0)
            return MEMO[i, j];
        MEMO[i, j] = 0;
        if Sij 不为空：
            for k=i+1 to j:
                if (MEMO[i, j] < MEMO[i,k]+MEMO[k,j]+1)
                    MEMO[i, j] = MEMO[i,k]+MEMO[k,j]+1;
                    Path[i][j] = k;
        return MEMO[i, j];
 自底向上
    ActivitySelector(S, i, j):
        MEMO[i+1][j+1];
        Path[i+1][j+1];
        for x=1 to i+1:
            MEMO[i,0] = 0;
        for x=1 to j+1:
            MEMO[0, j] = 0;
        for l=1 to j-i:
            for z=1 to i:
                m = z+l-1;
                MEMO[z, m] = 0;
                for k=z+1 to m:
                    if (MEMO[i, j] < MEMO[i,z]+MEMO[z,m]+1)
                        MEMO[i, j] = MEMO[i,z]+MEMO[z,m]+1;
                        Path[z][m] = k;
        return MEMO[i, j];
步骤四：根据获取的信息重构最优解
    printSelect(Path, i, j):
        if (i == j)
            return;
        else
            k = Path[i, j];
            printSelect(Path, i, k);
            print "{Ak}";
            printSelect(Path, k, j);
*/

#include <string>
#include <algorithm>
#define ACTIVITY_SIZE 11
int MEMO[ACTIVITY_SIZE+2][ACTIVITY_SIZE+2] = {0};   // 序列中插入虚拟的头尾节点
int PATH[ACTIVITY_SIZE+2][ACTIVITY_SIZE+2] = {0};   // 序列中插入虚拟的头尾节点

struct Activity {
    int id;
    int sTime, fTime;
    Activity() {}
    Activity(int i, int s, int f): id(i), sTime(s), fTime(f) {}
    void toString() const { std::cout << "Activity Id: " << id << "; sTime:" << sTime << "; fTime:" << fTime << std::endl; }
};

// 依据活动时间倒叙进行排列
bool compare(const Activity& a1, const Activity& a2) {
    return a1.fTime <= a2.fTime;
}

// 设置头尾节点
Activity* setHeadAndTail(Activity activities[], size_t size) {
    Activity* newAct = new Activity[size+2];
    newAct[0] = {INT_MIN, INT_MIN, INT_MIN};
    for (int i = 1; i <= size; ++i)
        newAct[i] = activities[i-1];
    newAct[size+1] = {INT_MAX, INT_MAX, INT_MAX};
    return newAct;
}

// 活动k是否与Sij相互兼容
bool isCompatible(Activity* activities, int i, int j, int k) {
    return activities[i].fTime <= activities[k].sTime && activities[k].fTime <= activities[j].sTime;
}

int activitySelector(Activity input[], size_t size) {
    Activity* activities = setHeadAndTail(input, size);
    std::sort(activities, activities+size+2, compare);
    for (int l = 2; l <= size+1; ++l) {
        for (int i = 0; i <= size; ++i) {
            int j = i + l;
            if (j > size+1) continue;
            if (activities[i].fTime > activities[j].sTime) continue;    // 活动i，j不兼容。    放弃考察
            // 考察 Sij 的所有划分
            for (int k = i+1; k < j; ++k) {
                if (!isCompatible(activities, i, j, k)) continue;       // ak不是 Sij 的兼容活动
                int e = MEMO[i][k] + MEMO[k][j] + 1;
                if (MEMO[i][j] < e) {
                    PATH[i][j] = k;
                    printf("PATH[%d][%d]=%d\n", i, j, k);
                    MEMO[i][j] = e;
                }
            }
        }
    }
    delete [] activities;
    return MEMO[0][size+1];
}

void printSelect(int i, int j) {
    int k = PATH[i][k];
    if (k != 0) {
        printSelect(i, k);
        printf("Activity%d ", k);
        printSelect(k, j);
    }
}

/*
 * 原本的思路：按照动态规划的方法来求，先求子问题：将Sij的一个最大兼容活动集合设为Aij，于是Aij至少包含一个活动ak，则：
 * 可以将Aij划分为子问题：Aij=Aik+ak+Akj
 *
 * 但是我们一开始不能知道哪一个k能够使得ak一定在最大兼容活动集Aij中，于是一般的需要从i~j便利所有的k的可能取值，来找这个ak。
 *
 * 上面是动态规划的思路；但是对于贪心算法而言，这里ak不去遍历，而只是去寻找第一个结束的活动，也就是a1。这里可以证明，a1一定是在
 * Sij的某一个最大兼容活动集Aij中。证明方法：
 *
 * 假设Aij是Sij的某个最大兼容活动集，假设Aij中，最早结束的活动是an，分两种情况：
 * ①如果an=a1，则得证
 * ②如果an不等于a1，则an的结束时间一定会晚于a1的结束时间，我们用a1去替换Aij中的an，于是得到A`，由于a1比an结束的早，而Aij中的其他活动
 * 都比an的结束时间开始的要晚，所以A`中的其他活动 都与a1不想交，所以A`中的所有活动是兼容的，所以A`也是Sij的一个最大兼容活动集。
 */
int greedyActivitySelector(Activity *activity, size_t size) {
    std::sort(activity, activity+size, compare);
    int max = 1;
    Activity b = activity[0];                 // 每一个曾替换 b 的活动都存在于最大相互兼容的活动子集中
    for (int i = 1; i < size; ++i) {
        if (b.fTime <= activity[i].sTime) {
            b = activity[i];
            max++;
        }
    }
    return max;
}
