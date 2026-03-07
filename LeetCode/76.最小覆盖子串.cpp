/*
 * @lc app=leetcode.cn id=76 lang=cpp
 * @lcpr version=30307
 *
 * [76] 最小覆盖子串
 */

// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size(), n = t.size();
        if(m < n) return "";
        unordered_map<char, int> need, window;
        for(char c : t) {
            need[c]++;
        }

        int left = 0, right = 0;
        int vaild = 0; // 记录window中的字符满足need的字符个数
        int start = 0, len = INT_MAX;
        while(right < m) {  // 左闭右开，一开始window是空的
            char c = s[right];
            // 扩大窗口
            right++;
            // 进行窗口内数据的一系列更新
            if(need.count(c)) {
                window[c]++;
                if(window[c] == need[c]) {
                    vaild++;
                }
            }

            // 判断左窗口是否要收缩
            while(vaild == need.size()) {
                // 更新最小覆盖子串
                if(right - left < len) {
                    start = left;
                    len = right - left;
                }
                // d是要移除窗口的字符
                char d = s[left];
                // 缩小窗口
                left++;
                if(need.count(d)) {
                    if(window[d] == need[d]) {
                        vaild--;
                    }
                    window[d]--;
                }
            }
        }
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ADOBECODEBANC"\n"ABC"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"a"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"aa"\n
// @lcpr case=end

 */

