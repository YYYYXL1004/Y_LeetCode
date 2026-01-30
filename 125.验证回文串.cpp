/*
 * @lc app=leetcode.cn id=125 lang=cpp
 * @lcpr version=30307
 *
 * [125] 验证回文串
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(string s) {
        string clean = "";
        // for(char c : s) {
        //     int cnum = (int)c;
        //     if(cnum >= 'a' && cnum <= 'z' || cnum >= '0' && cnum <= '9') {
        //         clean += c;
        //     } else if(cnum >= 'A' && cnum <= 'Z') {
        //         clean += tolower(c);
        //     } else {
        //         clean += "";
        //     }
        // }

        for(char c : s) {
            if(isalnum(c)) { // 判断是不是字母和数字
                clean += tolower(c);
            }
        }

        int n = clean.size();
        for(int i = 0; i < n; i++) {
            if(clean[i] != clean[n-1-i]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "A man, a plan, a canal: Panama"\n
// @lcpr case=end

// @lcpr case=start
// "race a car"\n
// @lcpr case=end

// @lcpr case=start
// " "\n
// @lcpr case=end

 */

