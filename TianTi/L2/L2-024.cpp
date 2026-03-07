/*
L2-024 部落
分数 25
作者 陈越
单位 浙江大学

在一个社区里，每个人都有自己的小圈子，还可能同时属于很多不同的朋友圈。
我们认为朋友的朋友都算在一个部落里，于是要请你统计一下，在一个给定社区中，
到底有多少个互不相交的部落？并且检查任意两个人是否属于同一个部落。

输入格式：
输入在第一行给出一个正整数N（≤10^4），是已知小圈子的个数。
随后N行，每行按下列格式给出一个小圈子里的人：
K P[1] P[2] ⋯ P[K]
其中K是小圈子里的人数，P[i]（i=1,⋯,K）是小圈子里每个人的编号。
这里所有人的编号从1开始连续编号，最大编号不会超过10^4。

之后一行给出一个非负整数Q（≤10^4），是查询次数。
随后Q行，每行给出一对被查询的人的编号。

输出格式：
首先在一行中输出这个社区的总人数、以及互不相交的部落的个数。
随后对每一次查询，如果他们属于同一个部落，则在一行中输出Y，否则输出N。

输入样例：
4
3 10 1 2
2 3 4
4 1 5 7 8
3 9 6 4
2
10 5
3 7

输出样例：
10 2
Y
N
*/

#include<bits/stdc++.h>
using namespace std;

vector<int> parent,rk;

int find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void _union(int p, int q) {
    int rq = find(q), rp = find(p);
    if(rk[rq] < rk[rp]) parent[rq] = rp;
    else if(rk[rp] < rk[rq]) parent[rp] = rq;
    else {
        parent[rq] = rp;
        rk[rp]++;
    }
}

int main() {
    int N; cin>>N;
    parent.resize(10005);
    for(int i = 1; i <= 10000; i++) parent[i] = i;
    rk.resize(10005, 1);

    int n_max = 0;
    set<int> ans;

    while(N--) {
        int K, root; cin>>K;
        cin>>root; K--;
        n_max = max(n_max, root);
        while(K--) {
            int x; cin>>x;
            n_max = max(n_max, x);
            _union(root, x);
        }
    }

    for(int i = 1; i <= n_max; i++) ans.insert(find(i));
    cout<<n_max<<" "<<ans.size()<<endl;

    int Q; cin>>Q;
    while(Q--) {
        int x, y;
        cin>>x>>y;
        if(find(x) == find(y)) cout<<"Y"<<endl;
        else cout<<"N"<<endl;
    }

    return 0;
}

// 【总结】
// 并查集基础应用：连通分量计数 + 连通性查询

// 核心思路：
// 1. 合并：每个小圈子取第一个人作为 root，其他人跟 root 合并
// 2. 计数：遍历 1~n_max，用 set 统计不同根节点数量（部落数）
// 3. 查询：find(x) == find(y) 判断是否同部落

// 关键点：
// - 总人数 = 出现过的最大编号 n_max
// - 部落数 = 不同根节点的数量（用 set 去重）
// - 每个小圈子内部都要合并，不是只合并第一个和最后一个

// 易错点：
// - 初始化 parent 从 1 开始还是 0 开始要看题目编号范围
// - 合并时取小圈子的第一个人作为 root，避免遗漏