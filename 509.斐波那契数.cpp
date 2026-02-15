/*
 * @lc app=leetcode.cn id=509 lang=cpp
 * @lcpr version=30400
 *
 * [509] 斐波那契数
 */

// @lc code=start
class Solution {
public:
    // 方法一：带备忘录的递归解法,「自顶向下」的解法
    // int fib(int n) {
    //     // 备忘录全初始化为 -1
    //     // 因为斐波那契数肯定是非负整数，所以初始化为特殊值 -1 表示未计算
    //     vector<int> memo(n + 1, -1);
    //     return dp(memo, n);
    // }
    // // 带着备忘录进行递归
    // int dp(vector<int>& memo, int n) {
    //     // base case
    //     if(n == 0 || n == 1) return n;
    //     if(memo != -1) return memo[n]; // 已经记录过，不用再计算
    //     // 在返回结果前，存入备忘录
    //     memo[n] = dp(memo, n - 1) + dp(memo, n - 2);
    //     return memo[n];
    // }

    //  方法二：DP table 的迭代解法，「自底向上」的解法
    int fib(int n) {
        if(n == 0 || n == 1) return n;
        // dp table
        vector<int> dp(n + 1);
        // base case
        dp[0] = 0, dp[1] = 1;
        // 状态转移
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 4\n
// @lcpr case=end

 */

