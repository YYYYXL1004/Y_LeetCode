/*
L2-013 红色警报
分数 25
作者 陈越
单位 浙江大学

战争中保持各个城市间的连通性非常重要。本题要求你编写一个报警程序，当失去一个城市导致国家被分裂为多个无法连通的区域时，
就发出红色警报。注意：若该国本来就不完全连通，是分裂的k个区域，而失去一个城市并不改变其他城市之间的连通性，则不要发出警报。

输入格式：
输入在第一行给出两个整数N（0 < N ≤ 500）和M（≤ 5000），分别为城市个数（于是默认城市从0到N-1编号）和连接两城市的通路条数。
随后M行，每行给出一条通路所连接的两个城市的编号，其间以1个空格分隔。在城市信息之后给出被攻占的信息，
即一个正整数K和随后的K个被攻占的城市的编号。
注意：输入保证给出的被攻占的城市编号都是合法的且无重复，但并不保证给出的通路没有重复。

输出格式：
对每个被攻占的城市，如果它会改变整个国家的连通性，则输出Red Alert: City k is lost!，其中k是该城市的编号；
否则只输出City k is lost.即可。如果该国失去了最后一个城市，则增加一行输出Game Over.。

输入样例：
5 4
0 1
1 3
3 0
0 4
5
1 2 0 4 3

输出样例：
City 1 is lost.
City 2 is lost.
Red Alert: City 0 is lost!
City 4 is lost.
City 3 is lost.
Game Over.
*/

#include<bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x << " = " << x << endl

int parent[505];
bool lost[505]; // 标记城市是否被攻占

int find(int x) {
    if(parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void _union(int p, int q) {
    int rp = find(p), rq = find(q);
    if(rp == rq) return;
    parent[rq] = rp;
}

// 计算目前连通分量数量
int _count(int n) {
    set<int> roots;
    for(int i = 0; i < n; i++) {
        if(!lost[i]) roots.insert(find(i));
    }
    return roots.size();
}

int main() {
    int N, M;
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        parent[i] = i;
        lost[i] = false;
    }

    vector<pair<int, int>> edges; // 保存所有边

    while(M--) {
        int p, q;
        cin >> p >> q;
        edges.emplace_back(p, q);
        _union(p, q);
    }

    int preCount = _count(N); // 记录攻占前的连通分量数

    int K;
    cin >> K;

    for(int i = 1; i <= K; i++) {
        int city;
        cin >> city;
        lost[city] = true;

        for(int j = 0; j < N; j++) parent[j] = j; // 重置并查集

        for(auto& edge : edges) { // 重新计算并查集
            int p = edge.first, q = edge.second;
            if(!lost[p] && !lost[q]) _union(p, q); // 都没丢失，计算并查集
        }

        int curCount = _count(N);

        if(curCount <= preCount) cout << "City " << city << " is lost." << endl;
        else if(curCount > preCount) cout << "Red Alert: City " << city << " is lost!" << endl;

        if(curCount == 0) cout << "Game Over." << endl;

        preCount = curCount;
    }

    return 0;
}

/*
总结：
本题考察并查集判断连通性的变化，关键点如下：

1. 题目分析：
   - 需要判断每次失去一个城市后，国家的连通性是否改变
   - 关键：连通分量数量增加 = 连通性被破坏 = 发出红色警报
   - 注意：初始可能就不连通，所以要用"连通分量数量变化"来判断

2. 解题思路：
   - 每次攻占一个城市后，重新建立并查集（排除已攻占的城市）
   - 统计当前连通分量数量，与攻占前比较
   - 如果连通分量数量增加，说明该城市的丢失导致国家分裂

3. 判断逻辑：
   - preCount：攻占前的连通分量数
   - curCount：攻占后的连通分量数
   - curCount > preCount → 发出红色警报
   - curCount <= preCount → 正常丢失

4. 易错点：
   - 城市编号从0开始，不是从1开始
   - 最后一个城市被攻占时curCount为0，要输出"Game Over."
   - 被攻占的城市不参与连通分量统计
   - 每次攻占后要重置并查集，重新建立连接关系
   - 需要保存所有边的信息，每次重建并查集时遍历

5. 时间复杂度：
   - O(K * (N + M))，每次攻占需要重置并查集和重新合并边
   - 对于本题数据范围（N≤500, M≤5000, K≤N）完全够用
*/
