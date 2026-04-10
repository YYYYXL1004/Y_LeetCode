/*
2129. 技能升级

问题描述
小蓝最近正在玩一款 RPG 游戏。他的角色一共有 N 个可以加攻击力的技能。
其中第 i 个技能首次升级可以提升 Ai 点攻击力，以后每次升级增加的点数都会减少 Bi。
在 ceil(Ai / Bi) 次之后，再升级该技能将不会改变攻击力。

现在小蓝可以总计升级 M 次技能，他可以任意选择升级的技能和次数。
请计算小蓝最多可以提高多少点攻击力。

输入格式
第一行包含两个整数 N 和 M。
以下 N 行每行包含两个整数 Ai 和 Bi。

输出格式
输出一行包含一个整数表示答案。

样例输入
3 6
10 5
9 2
8 1

样例输出
47

评测用例规模与约定
40%: 1 <= N, M <= 1000
60%: 1 <= N <= 1e4, 1 <= M <= 1e7
100%: 1 <= N <= 1e5, 1 <= M <= 2e9, 1 <= Ai, Bi <= 1e6
*/

#include <bits/stdc++.h>
using namespace std;

// 正解实现已按你的要求先删除，等你自己做出来后再添加。

// 你给的优先队列做法（60%）保留作对照：
#include<bits/stdc++.h>
using namespace std;
struct skill {
    long long a, b, count;
    skill(long long a, long long b, long long c) : a(a), b(b), count(c) {}
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, M;
    cin >> N >> M;

    auto cmp = [](const skill& s1, const skill& s2) {
        return s1.a < s2.a;
    };
    priority_queue<skill, vector<skill>, decltype(cmp)> pq(cmp);

    for (int i = 1; i <= N; i++) {
        long long a, b;
        cin >> a >> b;
        long long c = (a + b - 1) / b;
        pq.emplace(a, b, c);
    }

    long long sum = 0;
    while (M-- && !pq.empty()) {
        auto s = pq.top();
        pq.pop();
        sum += s.a;
        if (s.count > 1) {
            s.a = s.a - s.b;
            s.count--;
            pq.push(s);
        }
    }
    cout << sum;
    return 0;
}

// 你给的暴力做法（50%）保留作对照：
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//
//     int N, M;
//     cin >> N >> M;
//     priority_queue<int> pq;
//
//     for (int i = 1; i <= N; i++) {
//         int a, b;
//         cin >> a >> b;
//         // 原写法是 ceil(a / b)，整数场景应改成 (a + b - 1) / b
//         int c = (a + b - 1) / b;
//         for (int j = 1; j <= c; j++) {
//             pq.push(a);
//             a -= b;
//         }
//     }
//
//     long long sum = 0;
//     while (M-- && !pq.empty()) {
//         sum += pq.top();
//         pq.pop();
//     }
//
//     cout << sum;
//     return 0;
// }

/*
【总结】
1. 当前仅保留你的两版思路代码（50%暴力、60%优先队列）用于后续对照。
2. 等你自己完成正解后，再把最终实现与对应分析补回这里。
*/
