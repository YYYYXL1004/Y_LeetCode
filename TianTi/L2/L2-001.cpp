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

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int inf = 0x3f3f3f3f;
// typedef pair<int, int> pii;

int n,m,s,ed;
vector<int> dist;   // 记录从起点 s 到每个点的最短距离
vector<int> paths;   // 记录从起点 s 到每个点的最短路线有几条
vector<int> total;  // 记录走这条最短路，最多能集结多少支救援队
vector<int> vpre;   // 记录当前节点的前驱节点是谁。（为了最后顺藤摸瓜找回路线）
vector<int> team;
vector<vector<pii> >adj;

void dijkstra()
{
    dist[s] = 0; paths[s] = 1;
    total[s] = team[s];
    // pair默认比较first， 所以距离最小的先出来
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push({0, s});
    while(!pq.empty()) {
        auto cur = pq.top();  pq.pop();
        int d = cur.first, u = cur.second;
        if(d > dist[u]) continue;
        for(auto& edge: adj[u]) {
            int v = edge.first, w = edge.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                paths[v] = paths[u];
                total[v] = total[u] + team[v];
                vpre[v] = u;
                pq.push({dist[v], v});
            } else if(dist[u] + w == dist[v]) {
                paths[v] += paths[u];
                if(total[u] + team[v] > total[v]) {
                    total[v] = total[u] + team[v];
                    vpre[v] = u;
                }
            }
        }
    }
    cout<<paths[ed]<<" "<<total[ed]<<"\n";
    stack<int> path;
    for(int i = ed; i != -1; i = vpre[i]) {
        path.push(i);  // 倒序还原路径
    }
    cout<<path.top();  path.pop();
    while(!path.empty()) {
        cout<<" "<<path.top();
        path.pop();
    }
}

int main()
{
	cin>>n>>m>>s>>ed;
	team.resize(n+1);   dist.assign(n+1,inf);
	adj.resize(n+1);    paths.assign(n+1,0);
	total.assign(n+1,0);  vpre.assign(n+1,-1);
	for(int i=0;i<n;i++)  cin>>team[i];
	for(int i=0;i<m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
	}
	dijkstra();
	return 0;
}
