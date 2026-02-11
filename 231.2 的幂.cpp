/*
 * @lc app=leetcode.cn id=231 lang=cpp
 * @lcpr version=30307
 *
 * [231] 2 的幂
 */

// @lc code=start
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0) return false;
        int cnt = 0;
        while(n) {
            n &= n - 1;
            cnt++;
        }
        return cnt == 1;
        // return __builtin_popcountl(n) == 1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 1\n
// @lcpr case=end

// @lcpr case=start
// -2147483648\n
// @lcpr case=end

// @lcpr case=start
// 3\n
// @lcpr case=end

 */

