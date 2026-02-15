#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 一个岛屿如果没被包围，那它旁边的海水一定能一路连通到地图外面（外海）。
// 一个岛屿如果被包围了，那它旁边的海水是封闭的内湖，到不了地图外面。

int T, M, N;
vector<string> grid;
int dirs8[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int dirs4[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 8方向BFS标记外海水为 '2'
void bfsSea() {
    queue<pair<int, int>> q;
    // 扩展后的地图，(0, 0)一定是海水'0'，从它开始
    grid[0][0] = '2';
    q.push({0, 0});

    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        for(int d = 0; d < 8; d++) { // 8方向扩散
            int ni = cur.first + dirs8[d][0], nj = cur.second + dirs8[d][1];
            if(ni < 0 || ni >= M || nj < 0 || nj >= N) continue;
            if(grid[ni][nj] != '0' ) continue;  // 不是未标记的海水就跳过
            grid[ni][nj] = '2';
            q.push({ni, nj});
        }
    }
}

// 4方向DFS遍历岛屿， 检查是否与外海水'2’相邻
bool touchOuter;
void dfs(int i, int j) {
    if(i < 0 || i >= M || j < 0 || j >= N) return ;
    if(grid[i][j] != '1') return;
    grid[i][j] = '3'; // 标记已访问（淹没）
    // 检查4邻域是否有外海水'2'
    for(int d = 0; d < 4; d++) {
        int ni = i + dirs4[d][0], nj = j + dirs4[d][1];
        if(ni >= 0 && ni < M && nj >= 0 && nj <N && grid[ni][nj] == '2') {
            touchOuter = true;
        }  
    }
    // 递归淹没相邻陆地
    for(int d = 0; d < 4; d++) {
        dfs(i + dirs4[d][0], j + dirs4[d][1]);
    }
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        // scanf("%d%d", &M, &N);
        cin >> M >> N;
        // 扩展地图：外围加一圈海水
        grid.clear();
        grid.push_back(string(N + 2, '0')); // 顶部一行海水
        for(int i = 0; i < M; i++) {
            string s;  cin >> s;
            grid.push_back("0" + s + "0");  // 左右各加一行海水
        }
        grid.push_back(string(N + 2, '0')); // 底部一行海水
        M += 2;  N += 2;
        
        bfsSea();
        
        int ans = 0;
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(grid[i][j] == '1') {    // 发现新岛屿
                    touchOuter = false;
                    dfs(i ,j);             // 淹没整个岛屿
                    if(touchOuter) ans++;  // 只有挨着外海的才计数
                }
            } 
        } 
        cout << ans << "\n";
    }
    return 0;
}