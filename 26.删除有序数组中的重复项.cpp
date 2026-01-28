/*
 * @lc app=leetcode.cn id=26 lang=cpp
 * @lcpr version=30307
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int slow = 0, fast = 0;
        while(fast < n) {
            if(nums[fast] != nums[slow]) {
                slow++;
                // 维护nums[0..slow]无重复
                nums[slow] = nums[fast];
            }
            fast++;
        }
        return slow + 1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,2,2,3,3,4]\n
// @lcpr case=end

 */

