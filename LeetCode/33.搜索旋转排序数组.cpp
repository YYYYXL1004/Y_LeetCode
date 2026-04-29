/*
 * @lc app=leetcode.cn id=33 lang=cpp
 * @lcpr version=30403
 *
 * [33] 搜索旋转排序数组
 */

// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] == target) {
                return mid;
            }
            // nums[mid] >= nums[left]说明断崖在mid右侧,[left,mid]递增
            if(nums[mid] >= nums[l]) {
                if(nums[l] <= target && nums[mid] > target) {
                    r = mid - 1;  // 在[l, mid-1]中找
                } else {
                    l = mid + 1; // 在剩下的区间继续找
                }
            } else { // 说明断崖在mid左侧， [mid, right]递增
                if(nums[r] >= target && nums[mid] < target) {
                    l = mid + 1; // 在[mid+1, r]上找
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1; // 所有区间查找完毕，找不到返回-1
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,5,6,7,0,1,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [4,5,6,7,0,1,2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n0\n
// @lcpr case=end

 */

