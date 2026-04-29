/*
 * @lc app=leetcode.cn id=81 lang=cpp
 * @lcpr version=30403
 *
 * [81] 搜索旋转排序数组 II
 */

// @lc code=start
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        // 方法一：直接暴力查找
        // auto it = find(nums.begin(), nums.end(), target);
        // if(it != nums.end()) return true;
        // else return false;

        // 方法二：二分
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] == target) {
                return true;
            }
            // 遇到无法判断的情况，收缩边界
            if(nums[l] == nums[mid] && nums[mid] == nums[right]) {
                l++; r--;
            } else if(nums[l] <= nums[mid]) { // 左半区间递增
                if(nums[l] <= target && nums[mid] > target) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if(nums[mid] < target && nums[r] >= target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,5,6,0,0,1,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [2,5,6,0,0,1,2]\n3\n
// @lcpr case=end

 */

