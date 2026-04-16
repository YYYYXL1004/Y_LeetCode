#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
int n;
vector<int> adj[MAXN];
vector<int> pre;

void dfs(int root) {
    // 前序位置
    pre.push_back(root);
    if(!adj[root].empty()) {
        sort(adj[root].begin(), adj[root].end());
        for(int i : adj[root]) {
            dfs(i);
        }
    }else return ;
}

int main() {
    cin>>n;
    int root = 0;
    for(int i = 1; i <= n; i++) {
        int x;  cin>>x;
        if(x == 0) {
            root = i;
        } else {
            adj[x].push_back(i);
        }
    }
    int k = adj[root].size();
    int maxk = k;
    bool isman = true;
    for(int i = 1; i <= n; i++) {
        int sz = adj[i].size();
        if(sz != 0) {
            if(k != sz) {
                isman = false;
                maxk = max(maxk, sz);
            }
        }
    }
    cout<<maxk<<" ";
    if(isman) cout<<"yes\n";
    else cout<<"no\n";
    dfs(root);
    for(int i = 0; i < n; i++) {
        if(i > 0) cout<<" ";
        cout<<pre[i];
    }
    return 0;
}