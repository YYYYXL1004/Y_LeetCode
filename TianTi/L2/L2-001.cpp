/*
L2-001 紧急救援

题目：
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。在地图上显示有多个分散的城市和一些连接城市的快速道路。
每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。当其他城市有紧急求助电话给你的时候，
你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。

输入格式:
输入第一行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0 ~ (N−1）；
M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号。
第二行给出N个正整数，其中第i个数是第i个城市的救援队的数目，数字间以空格分隔。
随后的M行中，每行给出一条快速道路的信息，分别是：城市1、城市2、快速道路的长度，中间用空格分开，数字均为整数且不超过500。
输入保证救援可行且最优解唯一。

输出格式:
第一行输出最短路径的条数和能够召集的最多的救援队数量。
第二行输出从S到D的路径中经过的城市编号。数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2

输出样例:
2 60
0 1 3

题解：
Dijkstra 变形题，需要同时维护：
1. distTo[i]: 起点到城市 i 的最短距离
2. cntTo[i]: 起点到城市 i 的最短路径条数
3. teamsTo[i]: 起点到城市 i 的最短路径上能召集的最多救援队数
4. pre[i]: 记录路径前驱节点

关键逻辑：
- 发现更短路径：更新 distTo, cntTo, teamsTo, pre
- 发现等长路径：累加 cntTo，如果救援队更多则更新 teamsTo 和 pre

时间复杂度：O(E log V)
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, s, d;
vector<int> distTo;       // 最短距离
vector<int> cntTo;        // 最短路径条数
vector<int> teamsTo;      // 最多救援队数
vector<int> pre;          // 前驱节点
vector<int> res;          // 最终路径
vector<vector<pair<int, int>>> graph;  // graph[from] -> {to, weight}
unordered_map<int, int> mp;            // city -> 救援队数量

struct State {
    int node;
    int distFromStart;
    State(int node, int distFromStart) : node(node), distFromStart(distFromStart) {}

    bool operator<(const State& other) const {
        return distFromStart > other.distFromStart; // 最小堆
    }
};

void dijkstra() {
    distTo.assign(n, INT_MAX);
    cntTo.assign(n, 0);
    teamsTo.assign(n, 0);
    pre.assign(n, -1);

    priority_queue<State> pq;
    pq.emplace(s, 0);
    distTo[s] = 0;
    cntTo[s] = 1;
    teamsTo[s] = mp[s];

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int curNode = cur.node;
        int curDistFromStart = cur.distFromStart;

        if (distTo[curNode] < curDistFromStart) continue;

        for (auto& neighbor : graph[curNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            int nextDistFromStart = curDistFromStart + weight;
            int nextTeams = teamsTo[curNode] + mp[nextNode];

            // 发现更短路径
            if (nextDistFromStart < distTo[nextNode]) {
                distTo[nextNode] = nextDistFromStart;
                cntTo[nextNode] = cntTo[curNode];
                teamsTo[nextNode] = nextTeams;
                pre[nextNode] = curNode;
                pq.emplace(nextNode, nextDistFromStart);
            }
            // 发现等长路径
            else if (nextDistFromStart == distTo[nextNode]) {
                cntTo[nextNode] += cntTo[curNode];
                if (nextTeams > teamsTo[nextNode]) {
                    teamsTo[nextNode] = nextTeams;
                    pre[nextNode] = curNode;
                }
            }
        }
    }

    // 重建路径
    for (int x = d; x != -1; x = pre[x]) {
        res.push_back(x);
    }
    reverse(res.begin(), res.end());
}

int main() {
    cin >> n >> m >> s >> d;

    graph.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> mp[i];
    }

    for (int i = 0; i < m; i++) {
        int from, to, w;
        cin >> from >> to >> w;
        graph[from].emplace_back(to, w);
        graph[to].emplace_back(from, w);  // 无向图
    }

    dijkstra();

    cout << cntTo[d] << " " << teamsTo[d] << "\n";
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i < res.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
