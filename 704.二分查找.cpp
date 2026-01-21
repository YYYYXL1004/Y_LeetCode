/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 */

// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;
        int mid = 0;
        while(l<=r) { // 左闭右闭
            mid = l + ((r - l)/2); // 防止溢出
            if(target < nums[mid]) {
                r = mid -1;
            } else if(target > nums[mid]) {
                l = mid +1;
            } 
            else {
                return mid;
            }
        }
        return -1;
    }
};
// @lc code=end

