/*
L3-043 门诊预约排队系统
分数 30
作者 陈越
单位 浙江大学

帮助医院开发一个门诊预约排队系统，基本需求如下：

系统内每天预设 n 个就诊时间段，每个时间段对应一个号（从 1 到 n）；
患者可以从列表中选择一个可选的时间段预约挂号；
一个号只能被一位患者预约；
医生在一个号对应的时间段内，只能接待一位患者；
当医生准备接待下一位患者时，如果当前时间段对应的挂号患者在等待，则接待之；如果该患者不是等待状态，则接待已经到达等待的患者中预约号最小的那位；
180 岁及以上老人就诊没有特别优先权，当然前提是老人家也挂号了。具体来说，当医生叫下一位患者就诊时，如果当前时间段对应的挂号患者没有在等待，且等待的队列中有 180 岁及以上的老人，则不能直接叫老人的号，无论老人挂的号是什么时间。如果有多位老人在等待，则按这些老人预约号的非升序处理。
医生必须接待完所有患者，才能下班。

输入格式：
输入第一行给出正整数 n（<=10^4），为就诊患者的人数。随后 n 行，按照前来就诊的时间顺序，每行给出一位患者的信息，格式如下：

就诊时间段 预约时间段 患者ID 患者年龄
其中 时间段 为区间 [1,n] 内的整数，患者ID 为由 5 个数字组成的字符串，患者年龄为区间 [1,200] 内的整数。
题目保证每个就诊时间段有唯一的一位患者预约，但多位患者可能同时到达医院候诊。

输出格式：
输出 n 行，按照实际就诊时间段的递增顺序，每行输出一位患者的实际就诊时间段和 ID，其间以 1 个空格分隔，行首尾不得有多余空格。

输入样例：
9
1 3 02891 28
1 8 81926 83
1 2 37610 80
2 1 37428 79
3 7 46381 13
6 6 73846 93
8 5 18264 37
8 9 57382 24
8 4 27364 88

输出样例：
1 37610
2 81926
3 02891
4 37428
5 46381
6 73846
8 27364
9 57382
10 18264
*/

#include<bits/stdc++.h>
using namespace std;

struct people{
    int t, yue, id, age;
};

int main() {
    int n;  cin>>n;
    vector<people> v(n);
    for(int i = 0; i < n; i++) {
        cin>>v[i].t>>v[i].yue>>v[i].id>>v[i].age;
    }
    auto cmp = [](const people& p1, const people& p2) {
        return p1.yue < p2.yue;
    };
    set<people, decltype(cmp)> old_set(cmp);  // 80+ VIP通道
    set<people, decltype(cmp)> normal_set(cmp); // 普通候选大厅
    int time = 1;
    int i = 0; // 指针
    int cnt = 0; // 已经看完病的人
    while(cnt < n) {
        // 快进时间
        if(old_set.empty() && normal_set.empty() && i < n && v[i].t > time) {
            time = v[i].t;
        }
        // 把到达的人推入队列
        while(i < n && v[i].t <= time) {
            normal_set.insert(v[i]);
            if(v[i].age >= 80) {
                old_set.insert(v[i]);
            }
            i++;
        }
        people picked;
        people dummy;  // 构造一个我们要找预约号的假人
        dummy.yue = time;
        // 核心叫号逻辑
        auto it = normal_set.find(dummy); // set目前只看预约时间排序，所以可以find
        if(it != normal_set.end()) {  // 找到预约本时间的，直接就诊
            picked = *it;
        } else if(!old_set.empty()) { // 没找到，直接从vip室按顺序选人
            picked = *old_set.begin();
        } else { // 都没有，从普通大厅选人
            picked = *normal_set.begin();
        }
        cout<<time<<" ";
        printf("%05d\n", picked.id);
        // 看病结束，清理队列
        normal_set.erase(picked);
        if(picked.age >= 80) {
            old_set.erase(picked);
        }
        time++;
        cnt++;
    }
    return 0;
}

// 【总结】
// 通用模板（事件模拟 + 有序候诊结构）：
// 1) 按到达时间顺序读入，维护当前时间 time，并在队列为空时快进到下一位到达时刻。
// 2) 将所有 arrival <= time 的患者放入候诊结构。
// 3) 先尝试匹配“预约号 == 当前时间段”的患者；若不存在，再按候诊规则选下一个人。
// 4) 输出当前 time 的就诊者，随后从候诊结构删除并 time++。
// 5) 重复直到全部患者完成。
// 复杂度常见为 O(n log n)（插入/删除/取最值都来自平衡树或堆）。
//
// 本题差异化补充：
// - 代码采用两个按预约号排序的 set：normal_set 与 old_set，体现不同候选池的选人策略。
// - 通过 dummy + set.find 实现“优先找预约号等于当前时间段”的分支。
// - 易错点：患者ID有前导0时要按固定5位输出；比较器只看 yue 时要保证题目数据不会冲突。
// - 题面文字中的年龄阈值与优先规则较特殊，编码时要严格对照题意逐条实现。
