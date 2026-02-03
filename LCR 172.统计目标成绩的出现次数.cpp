/*
 * @lc app=leetcode.cn id=LCR 172 lang=cpp
 * @lcpr version=30307
 *
 * [LCR 172] 统计目标成绩的出现次数
 */

// @lc code=start
class Solution {
public:
    int countTarget(vector<int>& scores, int target) {
        int res = 0;
        for(int i : scores) {
            if(i == target) res++;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,2,3,4,4,4,5,6,6,8]\n4\n
// @lcpr case=end

 */

