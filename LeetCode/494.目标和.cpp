/*
 * @lc app=leetcode.cn id=494 lang=cpp
 * @lcpr version=30403
 *
 * [494] 目标和
 */

// @lc code=start
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(int num : nums) sum += num;
        // 正数和 P. 负数绝对值和 N
        // P + N = sum, P - N = target
        // 解方程 P = (sum + target) / 2 这就是背包容量
        // 目标值绝对值不能超过总和
        if(abs(target) > sum) return 0;
        if((sum + target) % 2 != 0) return 0;
        int P = (sum + target) / 2;
        
        // dp[j] 表示装满 j 的背包有几种方法
        vector<int> dp(P+1, 0);
        dp[0] = 1;  // 初始化，啥也不装算一个方法
        for(int i = 0; i < nums.size(); i++) {
            for(int j = P; j >= nums[i]; j--) {
                // 选或不选加起来
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }
        return dp[P];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,1,1]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */

