/*
 * @lc app=leetcode.cn id=461 lang=cpp
 * @lcpr version=30307
 *
 * [461] 汉明距离
 */

// @lc code=start
class Solution {
public:
    int hammingDistance(int x, int y) {
        // 方法一：逐位相比
        // int cnt = 0;
        // while(x || y) {
        //     cnt += (x & 1) == (y & 1) ? 0 : 1;
        //     x >>= 1;
        //     y >>= 1;   
        // }
        // return cnt;

        // 方法二：异或 + popcount
        // 关键：x ^ y 得到不同位的掩码，统计其中 1 的个数
        return __builtin_popcount(x ^ y);
    }
};
// @lc code=end



/*
// @lcpr case=start
// 1\n4\n
// @lcpr case=end

// @lcpr case=start
// 3\n1\n
// @lcpr case=end

 */

