/*
 * @lc app=leetcode.cn id=974 lang=cpp
 * @lcpr version=30403
 *
 * [974] 和可被 K 整除的子数组
 */

// @lc code=start
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> preSum_freq;
        preSum_freq[0] = 1;

        int preSum = 0;
        int count = 0;

        for(int i = 0; i < n; i++) {
            preSum += nums[i];
            // (preSum[j] - preSum[i]) % k = 0
            // preSum[j] = preSum[i] % k
            int need = (preSum % k + k) % k; // C++的负数取模有点问题
            if(preSum_freq.count(need)) {
                count += preSum_freq[need];
            }
            preSum_freq[need]++;
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,5,0,-2,-3,1]\n5\n
// @lcpr case=end

// @lcpr case=start
// [5]\n9\n
// @lcpr case=end

 */

