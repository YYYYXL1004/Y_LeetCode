/*
 * @lc app=leetcode.cn id=387 lang=cpp
 * @lcpr version=30307
 *
 * [387] 字符串中的第一个唯一字符
 */

// @lc code=start
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> mp;
        for(auto c : s) {
            mp[c]++;
        }
        for(int i = 0; i < s.size(); i++) {
            if(mp[s[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "leetcode"\n
// @lcpr case=end

// @lcpr case=start
// "loveleetcode"\n
// @lcpr case=end

// @lcpr case=start
// "aabb"\n
// @lcpr case=end

 */

