/*
 * @lc app=leetcode.cn id=377 lang=cpp
 * @lcpr version=30403
 *
 * [377] 组合总和 Ⅳ
 */

// @lc code=start
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        // dp[i] 表示凑成目标数为 i 的排列个数
        vector<unsigned long long> dp(target+1, 0);
        dp[0] = 1;  // 凑成和为 0 的方法有 1 种（啥也不选）
        // 求排列先循环背包，再循环
        for(int i = 1; i <= target; i++) {
            for(int j = 0; j < nums.size(); j++) {
                if(i >= nums[j]) dp[i] += dp[i-nums[j]];
            }
        }
        return dp[target];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n4\n
// @lcpr case=end

// @lcpr case=start
// [9]\n3\n
// @lcpr case=end

 */

