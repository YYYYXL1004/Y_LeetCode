/*
 * @lc app=leetcode.cn id=77 lang=cpp
 * @lcpr version=30307
 *
 * [77] 组合
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;

    void backtrack(int start, int n, int k) {
        // base case
        if(track.size() == k) {
            // 遍历到了第 k 层，收集当前节点的值
            res.push_back(track);
            return ;
        }

        for(int i = start; i <= n; i++) {
            track.push_back(i);
            backtrack(i + 1, n, k); 
            track.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n2\n
// @lcpr case=end

// @lcpr case=start
// 1\n1\n
// @lcpr case=end

 */

