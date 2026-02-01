/*
 * @lc app=leetcode.cn id=1658 lang=cpp
 * @lcpr version=30307
 *
 * [1658] 将 x 减到 0 的最小操作数
 */

// @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size(), sum = 0;
        for(int i : nums) sum += i;
        int target = sum - x; // 转化成求子数组目标和

        int left = 0, right = 0;
        int windowSum = 0; // 记录窗口内所有元素的和
        int len = -1;
        while(right < n) {
            // 扩大窗口
            windowSum += nums[right];
            right++;

            // 缩小窗口
            while(windowSum > target && left < right) {
                windowSum -= nums[left];
                left++;
            }
            // 寻找目标子数组
            if(windowSum == target) {
                len = max(len, right - left);
            }
        }
        return len == -1 ? -1 : n - len;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,4,2,3]\n5\n
// @lcpr case=end

// @lcpr case=start
// [5,6,7,8,9]\n4\n
// @lcpr case=end

// @lcpr case=start
// [3,2,20,1,1,3]\n10\n
// @lcpr case=end

 */

