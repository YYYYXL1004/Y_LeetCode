/*
 * @lc app=leetcode.cn id=338 lang=cpp
 * @lcpr version=30307
 *
 * [338] 比特位计数
 */

// @lc code=start
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1);
        for(int i = 0; i <= n; i++) {
            res[i] = __builtin_popcount(i);
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 5\n
// @lcpr case=end

 */

