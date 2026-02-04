/*
 * @lc app=leetcode.cn id=867 lang=cpp
 * @lcpr version=30307
 *
 * [867] 转置矩阵
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> res(n, vector<int>(m));
        // 直接转置
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                res[j][i]= matrix[i][j];
            }
        }
        // // 按列优先遍历原矩阵
        // for(int j = 0; j < n; j++) {     // 遍历每一列
        //     for(int i = 0; i < m; i++) { // 遍历该列的每一行
        //         res[j][i] = matrix[i][j];  // 第j列变成第j行
        //     }
        // }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3],[4,5,6]]\n
// @lcpr case=end

 */

