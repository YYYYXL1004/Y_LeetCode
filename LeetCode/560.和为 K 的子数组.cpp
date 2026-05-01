/*
 * @lc app=leetcode.cn id=560 lang=cpp
 * @lcpr version=30403
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> preSum_freq; // 记录前缀和: 出现频次
        preSum_freq[0] = 1;  // 兜底，前缀和为0的情况出现一次

        int count = 0;
        int preSum = 0;
        for(int i = 0; i < n; i++) {
            preSum += nums[i];
            int target = preSum - k; // 检查之前是否有preSum-k
            if(preSum_freq.count(target)) {
                count += preSum_freq[target];
            }
            preSum_freq[preSum]++; // 每次都要更新前缀和频次
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n3\n
// @lcpr case=end

 */

