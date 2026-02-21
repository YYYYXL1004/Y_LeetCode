/*
 * @lc app=leetcode.cn id=1368 lang=cpp
 * @lcpr version=30400
 *
 * [1368] 使网格图至少有一条有效路径的最小代价
 */

// @lc code=start
class Solution {
public:
    struct State{
        int x, y;
        int costFromStart;
        State(int x, int y, int costFromStart) : x(x), y(y), costFromStart(costFromStart) {}

        bool operator < (const State& other) const {
            return costFromStart > other.costFromStart;
        }
    };

    // 四个方向：1-右 2-左 3-下 4-上（与题目定义一致）
    // dirs[0] 不用，dirs[1]~dirs[4] 对应 dirID 1~4
    int dirs[5][2] = {{0,0}, {0,1}, {0,-1}, {1,0}, {-1,0}};

    // 返回坐标 (x, y) 的上下左右相邻坐标及对应的 dirID
    vector<vector<int>> adj(vector<vector<int>>& grid, int x, int y) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> neighbors;
        for(int dirID = 1; dirID <= 4; dirID++) {
            int nx = x + dirs[dirID][0];
            int ny = y + dirs[dirID][1];
            if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            neighbors.push_back({nx, ny, dirID});
        }
        return neighbors;
    }

    int dijkstra(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> costTo(m, vector<int>(n, INT_MAX));
        priority_queue<State> pq;
        pq.emplace(0, 0, 0);
        costTo[0][0] = 0;

        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curX = cur.x;
            int curY = cur.y;
            int curCostFromStart = cur.costFromStart;

            if(curX == m - 1 && curY == n - 1) return curCostFromStart;

            if(costTo[curX][curY] < curCostFromStart) continue;
            // costTo[curX][curY] = curCostFromStart;
            for(auto& neighbor : adj(grid, curX, curY)) {
                int nx = neighbor[0];
                int ny = neighbor[1];
                int dirID = neighbor[2];
                // 如果当前格子的箭头方向和走向邻居的方向一致，代价为 0，否则为 1
                int cost = (grid[curX][curY] == dirID) ? 0 : 1;
                int nextCostFromStart = curCostFromStart + cost;

                if(costTo[nx][ny] <= nextCostFromStart) continue;

                pq.emplace(nx, ny, nextCostFromStart);
                costTo[nx][ny] = nextCostFromStart;
            }
        }
        return -1;
    }

    // 本质上就是：「改箭头的最小次数」= 「边权为 0/1 的图上的最短路」
    int minCost(vector<vector<int>>& grid) {
        return dijkstra(grid);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1,3],[3,2,2],[1,1,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[4,3]]\n
// @lcpr case=end

 */

