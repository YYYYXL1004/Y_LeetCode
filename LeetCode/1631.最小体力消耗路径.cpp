/*
 * @lc app=leetcode.cn id=1631 lang=cpp
 * @lcpr version=30400
 *
 * [1631] 最小体力消耗路径
 */

// @lc code=start
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        return dijkstra(heights);
    }

    struct State{
        int row;
        int col;
        int distFromStart;
        State(int row, int col, int distFromStart) : row(row), col(col), distFromStart(distFromStart) {}

        bool operator < (const State& other) const {
            return distFromStart > other.distFromStart;
        }
    };

    int dijkstra(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 记录从起点 (0, 0) 到每个节点的最小体力消耗
        vector<vector<int>> distTo(m, vector<int>(n, INT_MAX));

        priority_queue<State> pq;
        pq.emplace(0, 0, 0);
        distTo[0][0] = 0;

        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curRow = cur.row;
            int curCol = cur.col;
            int curDistFormStart = cur.distFromStart;
            // 剪枝
            if(distTo[curRow][curCol] < curDistFormStart) continue;

            if(curRow == m - 1 && curCol == n - 1) { // 到达目标
                return distTo[curRow][curCol];
            }

            for(auto& neighbor : adj(matrix, curRow, curCol)) {
                int nextRow = neighbor[0];
                int nextCol = neighbor[1];
                int nextDistFromStart = max(curDistFormStart, abs(matrix[nextRow][nextCol] - matrix[curRow][curCol]));

                if(distTo[nextRow][nextCol] <= nextDistFromStart) continue;

                pq.emplace(nextRow, nextCol, nextDistFromStart);
                distTo[nextRow][nextCol] = nextDistFromStart;
            }
        }
        return -1;
    }

    // 返回坐标 (x, y) 的上下左右相邻坐标
    vector<vector<int>> adj(vector<vector<int>>& matrix, int x, int y) {
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> neighbors; // 存储相邻节点
        for(auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if(nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }
            neighbors.push_back({nx, ny});
        }
        return neighbors;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,2],[3,8,2],[5,3,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3],[3,8,4],[5,3,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]\n
// @lcpr case=end

 */

