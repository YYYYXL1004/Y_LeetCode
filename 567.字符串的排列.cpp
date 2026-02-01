/*
 * @lc app=leetcode.cn id=567 lang=cpp
 * @lcpr version=30307
 *
 * [567] 字符串的排列
 */

// @lc code=start
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if(m < n) return false;
        unordered_map<char, int> need, window;
        for(char c : s1) need[c]++;
        
        int left = 0, right = 0;
        int vaild = 0;
        while(right < m) {
            char c = s2[right];
            right++;
            if(need.count(c)) {
                window[c]++;
                if(window[c] == need[c]) {
                    vaild++;
                }
            }
            // 判断左侧窗口是否要收缩，要在宽度为n窗口下满足条件才可以
            while(right - left >= n) {
                // 必须在这里判断：此时窗口大小恰好为n，且满足字符频率要求
                if(vaild == need.size()) {
                    return true;
                }
                char d = s2[left];
                left++;

                if(need.count(d)) {
                    if(window[d] == need[d]) {
                        vaild--;
                    }
                    window[d]--;
                }
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ab"\n"eidbaooo"\n
// @lcpr case=end

// @lcpr case=start
// "ab"\n"eidboaoo"\n
// @lcpr case=end

 */

