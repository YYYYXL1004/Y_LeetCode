/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution {
public:
    int findLeft(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        int res = -1;
        while(l<=r) {
            int mid = l + (r-l)/2;
            if(target == nums[mid]) {
                res = mid; //记录位置
                r = mid - 1; // 继续向左找
            } else if(target > nums[mid]) {
                l = mid +1;
            } else {
                r = mid -1;
            }
        }
        return res;
    }
    int findRight(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        int res = -1;
        while(l<=r) {
            int mid = l + (r-l)/2;
            if(target == nums[mid]) {
                res = mid;
                l = mid + 1;
            } else if(target > nums[mid]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1, -1};;
        return {findLeft(nums, target), findRight(nums, target)};
    }
};
// @lc code=end

