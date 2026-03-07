/*
 * @lc app=leetcode.cn id=20 lang=cpp
 * @lcpr version=30307
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> left;
        for(char c : s) {
            if(c == '(' || c == '{' || c == '[') {
                left.push(c); // 左括号入栈
            } else { // 字符c是右括号
                if(!left.empty() && leftOf(c) == left.top()) {
                    left.pop(); // 匹配成功，弹出栈顶
                } else { // 和最近的左括号不匹配
                    return false;
                }
            }
        }
        // 是否所有的左括号都被匹配了
        return left.empty();
    }

    char leftOf(char c) {
        if(c == '}') return '{';
        else if(c == ')') return '(';
        return '[';
    }
};
// @lc code=end



/*
// @lcpr case=start
// "()"\n
// @lcpr case=end

// @lcpr case=start
// "()[]{}"\n
// @lcpr case=end

// @lcpr case=start
// "(]"\n
// @lcpr case=end

// @lcpr case=start
// "([])"\n
// @lcpr case=end

// @lcpr case=start
// "([)]"\n
// @lcpr case=end

 */

