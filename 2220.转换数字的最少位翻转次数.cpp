/*
 * @lc app=leetcode.cn id=2220 lang=cpp
 * @lcpr version=30307
 *
 * [2220] 转换数字的最少位翻转次数
 */

// @lc code=start
class Solution {
public:
    int minBitFlips(int start, int goal) {
        // 异或把二进制位数不同的地方置为 1
        return __builtin_popcount(start ^ goal);
    }
};
// @lc code=end



/*
// @lcpr case=start
// 10\n7\n
// @lcpr case=end

// @lcpr case=start
// 3\n4\n
// @lcpr case=end

 */

