/*
 * @lc app=leetcode.cn id=792 lang=cpp
 * @lcpr version=30403
 *
 * [792] 匹配子序列的单词数
 */

// @lc code=start
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // 方法一：分桶法：长字符串s只扫一遍，让所有的 words 来配合它的进度。
        // 建立26个桶, 首字母做索引
        // pair 是 {word_index, char_index}
        // vector<pair<int, int>> buckets[26];
        
        // // 初始化，把所有word按首字母扔进去对应桶
        // for(int i = 0; i < words.size(); i++) {
        //     buckets[words[i][0] - 'a'].emplace_back(i, 0); 
        // }
        // int count = 0;

        // for(char c : s) {
        //     // 核心优化：直接用swap把当前字符对应的桶 拿出来，原桶同时清空
        //     vector<pair<int, int>> curr_buckets;
        //     curr_buckets.swap(buckets[c - 'a']);

        //     for(auto& p : curr_buckets) {
        //         int word_idx = p.first;
        //         int char_idx = p.second;

        //         char_idx++;  // 砍头：指针向后移动
        //         if(char_idx == words[word_idx].size()) {
        //             // 指针走到末尾，说明子序列匹配成功
        //             count++; 
        //         } else {
        //             char next_char = words[word_idx][char_idx];
        //             buckets[next_char-'a'].emplace_back(word_idx, char_idx);
        //         }
        //     }
        // }
        // return count;


        // 方法二：二分法：先对长字符串s做一次底朝天的预处理，把它拆解成容易查询的数据字典，
        // 然后让每个 word 自己去字典里查。

        // 预处理：记录s中每个字符出现的index
        vector<vector<int>> pos(26);
        for(int i = 0; i < s.size(); i++) {
            pos[s[i] - 'a'].push_back(i);
        }

        int count = 0;
        for(auto& word : words) {
            int cur_idx = -1; // 记录当前在s中匹配到的最新位置
            bool is_sub = true;

            for(char c : word) {
                // 技巧：避免深拷贝
                const vector<int>& p = pos[c - 'a']; // 拿到这个字符出现的所有index
                // 找一个严格大于 curr_idx 的最小值
                auto it = upper_bound(p.begin(), p.end(), cur_idx);

                if(it == p.end()) {
                    is_sub = false;  // 找不到，说明相对顺序段了，或者这个字符压根没在s出现过
                    break;
                }
                // 更新当前匹配到为止，准备匹配下一个
                cur_idx = *it;
            }
            if(is_sub) count++;
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "abcde"\n["a","bb","acd","ace"]\n
// @lcpr case=end

// @lcpr case=start
// "dsahjpjauf"\n["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]\n
// @lcpr case=end

 */

