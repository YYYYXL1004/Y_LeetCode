/*
 * @lc app=leetcode.cn id=525 lang=cpp
 * @lcpr version=30307
 *
 * [525] 连续数组
 */

// @lc code=start
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        // // 哈希表：记录前缀和第一次出现的位置
        // unordered_map<int, int> prefixMap;
        // prefixMap[0] = -1; // 前缀和为0时，初始化对应索引为-1，方便记录长度

        // int preSum = 0;
        // int maxLen = 0;

        // for(int i = 0; i < n; i++) {
        //     preSum += (nums[i] == 0 ? -1 : 1);

        //     if(prefixMap.count(preSum)) {
        //         // 之前出现过相同的前缀和说明中间区间和为0
        //         maxLen = max(maxLen, i - prefixMap[preSum]);
        //     } else {
        //         // 第一次出现记录位置
        //         prefixMap[preSum] = i;
        //     }
        // }
        // return maxLen;  

        // 方法2：使用前缀和数组
        unordered_map<int, int> preMap; // 记录前缀和首次出现的索引位置
        vector<int> preSum(n + 1);
        preSum[0] = 0;

        for(int i = 1; i <= n; i++) {  // 修复：i <= n
            preSum[i] = preSum[i-1] + (nums[i-1] == 0 ? -1 : 1);
        }

        int maxlen = 0;
        
        for(int i = 0; i <= n; i++) {
            if(preMap.count(preSum[i])) {
                // preSum[i] == preSum[j]，区间[j, i-1]的和为0，长度为 i - j
                maxlen = max(maxlen, i - preMap[preSum[i]]);
            } else {
                // 第一次出现，记录位置
                preMap[preSum[i]] = i;
            }
        }
        
        return maxlen;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,0]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,1,1,1,1,0,0,0]\n
// @lcpr case=end

 */

