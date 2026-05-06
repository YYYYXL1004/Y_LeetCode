/*
 * @lc app=leetcode.cn id=139 lang=cpp
 * @lcpr version=30403
 *
 * [139] 单词拆分
 */

// @lc code=start
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length()+1, false);
        dp[0] = true;

        for(int i = 1; i <= s.length(); i++) {
            for(const string& word : wordDict) {
                int len = word.length();
                // 1: dp[i-len] 是 true 说明前面部分可以被拆分
                // 2: s.substr(i-len, len) == word 说明后面部分和当前单词匹配
                if(i >= len && dp[i - len] && s.substr(i - len, len) == word) {
                    dp[i] = true;
                    break;  // 只要找到一个就行了
                }
            }
        }
        return dp[s.length()];
    }
};
// @lc code=end



/*
// @lcpr case=start
// "leetcode"\n["leet","code"]\n
// @lcpr case=end

// @lcpr case=start
// "applepenapple"\n["apple","pen"]\n
// @lcpr case=end

// @lcpr case=start
// "catsandog"\n["cats","dog","sand","and","cat"]\n
// @lcpr case=end

 */

