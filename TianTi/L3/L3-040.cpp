#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
struct Edge{
    int to, cost, mood;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int b, n, m, k;
    cin>>b>>n>>m>>k;
    vector<vector<Edge>> adj(n+1);
    while(m--) {
        int u, v, cost, mood;
        cin>>u>>v>>cost>>mood;
        adj[u].emplace_back(v, cost, mood);
        adj[v].emplace_back(u, cost, mood);
    }
    while(k--) {
        int s;  cin>>s;
        vector<int> dist(n+1, INF);  // 里面是消费额度
        vector<int> max_mood(n+1, -1);
        dist[s] = 0;  max_mood[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});
        while(!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int u = cur.second;
            int d = cur.first;
            if(d > dist[u]) continue;
            for(auto& edge : adj[u]) {
                int v = edge.to, w = edge.cost, mm = edge.mood;
                // 第一优先级：花钱更少
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    max_mood[v] = max_mood[u] + mm;
                    pq.push({dist[v], v});
                } else if(dist[u] + w == dist[v]) { // 第二优先级：花钱一样多，但心情更好
                    if(max_mood[u] + mm > max_mood[v]) {
                        max_mood[v] = max_mood[u] + mm;
                    }
                }
            }
        }
        int maxm = -1; // 能到达的城市里的最高心情指数
        vector<int> ans;
        // 收集所有能在预算内到达的城市(不包括开始城市)
        for(int i = 1; i <= n; i++) {
            if(i != s && dist[i] <= b) {
                ans.push_back(i);
                maxm = max(maxm, max_mood[i]);
            }
        }
        if(ans.empty()) {
            cout<<"T_T\n"; 
        } else {
            // 此时ans已经是递增的了
            for(int i = 0; i < ans.size(); i++) {
                if(i > 0) cout<<" ";
                cout<<ans[i];
            }
            cout<<"\n";
            vector<int> best_mood;
            for(int i : ans) {
                if(max_mood[i] == maxm) {
                    best_mood.push_back(i);
                }
            }
            for(int i = 0; i < best_mood.size(); i++) {
                if(i > 0) cout<<" ";
                cout<<best_mood[i];
            }
            cout<<"\n";
        }
    }
    return 0;
}