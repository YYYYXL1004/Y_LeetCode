/*
 * @lc app=leetcode.cn id=136 lang=cpp
 * @lcpr version=30307
 *
 * [136] 只出现一次的数字
 */

// @lc code=start
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        // a ^ a = 0, a ^ 0 = a
        for(int n : nums) {
            res ^= n;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [4,1,2,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

