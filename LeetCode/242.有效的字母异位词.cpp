/*
 * @lc app=leetcode.cn id=242 lang=cpp
 * @lcpr version=30307
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        // 方法一：排序比较
        // if(s.size() != t.size()) return false;
        // sort(s.begin(), s.end());
        // sort(t.begin(), t.end());
        // for(int i = 0; i < s.size(); i++)
        // {
        //     if(s[i] != t[i]) {
        //         return false;
        //     }
        // }
        // return true;

        // 方法二：哈希表
        if(s.size() != t.size()) return false;
        vector<int> count1 = encode(s);
        vector<int> count2 = encode(t);
        for(int i = 0; i < count1.size(); i++) { // 比较每一个字母出现的次数
            if(count1[i] != count2[i]) {
                return false;
            }
        }
        return true;
    }

    vector<int> encode(string s) {
        vector<int> count(26, 0);
        for(char c : s) {
            int delta = c - 'a';  // 记录ACAII码差值
            count[delta]++;
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "anagram"\n"nagaram"\n
// @lcpr case=end

// @lcpr case=start
// "rat"\n"car"\n
// @lcpr case=end

 */

