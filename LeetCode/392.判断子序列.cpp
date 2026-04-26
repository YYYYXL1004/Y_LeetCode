/*
 * @lc app=leetcode.cn id=392 lang=cpp
 * @lcpr version=30403
 *
 * [392] 判断子序列
 */

// @lc code=start
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while(i < s.size() && j < t.size()) {
            if(s[i] == t[j]) {
                i++;
            }
            j++;
        }
        // 如果遍历完t, s还没遍历完，说明t不是s的子序列
        return i == s.size();
    }
};
// @lc code=end



/*
// @lcpr case=start
// "abc"\n"ahbgdc"\n
// @lcpr case=end

// @lcpr case=start
// "axc"\n"ahbgdc"\n
// @lcpr case=end

 */

