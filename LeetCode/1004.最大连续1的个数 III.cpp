/*
 * @lc app=leetcode.cn id=1004 lang=cpp
 * @lcpr version=30400
 *
 * [1004] 最大连续1的个数 III
 */

// @lc code=start
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int res = 0;
        int left = 0, right = 0;
        int windowSum = 0; // 窗口内1的个数
        while(right < nums.size()) {
            if(nums[right] == 1) {
                windowSum++;
            }
            right++;
            // 窗口内非1数量大于可修改的k，收缩窗口
            while(right - left - windowSum > k) {
                if(nums[left] == 1) {
                    windowSum--;
                }
                left++;
            }
            // 此时窗口一定是满足条件的，统计结果
            res = max(res, right - left);
        }
        return res;
        // int res = 0;
        // int left = 0, right = 0, len = 0;
        // while(right < nums.size()) {
        //     int num = nums[right];
        //     right++;
        //     if(num == 1) {
        //         len++;
        //     } else if(k >= 0) {
        //         len++;
        //         k--; // 扩大窗口，消耗一次翻转机会
        //     }
        //     while(k < 0 && left < right) {
        //         int d = nums[left];
        //         left++;
        //         if(d == 1) {
        //             len--;
        //         } else {
        //             len--;
        //             k++;
        //         }
        //     }
        //     res = max(res, len); // 此时k>=0, 并且窗口全是1
        // }
        // return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,0,0,0,1,1,1,1,0]\n2\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1]\n3\n
// @lcpr case=end

 */

