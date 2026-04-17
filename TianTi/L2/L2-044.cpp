#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dist[505][505];
char gender[505];

// 先找出每个人在所有异性眼中的“最差印象”（最大距离），
// 然后选出这个“最差印象”里得分最好（距离最小）的那批人。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;  cin>>N;
    // 1. 初始化距离矩阵
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    // 2. 读入数据、建图
    for(int i = 1; i <= N; i++) {
        int K;  cin>>gender[i]>>K;
        for(int k = 0; k < K; k++) {
            int v, w;  char c;
            cin>>v>>c>>w;  // 用c把冒号去掉
            dist[i][v] = min(dist[i][v], w); // 有向图
        }
    }
    // 3. Floyd模版
    // 注意：k 必须在最外层！
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            if(dist[i][k] == INF) continue;
            for(int j = 1; j <= N; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    // 4. 统计每个人的异性缘(最差印象里的最小值)
    vector<int> max_d(N+1, 0);
    int min_F = INF, min_M = INF;
    for(int i = 1; i <= N; i++) {
        // 找异性 j 对 i 的最远距离
        for(int j = 1; j <= N; j++) {
            if(gender[i] != gender[j]) {
                // 铁律：是 j 到 i 的距离，不是 i 到 j！
                max_d[i] = max(max_d[i], dist[j][i]);
            }
        }
        if(gender[i] == 'F') min_F = min(min_F, max_d[i]);
        if(gender[i] == 'M') min_M = min(min_M, max_d[i]);
    }
    // 5. 寻找大众情人并输出
    vector<int> ans_f, ans_m;
    for(int i = 1; i <= N; i++) {
        if(gender[i] == 'F' && max_d[i] == min_F) ans_f.push_back(i);
        if(gender[i] == 'M' && max_d[i] == min_M) ans_m.push_back(i);
    }
    for(int i = 0; i < ans_f.size(); i++) {
        if(i > 0) cout<<" ";
        cout<<ans_f[i];
    } cout<<"\n";
    for(int i = 0; i < ans_m.size(); i++) {
        if(i > 0) cout<<" ";
        cout<<ans_m[i];
    } cout<<"\n";
    return 0;
}