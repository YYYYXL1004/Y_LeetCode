/*
 * @lc app=leetcode.cn id=153 lang=cpp
 * @lcpr version=30403
 *
 * [153] 寻找旋转排序数组中的最小值
 */

// @lc code=start
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        // 找谷底,找到nums[mid+1] < nums[mid]即可
        // 左闭右开, l在搜索范围内
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] > nums[r]) {  // 说明谷底在mid右侧
                l = mid+1;
            } else {    // mid 落在断崖右边（或本身就是最小值），最小值在 [left, mid]
                r = mid;
            }
        }
        return nums[l];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,4,5,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [4,5,6,7,0,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [11,13,15,17]\n
// @lcpr case=end

 */

