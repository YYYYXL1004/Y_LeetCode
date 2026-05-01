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
        // 方法一：使用前缀和数组+哈希表
        unordered_map<int, int> preMap; // 哈希表：记录前缀和第一次出现的位置
        preMap[0] = -1;  // 对于整个数组前缀和为0的情况
        vector<int> preSum(n);
        preSum[0] = (nums[0] == 0 ? -1 : 1);
        for(int i = 1; i < n; i++) {
            preSum[i] = preSum[i - 1] + (nums[i] == 0 ? -1 : 1);
        }
        int maxlen = 0;
        for(int i = 0; i < n; i++) {
            if(preMap.count(preSum[i])) {
                // 再次出现相同的前缀和，说明[preMap[preSum[i]]+1, i]之间和为0
                maxlen = max(maxlen, i - preMap[preSum[i]]);
            } else {
                preMap[preSum[i]] = i; // 第一次出现，记录前缀和对应索引
            }
        }
        return maxlen;

        // 方法二：前缀和数组优化成一个变量记录
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

