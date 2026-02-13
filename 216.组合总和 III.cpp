/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * @lcpr version=30307
 *
 * [216] 组合总和 III
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    int trackSum = 0;

    // n是target
    void backtrack(int target, int k, int start) {
        if(trackSum == target && track.size() == k) {
            res.push_back(track);
            return ;
        }
        if(trackSum > target || track.size() > k)  return ;

        for(int i = start; i <= 9; i++) {
            track.push_back(i);
            trackSum += i;
            backtrack(target, k, i + 1);
            trackSum -= i;
            track.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        backtrack(n, k, 1);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n7\n
// @lcpr case=end

// @lcpr case=start
// 3\n9\n
// @lcpr case=end

// @lcpr case=start
// 4\n1\n
// @lcpr case=end

 */

