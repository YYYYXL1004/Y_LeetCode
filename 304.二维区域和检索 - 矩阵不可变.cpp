/*
 * @lc app=leetcode.cn id=304 lang=cpp
 * @lcpr version=30307
 *
 * [304] 二维区域和检索 - 矩阵不可变
 */

// @lc code=start
class NumMatrix {
    // preSum[i][j] 记录矩阵[0, 0, i-1, j-1]的元素和
    vector<vector<int> > preSum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m =matrix.size(), n = matrix[0].size();
        if(m == 0 || n== 0) return ;
        preSum.resize(m+1, vector<int>(n+1, 0)); // 初始化二维数组
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <=n; j++) { // 画图比较客观，注意下标preSum是从1开始的
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] + matrix[i-1][j-1] - preSum[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return preSum[row2+1][col2+1] - preSum[row1][col2+1] - preSum[row2+1][col1] + preSum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
// @lc code=end



/*
// @lcpr case=start
// ["NumMatrix","sumRegion","sumRegion","sumRegion"]\n[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]\n
// @lcpr case=end

 */

