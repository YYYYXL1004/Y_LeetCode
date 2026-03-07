/*
 * @lc app=leetcode.cn id=1260 lang=cpp
 * @lcpr version=30307
 *
 * [1260] 二维网格迁移
 */

// @lc code=start
class Solution {
public:
    // 方法一：暴力
    // vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    //     while(k--) {
    //         grid = Grid(grid);
    //     }
    //     return grid;
    // }

    // vector<vector<int>> Grid(vector<vector<int>>& grid) {
    //     int m = grid.size(), n = grid[0].size();
    //     vector<vector<int>> res(m, vector<int>(n));
    //     for(int i = 0; i < m; i++) {
    //         for(int j = 0; j < n; j++) {
    //             if(j == n - 1) {
    //                 if(i == m - 1) res[0][0] = grid[i][j];
    //                 else res[i + 1][0] = grid[i][n - 1];
    //             } else {
    //                 res[i][j + 1] = grid[i][j];
    //             }
    //         }
    //     }
    //     return res;
    // }

    // 方法二：转化为一维数组，右移K位
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int total = m * n;
        k %= total; // 降低计算量

        vector<vector<int>> res(m, vector<int>(n));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int oldPos = i * n + j; //原一维数组索引
                int newPos = (oldPos + k) % total; // 移动k次新索引
                res[newPos / n][newPos % n] = grid[i][j]; 
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n1\n
// @lcpr case=end

// @lcpr case=start
// [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]]\n4\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n9\n
// @lcpr case=end

 */

