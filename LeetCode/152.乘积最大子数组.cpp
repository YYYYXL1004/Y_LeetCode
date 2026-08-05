/*
 * @lc app=leetcode.cn id=152 lang=cpp
 * @lcpr version=30403
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0], maxn = nums[0], minn = nums[0];
        // 维护当前局部最大值与最小值
        for(int i = 1; i < nums.size(); i++) {
            int n = nums[i];
            if(n < 0) {  // 遇到负数先反转
                swap(maxn, minn);
            }
            maxn = max(n, maxn * n);
            minn = min(n, minn * n);

            res = max(res, maxn);
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,-2,4]\n
// @lcpr case=end

// @lcpr case=start
// [-2,0,-1]\n
// @lcpr case=end

 */

