/*
 * @lc app=leetcode.cn id=416 lang=cpp
 * @lcpr version=30403
 *
 * [416] 分割等和子集
 */

// @lc code=start
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 方法一：一维DP优化
        int sum = 0;
        for(int num : nums) {
            sum += num;
        }
        if(sum % 2 != 0) return false;
        int target = sum / 2;
        // dp[i]表示能否凑出来和为i的子集
        vector<bool> dp(target+1, false);
        dp[0] = true;

        // 外层遍历物品
        for(int i = 0; i < nums.size(); i++) {
            // 内层遍历背包容量，必须用倒序保证每个物品只能用一次
            for(int j = target; j >= nums[i]; j--) {
                // 选nums[i]    dp[j] = dp[j - nums[i]]
                // 不选nums[i]  dp[j] = dp[j]
                dp[j] = dp[j] || dp[j - nums[i]];
            }
            // 如果已经可以凑出来target，直接返回，进行剪枝
            if(dp[target]) return true;
        }
        return dp[target];

        // 方法二：二维，感觉更复杂了
        // int sum = 0;
        // for(int num : nums) sum += num;
        // if(sum % 2 != 0) return false;
        // int n = nums.size();
        // int target = sum / 2;
        // // 重点：开辟 n + 1 行。dp[i][j] 表示考虑前 i 个物品（不包含第 i 个，索引从 1 开始对应）
        // vector<vector<bool>>dp(n+1, vector<bool>(target+1, false));
        
        // // 唯一的初始化：0 个物品凑出容量 0，永远是可行的
        // dp[0][0] = true; 
        // // i 从 1 开始，完美避开 i-1 越界
        // for (int i = 1; i <= n; i++) {
        //     // j 从 0 到 target 正常遍历
        //     for (int j = 0; j <= target; j++) {
        //         // 注意：由于加了虚拟行，当前物品在原数组的索引是 i - 1
        //         int current_num = nums[i - 1]; 
                
        //         if (j < current_num) {
        //             // 装不下，直接继承上一层
        //             dp[i][j] = dp[i - 1][j];
        //         } else {
        //             // 装得下，选或不选
        //             dp[i][j] = dp[i - 1][j] || dp[i - 1][j - current_num];
        //         }
        //     }
        // }
        // return dp[n][target];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,5,11,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,5]\n
// @lcpr case=end

 */

