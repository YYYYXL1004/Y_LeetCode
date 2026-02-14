/*
 * @lc app=leetcode.cn id=695 lang=cpp
 * @lcpr version=30400
 *
 * [695] 岛屿的最大面积
 */

// @lc code=start
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0; 
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    // 淹没岛屿，并更新最大岛屿面积
                    res = max(res, dfs(grid, i, j));
                }
            }
        }
        return res;
    }
    // 淹没与 (i, j) 相邻的陆地，并返回淹没的陆地面积
    int dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return 0;
        if(grid[i][j] == 0) return 0;

        grid[i][j] = 0;
        return dfs(grid, i - 1, j) + dfs(grid, i + 1, j) +
                dfs(grid, i, j - 1) + dfs(grid, i, j + 1) + 1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0,0,0,0,0,0]]\n
// @lcpr case=end

 */

