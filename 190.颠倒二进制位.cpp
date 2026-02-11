/*
 * @lc app=leetcode.cn id=190 lang=cpp
 * @lcpr version=30307
 *
 * [190] 颠倒二进制位
 */

// @lc code=start
class Solution {
public:
    int reverseBits(int n) {
        int res = 0;
        for(int i = 0; i < 32; i++) {
            res <<= 1; // 左移res腾出来空间
            res |= (n & 1); // 取出n的最后一位放到 res最后一位
            n >>= 1;  // 右移n, 处理下一位
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 43261596\n
// @lcpr case=end

// @lcpr case=start
// 2147483644\n
// @lcpr case=end

 */

