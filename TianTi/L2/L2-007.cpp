/*
L2-007 家庭房产
分数 25
作者 陈越
单位 浙江大学

给定每个人的家庭成员和其自己名下的房产，请你统计出每个家庭的人口数、人均房产面积及房产套数。

输入格式：
输入第一行给出一个正整数N（≤1000），随后N行，每行按下列格式给出一个人的房产：
编号 父 母 k 孩子1 ... 孩子k 房产套数 总面积
其中编号是每个人独有的一个4位数的编号；父和母分别是该编号对应的这个人的父母的编号（如果已经过世，则显示-1）；
k（0≤k≤5）是该人的子女的个数；孩子i是其子女的编号。

输出格式：
首先在第一行输出家庭个数（所有有亲属关系的人都属于同一个家庭）。随后按下列格式输出每个家庭的信息：
家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积
其中人均值要求保留小数点后3位。家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出。

输入样例：
10
6666 5551 5552 1 7777 1 100
1234 5678 9012 1 0002 2 300
8888 -1 -1 0 1 1000
2468 0001 0004 1 2222 1 500
7777 6666 -1 0 2 300
3721 -1 -1 1 2333 2 150
9012 -1 -1 3 1236 1235 1234 1 100
1235 5678 9012 0 1 50
2222 1236 2468 2 6661 6662 1 300
2333 -1 3721 3 6661 6662 6663 1 100

输出样例：
3
8888 1 1.000 1000.000
0001 15 0.600 100.000
5551 4 0.750 100.000

*/

#include<bits/stdc++.h>
using namespace std;

int parent[10005], cnt[10005], sqcnt[10005];
bool exist[10005];

int find(int x) {
    if(parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void _union(int p, int q) {
    int rp = find(p), rq = find(q);
    if(rp != rq) parent[rp] = rq;
}

int main() {
    int N;
    cin >> N;

    for(int i = 0; i < 10005; i++) parent[i] = i;

    while(N--) {
        int id, fa, ma, k, nums, sq;
        cin >> id >> fa >> ma >> k;
        exist[id] = true;  // 关键：标记本人存在

        if(fa != -1) { exist[fa] = true; _union(id, fa); }
        if(ma != -1) { exist[ma] = true; _union(id, ma); }

        while(k--) {
            int ch;
            cin >> ch;
            exist[ch] = true;
            _union(id, ch);
        }

        cin >> nums >> sq;
        cnt[id] = nums;
        sqcnt[id] = sq;
    }

    // 按根节点分组统计
    map<int, vector<int>> mp;
    for(int i = 0; i < 10005; i++) {
        if(exist[i]) mp[find(i)].push_back(i);
    }

    // 统计结果
    struct Family {
        int minId, cnt;
        double avgCnt, avgSq;
    };
    vector<Family> ans;

    for(auto& [root, v] : mp) {
        Family f;
        f.cnt = v.size();
        f.minId = *min_element(v.begin(), v.end());

        int totalCnt = 0, totalSq = 0;
        for(int id : v) {
            totalCnt += cnt[id];
            totalSq += sqcnt[id];
        }
        f.avgCnt = (double)totalCnt / f.cnt;
        f.avgSq = (double)totalSq / f.cnt;
        ans.push_back(f);
    }

    // 排序
    sort(ans.begin(), ans.end(), [](Family& a, Family& b) {
        if(a.avgSq != b.avgSq) return a.avgSq > b.avgSq;
        return a.minId < b.minId;
    });

    cout << ans.size() << endl;
    for(auto& f : ans) {
        printf("%04d %d %.3f %.3f\n", f.minId, f.cnt, f.avgCnt, f.avgSq);
    }

    return 0;
}

// 【总结】
// 并查集+分组统计的经典题目

// 核心思路：先合并，后统计
// 1. 阶段1（输入）：合并家庭 + 标记存在 + 记录个人房产
// 2. 阶段2（分组）：遍历所有人，按 find(i) 分组
// 3. 阶段3（输出）：计算人均 → 排序 → 输出

// 关键点：
// - exist[] 标记所有出现的人（包括本人、父母、子女）
// - 房产信息存在个人身上，统计时再累加
// - 用 map<int, vector<int>> 按 find(i) 分组，同一组是一家人
// - 输出编号用 %04d 补零

// 易错点：
// - 忘记标记 exist[id]（本人也要标记）
// - 根节点不一定是家庭成员的最小编号，需要额外统计
// - 有些人的房产信息为 0（只作为父母/子女出现），但仍属于家庭