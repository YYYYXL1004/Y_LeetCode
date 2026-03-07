/*
 * @lc app=leetcode.cn id=713 lang=cpp
 * @lcpr version=30400
 *
 * [713] 乘积小于 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int window = 1;
        int left = 0, right = 0;
        int res = 0;
        while(right < nums.size()) {
            window *= nums[right];
            right++;
            // 缩小窗口
            while(window >= k && left < right) {
                window /= nums[left];
                left++;
            } 
            // 现在肯定是合法的窗口，因为是在收缩窗口后
            // 计算以以当前 right-1 位置结尾的合法子数组有多少个，因为right是单调递增的不会重复
            // 10 对应 1个子数组 [10]
            // 10, 5 对应两个子数组 [10, 5] [5]
            // 5, 2 对应两个 [5, 2] [2]
            // 5, 2, 6对应三个 [5, 2, 6] [2, 6] [6]
            res += right - left;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,5,2,6]\n100\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n0\n
// @lcpr case=end

 */

