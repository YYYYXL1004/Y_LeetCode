/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * @lcpr version=30307
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int upper_bound = 0, lower_bound = m - 1;
        int left_bound = 0, right_bound = n - 1;
        vector<int> res;
        while(res.size() < m*n) {
            if(upper_bound <= lower_bound) {
                // 从顶部自左往右遍历
                for(int j = left_bound; j <= right_bound; j++) {
                    res.push_back(matrix[upper_bound][j]);
                }
                // 上边界下移
                upper_bound++;
            }
            if(right_bound >= left_bound) {
                // 从右侧自上往下遍历
                for(int i = upper_bound; i <= lower_bound; i++) {
                    res.push_back(matrix[i][right_bound]);
                }
                // 右边界左移
                right_bound--;
            }
            if(lower_bound >= upper_bound) {
                // 从底部自右往左遍历
                for(int j = right_bound; j >= left_bound; j--) {
                    res.push_back(matrix[lower_bound][j]);
                }
                // 下边界上移
                lower_bound--;
            }
            if(left_bound <= right_bound) {
                // 从左侧自下往上遍历
                for(int i = lower_bound; i >= upper_bound; i--) {
                    res.push_back(matrix[i][left_bound]);
                }
                // 左边界右移
                left_bound++;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3,4],[5,6,7,8],[9,10,11,12]]\n
// @lcpr case=end

 */

