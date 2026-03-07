/*
 * @lc app=leetcode.cn id=1314 lang=cpp
 * @lcpr version=30307
 *
 * [1314] 矩阵区域和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int> > preSum;
    int sumRegion(int x1, int y1, int x2, int y2) {
        return preSum[x2+1][y2+1] - preSum[x1][y2+1] - preSum[x2+1][y1] + preSum[x1][y1];
    }
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        preSum.resize(m+1, vector<int>(n+1, 0));
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j<= n; j++) { // 注意原矩阵下标，是i-1,j-1
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] + mat[i-1][j-1] - preSum[i-1][j-1];
            }
        }
        vector<vector<int> > res(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) { // 使用min，max优雅避免索引越界
                // 左上角坐标
                int x1 = max(i-k, 0);
                int y1 = max(j-k, 0);
                // 右下角
                int x2 = min(i+k, m-1);
                int y2 = min(j+k, n-1);
                res[i][j] = sumRegion(x1, y1, x2, y2);
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
// [[1,2,3],[4,5,6],[7,8,9]]\n2\n
// @lcpr case=end

 */

