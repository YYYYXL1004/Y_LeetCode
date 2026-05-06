/*
 * @lc app=leetcode.cn id=279 lang=cpp
 * @lcpr version=30403
 *
 * [279] 完全平方数
 */

// @lc code=start
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        // 因为不是求排列， 所以两个循环顺序可颠倒
        for(int i = 1; i <= n; i++) {  // 遍历背包
            for(int j = 1; j * j <= i; j++) { // 遍历物品
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 12\n
// @lcpr case=end

// @lcpr case=start
// 13\n
// @lcpr case=end

 */

