/*
 * @lc app=leetcode.cn id=59 lang=cpp
 * @lcpr version=30307
 *
 * [59] 螺旋矩阵 II
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int upper_bound = 0, lower_bound = n - 1;
        int left_bound = 0, right_bound = n - 1;
        vector< vector<int> > res(n, vector<int>(n));
        int num = 1;
        while(num <= n * n) {
            if(upper_bound <= lower_bound) {
                for(int j = left_bound; j <= right_bound; j++) {
                    res[upper_bound][j] = num;
                    num++;
                }
                upper_bound++;  // 上边界下移
            }
            if(right_bound >= left_bound) {
                for(int i = upper_bound; i <= lower_bound; i++) {
                    res[i][right_bound] = num;
                    num++;
                }
                right_bound--;
            }
            if(lower_bound >= upper_bound) {
                for(int j = right_bound; j >= left_bound; j--) {
                    res[lower_bound][j] = num;
                    num++;
                }
                lower_bound--;
            }
            if(left_bound <= right_bound) {
                for(int i = lower_bound; i >= upper_bound; i--) {
                    res[i][left_bound] = num;
                    num++;
                }
                left_bound++;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

