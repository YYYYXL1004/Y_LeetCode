/*
 * @lc app=leetcode.cn id=523 lang=cpp
 * @lcpr version=30307
 *
 * [523] 连续的子数组和
 */

// @lc code=start
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> preSum(n+1);
        preSum[0] = 0;  // 哨兵
        for(int i = 1; i <= n;i++ ) {
            preSum[i] = preSum[i-1] + nums[i-1];
        }
        // 前缀和与k余数到索引的映射
        unordered_map<int, int> valToIndex;
        for(int i = 0; i <= n; i++) {  // preSum[0] 也可能是答案的一部分所以遍历从1开始
            int val = preSum[i] % k;
            if(!valToIndex.count(val)) {
                valToIndex[val] = i;
            }
            // 如果这这个前缀和已经有了对应的索引，则什么都不做
            // 因本题只想找长度最大的子数组，因此前缀和索引应该尽量小
        }
        for(int i = 1; i <=n; i++) {
            // 要使(preSum[i] - need)  % k == 0
            int need = preSum[i] % k;
            if(valToIndex.count(need)) {
                if(i - valToIndex[need] >= 2) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [23,2,4,6,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n13\n
// @lcpr case=end

 */

