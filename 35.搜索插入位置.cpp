/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] 搜索插入位置
 */

// @lc code=start
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // int l = 0;
        // int r = nums.size() - 1;
        // // if(target > nums[r]) return r+1;
        // // else if(target < nums[l]) return 0;
        // while(l <= r) {
        //     int mid = l + (r - l) / 2;
        //     if(target < nums[mid]) {
        //         r = mid - 1;
        //     } else if(target > nums[mid]) {
        //         l = mid + 1;
        //     } else {
        //         return mid;
        //     }
        // }
        // return l;

        int pos = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        return pos;
    }
};
// @lc code=end

