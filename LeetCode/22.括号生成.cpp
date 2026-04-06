/*
 * @lc app=leetcode.cn id=22 lang=cpp
 * @lcpr version=30402
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
public:
    string track = "";
    vector<string> res;

    void backtrace(int left, int right) {
        if(right < left) return ; // 右括号剩余数量小于左括号
        if(left <0 || right < 0) return ;
        if(left == 0 && right == 0) { // 终止条件
            res.push_back(track);
            return ;
        }

        track.push_back('(');
        backtrace(left - 1, right);
        track.pop_back(); // 回溯

        track.push_back(')');
        backtrace(left, right - 1);
        track.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        backtrace(n, n);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

