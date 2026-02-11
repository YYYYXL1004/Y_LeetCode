/*
 * @lc app=leetcode.cn id=263 lang=cpp
 * @lcpr version=30307
 *
 * [263] 丑数
 */

// @lc code=start
class Solution {
public:
    // 任意一个大于一的正整数都可以分解成若干质数的乘积
    bool isUgly(int n) {
        if(n <= 0) return false;
        // 如果 n 是丑数，分解因子应该只有 2, 3, 5
        while(n % 2 == 0) n /= 2;
        while(n % 3 == 0) n /= 3;
        while(n % 5 == 0) n /= 5;
        // 如果能够成功分解，就是丑数
        return n == 1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 6\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

// @lcpr case=start
// 14\n
// @lcpr case=end

 */

