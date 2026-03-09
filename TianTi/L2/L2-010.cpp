/*
L2-010 排座位
分数 25
作者 陈越
单位 浙江大学

布置宴席最微妙的事情，就是给前来参宴的各位宾客安排座位。无论如何，总不能把两个死对头排到同一张宴会桌旁！
这个艰巨任务现在就交给你，对任何一对客人，请编写程序告诉主人他们是否能被安排同席。

输入格式：
输入第一行给出3个正整数：N（≤100），即前来参宴的宾客总人数，则这些人从1到N编号；
M为已知两两宾客之间的关系数；K为查询的条数。随后M行，每行给出一对宾客之间的关系，
格式为：宾客1 宾客2 关系，其中关系为1表示是朋友，-1表示是死对头。
注意两个人不可能既是朋友又是敌人。最后K行，每行给出一对需要查询的宾客编号。

这里假设朋友的朋友也是朋友。但敌人的敌人并不一定就是朋友，朋友的敌人也不一定是敌人。
只有单纯直接的敌对关系才是绝对不能同席的。

输出格式：
对每个查询输出一行结果：
- 如果两位宾客之间是朋友，且没有敌对关系，则输出No problem；
- 如果他们之间并不是朋友，但也不敌对，则输出OK；
- 如果他们之间有敌对，然而也有共同的朋友，则输出OK but...；
- 如果他们之间只有敌对关系，则输出No way。

输入样例：
7 8 4
5 6 1
2 7 -1
1 3 1
3 4 1
6 7 -1
1 2 1
1 4 1
2 3 -1
3 4
5 7
2 3
7 2

输出样例：
No problem
OK
OK but...
No way
*/

#include<bits/stdc++.h>

using namespace std;

int parent[105];  // 朋友并查集

map<int, set<int>> di; // 记录直接敌人的关系

int find(int x) {
    if(parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
} 

void _union(int p, int q) { 
    int rp = find(p), rq = find(q);
    if(rp == rq) return;
    parent[rq] = rp;
}

int main() {
    int N, M, K;
    cin>>N>>M>>K;
    
    for(int i = 1; i <= N; i++) {
        parent[i] = i;
    }
    
    while(M--) {
        int p, q, re;
        cin>>p>>q>>re;
        if(re == 1) _union(p, q);
        else {
            di[p].insert(q);
            di[q].insert(p);
        }
    }
    
    while(K--) {
        int p, q;
        cin>>p>>q;
        int paP = find(p), paQ = find(q);
        bool isdi = false;
        if(di[p].count(q)) isdi = true;
        
        if(paP == paQ && !isdi) cout<<"No problem"<<endl;
        else if(paP != paQ && !isdi) cout<<"OK"<<endl;
        else if(paP == paQ && isdi) cout<<"OK but..."<<endl;
        else if(paP != paQ && isdi) cout<<"No way"<<endl;
    }
    
    return 0;
}

/*
总结：
本题考察并查集的应用，关键点如下：

1. 题目分析：
   - 朋友关系具有传递性（朋友的朋友也是朋友），适合用并查集维护
   - 敌对关系不具有传递性，需要单独记录直接敌对关系
   - 查询时需要判断四种情况：是否朋友 + 是否敌对

2. 解题思路：
   - 使用并查集维护朋友关系（关系为1时合并）
   - 使用map<int, set<int>>记录双向的直接敌对关系（关系为-1时添加）
   - 查询时同时判断两个条件：是否在同一集合（朋友）+ 是否有直接敌对关系

3. 四种输出情况：
   - No problem：是朋友（同一集合）且无直接敌对
   - OK：非朋友也无敌对
   - OK but...：有共同朋友（同一集合）但有直接敌对关系
   - No way：非朋友且有直接敌对关系

4. 易错点：
   - 敌对关系要双向记录，因为查询可能是任意顺序
   - 只有"直接敌对"才算敌对，敌人的敌人不一定是朋友
*/
