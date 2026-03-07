/*
 * @lc app=leetcode.cn id=724 lang=cpp
 * @lcpr version=30307
 *
 * [724] 寻找数组的中心下标
 */

// @lc code=start
class Solution {
public:
    vector<int> preSum;
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        preSum.resize(n+1);
        for(int i = 1; i <= n; i++) { // 以及记录nums[0...i-1]之和
            preSum[i] = preSum[i-1] + nums[i-1];
        }
        for(int i = 0; i < n; i++) {
            if(preSum[i] == preSum[n] - preSum[i+1]) {
                return i;
            }
        }
        return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,7,3,6,5,6]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,-1]\n
// @lcpr case=end

 */

