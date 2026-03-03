/*
 * @lc app=leetcode.cn id=424 lang=cpp
 * @lcpr version=30400
 *
 * [424] 替换后的最长重复字符
 */

// @lc code=start
class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0;
        int left = 0, right = 0, windowMax = 0; //记录window中最多字符的个数
        vector<int> windowCount(26, 0);  // 记录window中各个字符的个数

        while(right < s.size()) {
            int c = s[right] - 'A';
            windowCount[c]++;
            windowMax = max(windowMax, windowCount[c]);
            right++;

            while(right - left - windowMax > k) {
                int d = s[left] - 'A';
                windowCount[d]--;
                left++;
                // 收缩时 windowMax 可能不准，但不影响正确性，
                // 因为我们只在扩张时记录答案，而扩张时 windowMax 一定是对的。
            }
            res = max(res, right - left);
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ABAB"\n2\n
// @lcpr case=end

// @lcpr case=start
// "AABABBA"\n1\n
// @lcpr case=end

 */

