/*
 * @lc app=leetcode.cn id=283 lang=cpp
 * @lcpr version=30307
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int slow = 0, fast = 0;
        while(fast < n) {
            if(nums[fast] != 0) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        for(int i = slow; i < n; i++) {
            nums[i] = 0;
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,0,3,12]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

