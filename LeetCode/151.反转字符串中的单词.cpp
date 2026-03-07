/*
 * @lc app=leetcode.cn id=151 lang=cpp
 * @lcpr version=30307
 *
 * [151] 反转字符串中的单词
 */

// @lc code=start
class Solution {
public:
    // 方法2：原地修改 - 先整体反转，再逐词反转
    string reverseWords(string s) {
        // 快慢指针 去掉多余空格
        int slow = 0;
        for(int fast = 0; fast <s.size(); fast++) {
            if(s[fast] != ' ') {
                if(slow != 0) s[slow++] = ' ';  // 修复：+= 改为 =
                while(fast < s.size() && s[fast] != ' ') {
                    s[slow++] = s[fast++];
                }
            }
        }
        s.resize(slow); 
        // 反转整个字符串
        reverse(s, 0, s.size()-1);
        // 反转每个单词
        int start = 0;
        for(int i = 0; i <= s.size(); i++) {
            // 最后一个单词后面没有空格，所以不会触发 s[i] == ' '
            // 需要 i == s.size() 来触发最后一个单词的反转
            if(i == s.size() || s[i] == ' ') {
                reverse(s, start, i-1);
                start = i + 1;
            }
        }
        return s;
    }
    // 反转区间
    void reverse(string &s, int left, int right) {
        while(left < right) {
            swap(s[left++], s[right--]);
        }
    }
    /*
    // 方法1：使用stringstream
    string reverseWords(string s) {
        stringstream ss;
        // 先清洗数据
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if(c != ' ') {
                ss << c; // 不是空格就保留
            } else if(!ss.str().empty() && ss.str().back()!= ' ') {
                ss << " "; // 单词间保留一个空格
            }
        }
        string str = ss.str();
        if(!str.empty() && str.back() == ' ') {
            str.pop_back(); // 如果末尾有空格，去除
        }
        
        // 分割单词并逆序
        vector<string> words;
        stringstream ss2(str);
        string word;
        while(ss2 >> word) {
            words.push_back(word);
        }
        
        // 逆序拼接
        string res;
        for(int i = words.size()-1; i >= 0; i--) {
            res += words[i];
            if(i > 0) res += " ";
        }
        return res;
    }
    */
};
// @lc code=end



/*
// @lcpr case=start
// "the sky is blue"\n
// @lcpr case=end

// @lcpr case=start
// "  hello world  "\n
// @lcpr case=end

// @lcpr case=start
// "a good   example"\n
// @lcpr case=end

 */

