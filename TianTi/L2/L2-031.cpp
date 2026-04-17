#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
vector<int> adj[MAXN];
int indegree[MAXN];  // 入度，找root

int main() {
    int N;  cin>>N;
    for(int i = 1; i <= N; i++) {
        int k;  cin>>k;
        while(k--) {
            int x; cin>>x;
            adj[i].push_back(x);
            indegree[x]++;
        }
    }
    int root = 0;
    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) {
            root = i;
            break;
        }
    }
    queue<int> q;
    q.push(root);
    int last = root;
    while(!q.empty()) {
        int cur = q.front();  q.pop();
        last = cur;
        for(int v : adj[cur]) {
            q.push(v);
        }
    }
    cout<<last;
    return 0;
}