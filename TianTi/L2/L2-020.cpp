#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
int N;
double Z, r;
vector<int> adj[MAXN];
double weight[MAXN];  // 记录得道者放大倍数
double sum = 0.0;  // 总功力
double r_rate;  // 记录每次传递后剩下的比列 (1-r%)

// DFS 函数：u 是当前节点，power 是传到 u 手里的功力
void dfs(int u, double power) {
    if(weight[u] > 0) {
        sum += power * weight[u];
        return ; // 得道者没有徒弟，直接回溯
    }
    // 不是得道者，继续传功力给徒弟
    for(int v : adj[u]) {
        dfs(v, power * r_rate);
    }
}

int main() {
    cin>>N>>Z>>r;
    r_rate = 1 - r / 100.0;
    for(int i = 0; i < N; i++) {
        int k;  cin>>k;
        if(k != 0) {
            while(k--) {
                int x;  cin>>x;
                adj[i].push_back(x);
            }
        } else {
            cin>>weight[i];
        }
    }
    dfs(0, Z);
    // 用 long long 强转可以直接截断小数部分（相当于向下取整），还能防止 int 溢出
    cout<<(long long)sum;
    return 0;
}