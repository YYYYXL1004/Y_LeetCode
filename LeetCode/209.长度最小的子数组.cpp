/*
 * @lc app=leetcode.cn id=209 lang=cpp
 * @lcpr version=30403
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // 方法一：滑动窗口 O(N)
        // int n = nums.size();
        // int minlen = INT_MAX;
        // int l = 0;
        // int sum = 0;

        // for(int r = 0; r < n; r++) {
        //     sum += nums[r];
        //     // 大于等于时尝试缩小
        //     while(sum >= target) {
        //         minlen = min(minlen, r - l + 1);  // [l, r]长度为r-l+1
        //         sum -= nums[l];
        //         l++;   // 缩小窗口
        //     }
        // }
        // return (minlen == INT_MAX) ? 0 : minlen;

        // 方法二：前缀和+二分查找 O(n logn)
        int n = nums.size();
        vector<int> preSum(n+1);
        preSum[0] = 0;
        for(int i = 1; i <= n; i++) {
            preSum[i] = preSum[i-1] + nums[i-1]; 
        }
        // 因为元素恒大于1，所以前缀和数组单调递增
        // 子数组[l, r]的和是preSum[r+1] - preSum[l]
        // 找preSum[r+1] - preSum[l] >= target 使得 r- l + 1最小
        // preSum[r+1] >= preSum[l] + target  对于每一个l，找第一个r
        int minlen = INT_MAX;
        for(int i = 0; i < n; i++) {
            int need = preSum[i] + target;
            auto it = lower_bound(preSum.begin()+ i + 1, preSum.end(), need);
            if(it == preSum.end()) continue;
            else {
                int r = it - preSum.begin();  // it是r+1 [l, r]
                minlen = min(minlen, r - i);
            }
        }
        return minlen == INT_MAX ? 0 : minlen;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 7\n[2,3,1,2,4,3]\n
// @lcpr case=end

// @lcpr case=start
// 4\n[1,4,4]\n
// @lcpr case=end

// @lcpr case=start
// 11\n[1,1,1,1,1,1,1,1]\n
// @lcpr case=end

 */

