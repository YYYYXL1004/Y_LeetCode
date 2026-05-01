/*
 * @lc app=leetcode.cn id=523 lang=cpp
 * @lcpr version=30307
 *
 * [523] 连续的子数组和
 */

// @lc code=start
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        // vector<int> preSum(n);
        // preSum[0] = nums[0];
        // for(int i = 1; i < n; i++) {
        //     preSum[i] = preSum[i-1] + nums[i];
        // }
        // unordered_map<int, int> preMap; // 记录前缀和到索引的映射
        // preMap[0] = -1; // 当前缀和数组从0开始时，要注意preMap的初始化
        // for(int i = 0; i < n; i++) {
        //     int val = preSum[i] % k;
        //     if(!preMap.count(val)) {
        //         preMap[val] = i;
        //     }
        //     // 如果该前缀和已经有了对应索引，啥也不用干，因为要数组尽可能长
        // }
        // for(int i = 0; i < n; i++) {
        //     // 要使(preSum[i] - need)  % k == 0
        //     int need = preSum[i] % k;
        //     if(preMap.count(need)) {
        //         if(i - preMap[need] >= 2) {
        //             return true;
        //         }
        //     }
        // }
        // return false;

        // 方法二：变量代替数组
        // Hash Map 记录 {remainder (余数) : 第一次出现的 index (索引)}
        unordered_map<int, int> remainder_map;
        
        // 兜底操作：处理从 index 0 开始就刚好是 k 的倍数的子数组
        remainder_map[0] = -1;
        int prefix_sum = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            prefix_sum += nums[i];
            
            // 计算当前前缀和的余数 (Remainder)
            int remainder = prefix_sum % k;
            
            // 检查这个余数之前是否出现过
            if (remainder_map.count(remainder)) {
                // 余数出现过，说明中间这段和是 k 的倍数
                // 接着判断 Subarray (子数组) 长度是否至少为 2
                if (i - remainder_map[remainder] >= 2) {
                    return true;
                }
            } else {
                // 注意：只有当余数没出现过时才插入！
                // 如果出现过但长度不够，我们不能更新索引，因为我们要保留最早的索引，让子数组尽可能长
                remainder_map[remainder] = i;
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [23,2,4,6,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n13\n
// @lcpr case=end

 */

