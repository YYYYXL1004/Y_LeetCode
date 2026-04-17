#include<bits/stdc++.h>
using namespace std;

int main() {
    int V, E, K;
    cin>>V>>E>>K;
    vector<pair<int, int>> edges;
    for(int i = 1; i <= E; i++) {
        int u, v;  cin>>u>>v;
        edges.emplace_back(u, v);
    }
    int N;  cin>>N;
    while(N--) {
        vector<int> mp(V+1);  // 点的颜色
        set<int> color;  // 计算颜色个数
        for(int i = 1; i <= V; i++) {
            cin>>mp[i];
            color.insert(mp[i]);
        }
        bool is = true; // 符不符合要求
        if((int)color.size() != K) {
            is = false;
        } else {
            for(auto edge : edges) {
                int u = edge.first;
                int v = edge.second;
                if(mp[u] == mp[v]) {
                    is = false;
                    break;
                }
            }
        }
        if(is) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}

// 方法2：BFS遍历
// const int MAXN = 505;
// vector<int> adj[MAXN];

// int main() {
//     int V, E, K;
//     cin>>V>>E>>K;
//     for(int i = 1; i <= E; i++) {
//         int u, v;  cin>>u>>v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }
//     int N;  cin>>N;
//     while(N--) {
//         vector<int> mp(V+1);  // 点对应颜色
//         vector<int> visited(V+1); // 访问数组，控制防止走回路
//         set<int> color;
//         for(int i = 1; i <= V; i++) {
//             cin>>mp[i];
//             color.insert(mp[i]);
//         }
//         bool is = true; // 是不是解
//         if(color.size() != K) {
//             is = false;
//         } else {
//             // 外层遍历，处理可能存在多个连通分量的情况
//             for(int i = 1; i <= V ; i++) {
//                 if(visited[i]) continue; // 被搜过，跳过
//                 if(!is) break;
//                 // BFS遍历
//                 queue<int> q;
//                 q.push(i);
//                 visited[i] = 1;  // 标记
//                 while(!q.empty()) {
//                     int cur = q.front();  q.pop();
//                     for(int v : adj[cur]) {
//                         if(mp[v] == mp[cur]) {
//                             is = false;
//                             break;
//                         }
//                         if(!visited[v]) { // 防止走回头路
//                             q.push(v);
//                             visited[v] = 1;  // 铁律：入队立刻标记！
//                         }
//                     }
//                     if(!is) break;
//                 }
//             }
//         }
//         if(is) cout<<"Yes\n";
//         else cout<<"No\n";
//     }
//     return 0;
// }