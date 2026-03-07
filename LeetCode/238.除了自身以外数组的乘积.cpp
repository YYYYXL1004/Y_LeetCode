/*
 * @lc app=leetcode.cn id=238 lang=cpp
 * @lcpr version=30307
 *
 * [238] 除了自身以外数组的乘积
 */

// @lc code=start
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        
        // // 方法1：前缀积 + 后缀积，空间O(n)
        // vector<int> prefix(n); // 前缀积num[0...i]的积
        // prefix[0] = nums[0];
        // for(int i = 1; i <n; i++) {
        //     prefix[i] = prefix[i-1] * nums[i];
        // }

        // vector<int> suffix(n); //从右到左的前缀积nums[i..n-1]
        // suffix[n-1] = nums[n-1];
        // for(int i = n-2; i >= 0; i--) {
        //     suffix[i] = suffix[i+1] * nums[i];
        // }

        // vector<int> ans(n);
        // ans[0] = suffix[1];
        // ans[n-1] = prefix[n-2];
        // for(int i = 1; i < n-1; i++) {
        //     // 左侧积 * 右侧积
        //     ans[i] = prefix[i-1] * suffix[i+1]; 
        // }        
        // return ans;

        // 方法2：空间优化，O(1)额外空间（不算输出数组）
        vector<int> ans(n, 1);
        
        // 计算左侧所有元素的乘积 
        // 第一遍ans[i]记录nums[0..i-1]的乘积
        int left = 1;
        for(int i = 0; i < n; i++) {
            ans[i] = left;
            left *= nums[i];
        }
        
        // 计算右侧所有元素的乘积，并与左侧乘积相乘
        // 第2遍 ans[i]记录nums[0..i-1]*nums[i+1..n-1]
        int right = 1;
        for(int i = n - 1; i >= 0; i--) {
            ans[i] *= right;
            right *= nums[i];
        }
        
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [-1,1,0,-3,3]\n
// @lcpr case=end

 */

