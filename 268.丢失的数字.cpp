/*
 * @lc app=leetcode.cn id=268 lang=cpp
 * @lcpr version=30307
 *
 * [268] 丢失的数字
 */

// @lc code=start
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res = n; // 先放入 n(因为索引直到 n - 1 )
        
        // 因为 索引和元素相同时， 异或结果为0， 只有丢失的数字不会被异或为0
        for(int i = 0; i < n; i++) {
            res ^= i ^ nums[i];
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,0,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,1]\n
// @lcpr case=end

// @lcpr case=start
// [9,6,4,2,3,5,7,0,1]\n
// @lcpr case=end

 */

