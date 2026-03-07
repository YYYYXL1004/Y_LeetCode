/*
 * @lc app=leetcode.cn id=1254 lang=cpp
 * @lcpr version=30400
 *
 * [1254] 统计封闭岛屿的数目
 */

// @lc code=start
class Solution {
public:
    // 主函数：计算封闭岛屿的数量
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;
        int m = grid.size(), n = grid[0].size();
        for(int j = 0; j < n; j++) {
            dfs(grid, 0, j); // 把靠上面的岛屿淹掉
            dfs(grid, m - 1, j); //把靠下面的岛屿淹掉
        }
        for(int i = 0; i < m; i++) {
            dfs(grid, i, 0);  // 淹掉左边的
            dfs(grid, i, n - 1); // 淹掉右边的
        }
        // 遍历 grid，剩下的岛屿都是封闭岛屿
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    res++;
                    dfs(grid, i, j);
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if(i < 0 || i >= m || j <0 || j>= n) return;
        if(grid[i][j] == 1) return;

        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        grid[i][j] = 1;
        for(auto &d : dirs) {
            int next_i = i + d[0];
            int next_j = j + d[1];
            dfs(grid, next_i, next_j);
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1,1,1,1,1,1],[1,0,0,0,0,0,1],[1,0,1,1,1,0,1],[1,0,1,0,1,0,1],[1,0,1,1,1,0,1],[1,0,0,0,0,0,1],[1,1,1,1,1,1,1]]\n
// @lcpr case=end

 */

