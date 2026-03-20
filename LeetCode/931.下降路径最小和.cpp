/*
 * @lc app=leetcode.cn id=931 lang=cpp
 * @lcpr version=30400
 *
 * [931] 下降路径最小和
 */

// @lc code=start
#include <vector>
class Solution {
public:
    // 能用 DP table 的情况：状态是连续的索引（如数组下标），转移逻辑清晰 → 推荐用 DP table，代码简洁
    // 适合用备忘录递归的情况：状态不规则、部分状态不会被访问、转移逻辑复杂 → 递归更灵活
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> dp(n, vector<int>(n));
        // base case 第一行
        for(int i = 0; i < n; i++) {
            dp[0][i] = matrix[0][i];
        }

        for(int i = 1; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int left = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
                int mid = dp[i - 1][j];
                int right = (j < n - 1) ? dp[i - 1][j + 1] : INT_MAX;
                dp[i][j] = matrix[i][j] + min({left, mid, right});
            }
        }
        int res = INT_MAX;
        for(int i = 0; i < n; i++) {
            res = min(res, dp[n - 1][i]); // 遍历最后一行所有列
        }
        return res;
    }

    // 方法一： 带备忘录的从顶向下
    // vector<vector<int>> memo;
    // // 从第一行（matrix[0][..]）向下落，落到位置 matrix[i][j] 的最小路径和为 dp(matrix, i, j)。
    // int dp(vector<vector<int>>& matrix, int i, int j) {
    //     if(i < 0 || j < 0 || i >= matrix.size() || j >= matrix[0].size()) {
    //         return INT_MAX;
    //     }
    //     if(i == 0) return matrix[0][j]; // base case从第0行开始
    //     if(memo[i][j] != 22222) return memo[i][j]; // 备忘录有记录就返回
    //     // memo[i][j] = matrix[i][j] + min(dp(matrix, i - 1, j - 1), min(dp(matrix, i - 1, j), dp(matrix, i - 1, j + 1)));
        
    //     memo[i][j] = matrix[i][j] + min({dp(matrix, i - 1, j - 1), dp(matrix, i - 1, j), dp(matrix, i - 1,  j + 1)});
    //     return memo[i][j];
    // }

    // int minFallingPathSum(vector<vector<int>>& matrix) {
    //     int n = matrix[0].size();
    //     int res = INT_MAX;
    //     memo = vector<vector<int>>(n, vector<int>(n, 22222)); //大于10000即可
    //     for(int j = 0; j < n; j++) {
    //         // 终点可能在 matrix[n-1] 的任意一列
    //         res = min(res, dp(matrix, n - 1, j));
    //     }
    //     return res;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,1,3],[6,5,4],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[-19,57],[-40,-5]]\n
// @lcpr case=end

 */

