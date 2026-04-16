#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e4+4;
int N;
vector<int> adj[MAXN];
int in_degree[MAXN];  // 通过入度判断根节点
vector<int> cur; // 现在正在遍历的路径
vector<int> ans;  

void dfs(int u) {
    cur.push_back(u);
    // 只有当当前路径长度大于历史最长时，才更新
    // 因为我们提前排序了，同等长度下最先到达的必定是字典序最小的，所以这里是 > 而不是 >=
    if(cur.size() > ans.size()) {
        ans = cur;
    }

    for(int v : adj[u]) {
        dfs(v);
    }
    cur.pop_back(); // 回溯
}

int main() {
    cin>>N;
    for(int i = 0; i < N;i++) {
        int k; cin>>k;
        while(k--) {
            int x;  cin>>x;
            adj[i].push_back(x);
            in_degree[x]++;
        }
        // 提前对邻接表排序，把复杂的字典序比较直接抹杀在摇篮里
        sort(adj[i].begin(), adj[i].end());
    }
    int root = 0;
    for(int i = 0; i < N; i++) {
        if(in_degree[i] == 0) {
            root = i; 
            break;
        }
    }
    dfs(root);
    cout<<ans.size()<<"\n";
    for(int i = 0; i < ans.size(); i++) {
        if(i > 0) cout<<" ";
        cout<<ans[i];
    }
    return 0;
}

// 总结：
// 1. 题目要求最长路径，且同样长度下字典序最小。我们可以通过提前排序邻接表来简化字典序的处理。
// 2. 通过入度数组找到根节点，DFS遍历所有路径，更新最长路径即可。