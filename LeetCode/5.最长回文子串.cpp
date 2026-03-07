/*
 * @lc app=leetcode.cn id=5 lang=cpp
 * @lcpr version=30307
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";
        for(int i = 0; i < s.size(); i++) {
            // 以单个字符为中心的最长回文子串
            string s1 = huiwen(s, i, i);
            // 以两个相邻字符为中心的回文子串
            string s2 = huiwen(s, i, i+1);

            // 找最长的
            res = res.size() > s1.size() ? res : s1;
            res = res.size() > s2.size() ? res : s2;
        }
        return res;
    }

    string huiwen(string s, int l, int r) {
        while(l >= 0 && r < s.size() && s[l] == s[r]) {
            // 向两边展开
            l--;
            r++;
        }
        // 此时 s[l+1,,,r-1]就是最长回文子串
        return s.substr(l+1, r-1-(l+1)+1);
    }
};
// @lc code=end



/*
// @lcpr case=start
// "babad"\n
// @lcpr case=end

// @lcpr case=start
// "cbbd"\n
// @lcpr case=end

 */

