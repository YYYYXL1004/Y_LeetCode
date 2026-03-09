/*
L2-025 分而治之
分数 25
作者 陈越
单位 浙江大学

分而治之，各个击破是兵家常用的策略之一。在战争中，我们希望首先攻下敌方的部分城市，使其剩余的城市变成孤立无援，
然后再分头各个击破。为此参谋部提供了若干打击方案。本题就请你编写程序，判断每个方案的可行性。

输入格式：
输入在第一行给出两个正整数 N 和 M（均不超过10 000），分别为敌方城市个数（于是默认城市从 1 到 N 编号）
和连接两城市的通路条数。随后 M 行，每行给出一条通路所连接的两个城市的编号，其间以一个空格分隔。
在城市信息之后给出参谋部的系列方案，即一个正整数 K （≤ 100）和随后的 K 行方案，每行按以下格式给出：
Np v[1] v[2] ... v[Np]
其中 Np 是该方案中计划攻下的城市数量，后面的系列 v[i] 是计划攻下的城市编号。

输出格式：
对每一套方案，如果可行就输出YES，否则输出NO。

输入样例：
10 11
8 7
6 8
4 5
8 4
8 1
1 2
1 4
9 8
9 1
1 10
2 4
5
4 10 3 8 4
6 6 1 7 5 4 9
3 1 8 4
2 2 8
7 9 8 7 6 5 4 2

输出样例：
NO
YES
YES
NO
NO
*/

#include<bits/stdc++.h>

using namespace std;

#define debug(x) cout << #x << " = " << x << endl

int parent[10005];
bool lost[10005];
int N, M;

int find(int x) {
    if(parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void _union(int p, int q) {
    int rp = find(p);
    int rq = find(q);
    if(rp == rq) return;
    parent[rq] = rp;
}

void clear() {
    for(int i = 1; i <= N; i++) {
        parent[i] = i;
        lost[i] = false;
    }
}

int _count() {
    set<int> roots;
    for(int i = 1; i <= N; i++) {
        if(!lost[i]) roots.insert(find(i));
    }
    return roots.size();
}

int main() {
    cin >> N >> M;
    clear();

    vector<pair<int, int>> edges;
    while(M--) {  // 记录所有边
        int p, q;
        cin >> p >> q;
        edges.emplace_back(p, q);
    }

    int K;
    cin >> K;

    while(K--) {
        int np;
        cin >> np;
        for(int i = 1; i <= np; i++) {
            int x;
            cin >> x;
            lost[x] = true;
        }

        for(auto& edge : edges) {
            if(!lost[edge.first] && !lost[edge.second]) {  // 都没被摧毁
                _union(edge.first, edge.second);
            }
        }

        if(_count() == N - np) cout << "YES" << endl;  // 如果剩下的都是独立的，返回YES
        else cout << "NO" << endl;

        clear();  // 重置状态，处理下一个方案
    }

    return 0;
}

/*
总结：
本题考察并查集判断图的连通性，与L2-013红色警报类似，但更简单。

1. 题目分析：
   - 判断方案是否可行 = 攻下指定城市后，剩余城市是否全部孤立
   - 剩余城市全部孤立 = 每个剩余城市自成一个连通分量
   - 即：连通分量数 == 剩余城市数

2. 解题思路：
   - 标记计划攻下的城市为lost
   - 重建并查集，只连接两端都未被攻占的边
   - 统计剩余城市的连通分量数
   - 若连通分量数 == 剩余城市数(N - np)，说明全部孤立，方案可行

3. 核心判断：
   - _count() == N - np → YES（所有剩余城市孤立）
   - _count() < N - np → NO（存在连通的城市对）

4. 与L2-013的区别：
   - L2-013：判断连通分量是否增加（动态过程）
   - L2-025：判断剩余城市是否全部孤立（静态状态）
   - L2-025更简单，只需判断最终状态

5. 易错点：
   - 城市编号从1开始，不是从0
   - 每个方案处理后要clear()重置状态
   - lost数组要用bool类型，int可能出问题

6. 时间复杂度：
   - O(K * (N + M))，每个方案需要重置并查集和遍历所有边
*/
