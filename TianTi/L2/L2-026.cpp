#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
int N;
vector<int> adj[MAXN];
int depth[MAXN]; // 记录每个节点的深度

int main() {
    cin>>N;
    int root = 0;
    for(int i = 1; i <= N; i++) {
        int x;  cin>>x;
        if(x != -1) {
            adj[x].push_back(i);
        } else {
            root = i;
        }
    }

    queue<int> q;
    q.push(root);
    int max_depth = 1;
    depth[root] = 1;
    while(!q.empty()) {
        int cur = q.front();  q.pop();
        for(int i : adj[cur]) {
            q.push(i);
            depth[i] = depth[cur] + 1;
            max_depth = max(max_depth, depth[i]);
        }
    }
    // 递增顺序输出
    vector<int> ans;
    for(int i = 1; i <= N; i++) {
        if(depth[i] == max_depth) {
            ans.push_back(i);
        }
    } // 不用排序，本就是递增输入的
    cout<<max_depth<<"\n";
    for(int i = 0; i < ans.size(); i++) {
        if(i != 0) cout<<" ";
        cout<<ans[i];
    }
    return 0;
}