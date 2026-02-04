/*
 * @lc app=leetcode.cn id=14 lang=cpp
 * @lcpr version=30307
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        int len = 201; // 最小的字符串长
        for(int i = 0; i < strs.size(); i++) {
            len = min(len, int(strs[i].size())); // 不加强制字符转化会报错
        } // strs[i].size()返回size_t类型数据（无符号整数）
        int i = 0;
        for(int j = 0; j < len; j++) {
            char c = strs[0][j];
            for(int i = 1; i < strs.size(); i++) {
                if(strs[i][j] != c) {
                    return strs[0].substr(0, j); // 返回前j个字符
                }
            }
        }
        return strs[0].substr(0, len); // 全部匹配
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["flower","flow","flight"]\n
// @lcpr case=end

// @lcpr case=start
// ["dog","racecar","car"]\n
// @lcpr case=end

 */

