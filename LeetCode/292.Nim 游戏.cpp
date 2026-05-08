/*
 * @lc app=leetcode.cn id=292 lang=cpp
 * @lcpr version=30403
 *
 * [292] Nim 游戏
 */

// @lc code=start
class Solution {
public:
    bool canWinNim(int n) {
        if (n % 4 != 0) {
            return true;
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

// @lcpr case=start
// 2\n
// @lcpr case=end

 */

