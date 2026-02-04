/*
 * @lc app=leetcode.cn id=977 lang=cpp
 * @lcpr version=30307
 *
 * [977] 有序数组的平方
 */

// @lc code=start
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);

        // 方法一：直接sort,O(nlogn)
        // for(int i = 0; i < n; i++) {
        //     res[i] = nums[i] * nums[i];
        // }
        // sort(res.begin(), res.end());

        // 方法二：双指针
        int i = 0, j = n - 1;  // 两个指针分别初始化在正负子数组绝对值最大的元素索引
        int p = n - 1;  // 从后往前排的
        while(i <= j) {
            if(abs(nums[i]) >= nums[j]) {
                res[p] = nums[i] * nums[i];
                i++;
            } else {
                res[p] = nums[j] * nums[j];
                j--;
            }
            p--;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-4,-1,0,3,10]\n
// @lcpr case=end

// @lcpr case=start
// [-7,-3,2,3,11]\n
// @lcpr case=end

 */

