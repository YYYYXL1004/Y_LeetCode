/*
 * @lc app=leetcode.cn id=518 lang=cpp
 * @lcpr version=30403
 *
 * [518] 零钱兑换 II
 */

// @lc code=start
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // 方法一：完全背包（二维写法
        // int n = coins.size();
        // // dp[i][j] 是使用前i个硬币可以凑出来j的方案数
        // vector<vector<unsigned int>> dp(n+1, vector<unsigned int>(amount+1, 0));
        // // base case
        // for(int i = 0; i <= n; i++) dp[i][0] = 1;
        // for(int i = 1; i <= n; i++) {
        //     for(int j = 1; j <= amount; j++) {
        //         // 背包有空间
        //         if(j - coins[i-1] >= 0) {
        //             // 还是装或不装两种情况相加
        //             dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i-1]];
        //         } else {
        //             dp[i][j] = dp[i-1][j];
        //         }
        //     }
        // }
        // return dp[n][amount];

        // 方法二：一维优化
        // dp[j] 表示凑出总金额j的组合数
        vector<unsigned long long> dp(amount+1, 0);
        dp[0] = 1;  // 啥也不用 总金额为0
        for(int i = 0; i < coins.size(); i++) {
            for(int j = coins[i]; j <= amount; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 5\n[1,2,5]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[2]\n
// @lcpr case=end

// @lcpr case=start
// 10\n[10]\n
// @lcpr case=end

 */

