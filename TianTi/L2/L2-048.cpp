#include<bits/stdc++.h>
using namespace std;

// 方法一：只要是纯粹统计“连通块（岛屿）数量”或“全图染色”的问题，强烈推荐首选 DFS。
int N, M;
vector<string> mp;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int cnt = 0;
int bao = 0;
bool have = false;

// 淹没岛屿
void dfs(int x, int y) {
    if(x < 0 || x >= N || y < 0 || y >= M) return ;
    if(mp[x][y] == '0') return ;
    if(mp[x][y] >= '2' && mp[x][y] <= '9') {
        have = true;
    }
    mp[x][y] = '0';  // 淹没
    for(int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int main() {
    cin>>N>>M;
    mp.resize(N);
    for(int i = 0; i < N; i++) {
        cin>>mp[i];
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(mp[i][j] != '0') {
                cnt++;
                have = false;
                dfs(i, j);  // 遍历这个岛屿
                if(have) bao++;
            }
        }
    }
    cout<<cnt<<" "<<bao;
    return 0;
}

// 方法二：BFS 求最少步数、最短逃生距离优先
// int main() {
//     int N, M;  cin>>N>>M;
//     vector<string> mp(N);
//     for(int i = 0; i < N; i++) {
//         cin>>mp[i];
//     }
//     int cnt = 0; // 岛屿数量
//     int bao = 0; // 含有宝藏的岛屿
//     // 上下左右方向数组
//     int dx[] = {-1, 1, 0, 0};
//     int dy[] = {0, 0, -1, 1};
    
//     for(int i = 0; i < N; i++) {
//         for(int j = 0; j < M; j++) {
//             if(mp[i][j] != '0') { // 找到岛屿就BFS
//                 cnt++;
//                 bool have = false; // 有没有宝藏
//                 queue<pair<int, int>> q;
//                 q.push({i, j});
//                 if(mp[i][j] >= '2' && mp[i][j] <= '9') {
//                     have =true;
//                 }
//                 mp[i][j] = '0'; // 淹没岛屿
//                 while(!q.empty()) {
//                     auto cur = q.front();  q.pop();
//                     int x = cur.first, y = cur.second;
//                     for(int k = 0; k < 4; k++) {
//                         int nx = x + dx[k], ny = y + dy[k];
//                         if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
//                         if(mp[nx][ny] == '0') continue; // 海水直接跳过
//                         if(mp[nx][ny] >= '2' && mp[nx][ny] <= '9') {
//                             have =true;
//                         }  // 入队就标记
//                         mp[nx][ny] = '0';
//                         q.push({nx, ny});
//                     }
//                 }
//                 if(have) bao++;
//             }
//         }
//     }
//     cout<<cnt<<" "<<bao;
//     return 0;
// }