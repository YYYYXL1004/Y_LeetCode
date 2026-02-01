/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * @lcpr version=30307
 *
 * [438] 找到字符串中所有字母异位词
 */

// @lc code=start
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        unordered_map<char, int> need, window;
        for(char c : p) need[c]++;

        int left = 0, right = 0;
        int vaild = 0;
        while(right < s.size()) {
            char c = s[right];
            right++;
            if(need.count(c)) {
                window[c]++;
                if(window[c] == need[c]) {
                    vaild++;
                }
            }
            // right - left 是左闭右开的window长度
            while(right - left >= p.size()) { 
                if(vaild == need.size()) {
                    res.push_back(left);
                }

                char d = s[left];
                left++;
                if(need.count(d)) {
                    if(window[d] == need[d]) {
                        vaild--;
                    }
                    window[d]--;
                }
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "cbaebabacd"\n"abc"\n
// @lcpr case=end

// @lcpr case=start
// "abab"\n"ab"\n
// @lcpr case=end

 */

