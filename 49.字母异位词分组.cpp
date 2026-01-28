/*
 * @lc app=leetcode.cn id=49 lang=cpp
 * @lcpr version=30307
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string> > codeToGroup;
        for(auto & s : strs) {
            string code = encode(s);
            codeToGroup[code].push_back(s);
        }

        // 获取结果
        vector<vector<string> > res;
        for(auto& group: codeToGroup) { // group是pair<string, vector<string>>
            res.push_back(group.second);
        }
        return res;
    }

    string encode(const string& s){
        // // 利用每个字符的出现次数进行编码
        // string count(26, '0');
        // for(char c : s) {
        //     int delta = c - 'a';
        //     count[delta]++;
        // }
        // return count;
        
        // 或者使用排序后的字符串作为key
        string key = s;
        sort(key.begin(), key.end());
        return key;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["eat","tea","tan","ate","nat","bat"]\n
// @lcpr case=end

// @lcpr case=start
// [""]\n
// @lcpr case=end

// @lcpr case=start
// ["a"]\n
// @lcpr case=end

 */

