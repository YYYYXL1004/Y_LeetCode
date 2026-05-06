/*
 * @lc app=leetcode.cn id=1049 lang=cpp
 * @lcpr version=30403
 *
 * [1049] 最后一块石头的重量 II
 */

// @lc code=start
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 把物品分成两堆，让其中一堆尽可能接近总重量的一半,用0/1背包
        int sum = 0;
        for(int num : stones) sum += num;
        int target = sum / 2;
        // 找一堆和尽量接近sum/2
        // dp[j] 表示容量为 j 的背包，最多能装多重的石头
        vector<int> dp(target+1, 0);
        for(int i = 0; i < stones.size(); i++){
            for(int j = target; j >= stones[i]; j--) {
                // 依旧选或不选
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        // 较小的一推重量是dp[target],因为它限制在 sum / 2下
        return (sum - dp[target]) - dp[target];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,7,4,1,8,1]\n
// @lcpr case=end

// @lcpr case=start
// [31,26,33,21,40]\n
// @lcpr case=end

 */
