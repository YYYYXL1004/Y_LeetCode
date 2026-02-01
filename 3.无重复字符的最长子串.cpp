/*
 * @lc app=leetcode.cn id=3 lang=cpp
 * @lcpr version=30307
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;

        int left = 0, right = 0;
        int res = 0;

        while(right < s.size()) {
            char c = s[right];
            right++;
            window[c]++;
            // 窗口收缩的条件,收缩完保证一定没有重复元素
            while(window[c] > 1) {
                char d = s[left];
                left++;
                window[d]--;
            }
            // 这里更新答案
            res = max(res, right - left);
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "abcabcbb"\n
// @lcpr case=end

// @lcpr case=start
// "bbbbb"\n
// @lcpr case=end

// @lcpr case=start
// "pwwkew"\n
// @lcpr case=end

 */

