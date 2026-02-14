/*
 * @lc app=leetcode.cn id=1020 lang=cpp
 * @lcpr version=30400
 *
 * [1020] 飞地的数量
 */

// @lc code=start
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for(int i = 0; i < m; i++) {
            dfs(grid, i, 0); // 左边
            dfs(grid, i, n - 1); // 右边
        }
        for(int j = 0; j < n ; j++) {
            dfs(grid, 0, j); // 上边
            dfs(grid, m - 1, j); // 下边
        }

        int res = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    res += dfs(grid, i, j);
                }
            }
        }
        return res;
    }

    // 淹掉岛屿并计算岛屿面积
    int dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n)  return 0;
        if(grid[i][j] == 0) return 0;
        
        grid[i][j] = 0;
        return dfs(grid, i - 1, j) + dfs(grid, i + 1, j) + dfs(grid, i, j - 1) + dfs(grid, i, j + 1) + 1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]\n
// @lcpr case=end

 */

