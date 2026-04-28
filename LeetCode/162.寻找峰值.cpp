/*
 * @lc app=leetcode.cn id=162 lang=cpp
 * @lcpr version=30403
 *
 * [162] 寻找峰值
 */

// @lc code=start
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // 方法一：线性扫描
        // for(int i = 0; i < nums.size() - 1; i++) {
        //     if(nums[i] > nums[i+1]) {
        //         return i; // 找到下坡路，当前点肯定是峰值
        //     }
        // }
        // return nums.size()-1; // 都是上坡，返回最后一个元素是峰值

        // 方法二：二分查找(l <= r) 找目标，太麻烦了，改成 (l < r) 找边界
        // int l = 0, r = nums.size()-1;
        // // 闭区间 [left, right]，当 left > right 时跳出
        // while(l <= r) {
        //     int mid = l + (r - l) / 2;
        //     // 注意边界条件：mid 可能是第一个或者最后一个元素，不能越界访问
        //     bool greaterThanLeft = (mid == 0 || nums[mid] > nums[mid-1]);
        //     bool greaterThanRight = (mid == nums.size()-1 || nums[mid] > nums[mid+1]);
        //     if(greaterThanLeft && greaterThanRight) {
        //         return mid; // 找到峰值
        //     } else if(greaterThanLeft) {
        //         l = mid + 1; // 比左边大但比右边小，说明峰值在右边
        //     } else {
        //         // 剩下两种情况：
        //         // 1. 下坡 (比左边小，比右边大)，峰值在左边
        //         // 2. 谷底 (比左边小，比右边小)，峰值在左边或右边都行，随便走一边，这里我们归给去左边找
        //         r = mid - 1; 
        //     }
        // }
        // return -1; // 理论上不会走到这里，题目保证有解

        // 方法三：二分查找 (l < r) 找边界
        int l = 0, r = nums.size() - 1;
        // 循环条件改成 l < r，保证循环结束时 l == r
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] < nums[mid+1]) {
                // 上坡，峰值在右边
                l = mid + 1;
            } else {
                // 下坡，峰值在左边（包括mid）
                r = mid;
            }
        }
        return l; // 此时 l == r，指向峰值
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,3,5,6,4]\n
// @lcpr case=end

 */

