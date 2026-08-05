/*
 * @lc app=leetcode.cn id=128 lang=cpp
 * @lcpr version=30403
 *
 * [128] 最长连续序列
 */

// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_set<int> s(nums.begin(), nums.end());
        for(int num : s) {
            if(!s.count(num-1)) { // 找不到前一个连续的值，说明这是最开始的
                int cur = num;
                while(s.count(cur+1)) {
                    cur++;
                }
                res = max(res, cur - num + 1);
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [100,4,200,1,3,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,3,7,2,5,8,4,6,0,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,0,1,2]\n
// @lcpr case=end

 */

