/*
 * @lc app=leetcode.cn id=566 lang=cpp
 * @lcpr version=30307
 *
 * [566] 重塑矩阵
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
        if(r * c != m * n) return mat;
        // 方法一：通过中间一维数组中转
        // vector<int> v(m*n);
        // vector<vector<int>> res(r, vector<int>(c,0));
        // int in = 0;
        // for(int i = 0; i < m; i++) {
        //     for(int j = 0; j < n; j++) {
        //         v[in++] = mat[i][j];
        //     }
        // }
        // in = 0;
        // for(int i = 0; i < r; i++) {
        //     for(int j = 0; j < c; j++) {
        //         res[i][j] = v[in++];
        //     }
        // }
        // return res;
        
        // 方法二：通过数学技巧，坐标直接转化
        vector<vector<int>> res(r, vector<int>(c));
        for(int i = 0; i < m * n; i++) {
            res[i / c][i % c] = mat[i / n][i % n];
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[3,4]]\n1\n4\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,4]]\n2\n4\n
// @lcpr case=end

 */

