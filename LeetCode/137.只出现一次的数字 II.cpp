/*
 * @lc app=leetcode.cn id=137 lang=cpp
 * @lcpr version=30307
 *
 * [137] 只出现一次的数字 II
 */

// @lc code=start
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // 方法一：统计每一位
        // 对于每一位，统计所有数字在该位上 1 出现的次数
        // 如果次数 % 3 != 0，说明单独的数在该位为 1
        
        // nums = [2, 2, 3, 2]
        // 二进制表示：
        // 2 = 010
        // 2 = 010
        // 3 = 011  ← 只出现1次
        // 2 = 010
        
        // 逐位统计：
        // 位2: 0+0+0+0 = 0 → 0 % 3 = 0 → res 该位为 0
        // 位1: 1+1+1+1 = 4 → 4 % 3 = 1 → res 该位为 1
        // 位0: 0+0+1+0 = 1 → 1 % 3 = 1 → res 该位为 1
        
        // res = 0b011 = 3 ✓

        int res = 0;
        for(int i = 0; i < 32; i++) {
            int count = 0;
            for(int n : nums) {
                count += (n >> i) & 1; // // 统计第 i 位是 1 的数量
            }
            if(count % 3 != 0) res |= (1 << i); // 该位设置成q1
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,2,3,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,0,1,0,1,99]\n
// @lcpr case=end

 */

