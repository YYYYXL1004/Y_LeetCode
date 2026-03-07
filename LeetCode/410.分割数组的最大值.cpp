/*
 * @lc app=leetcode.cn id=410 lang=cpp
 * @lcpr version=30307
 *
 * [410] 分割数组的最大值
 */

// @lc code=start
class Solution {
public:
    // 题目转化：你只有一艘货船，现在有若干货物，每个货物的重量是 nums[i]，
    // 现在你需要在 k 天内将这些货物运走，请问你的货船的最小载重是多少？

    // 当子数组和的最大值为 x 时，需要 f(x) 个子数组
    int f(vector<int>& nums, int x) {
        int count = 0;
        for(int i = 0; i < nums.size(); ) {
            int cap = x;
            while(i < nums.size()) {
                if(cap < nums[i]) break;
                else cap -= nums[i];
                i++;
            }
            count++;
        }
        return count;
    }

    int splitArray(vector<int>& nums, int k) {
        int left = 0, right = 0;
        for(int i : nums) {
            left = max(i, left);
            right += i;
        }
        while(left <= right) {  // 转化成求左边界的问题
            int mid = left + (right - left) / 2;
            if(f(nums, mid) <= k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [7,2,5,10,8]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

 */

