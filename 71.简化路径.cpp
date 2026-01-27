/*
 * @lc app=leetcode.cn id=71 lang=cpp
 * @lcpr version=30307
 *
 * [71] 简化路径
 */

// @lc code=start
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack; // 用vector模拟栈，方便最后拼接
        stringstream ss(path);
        string token;

        // 按照'/'分割路径
        while(getline(ss, token, '/')) {
            if(token.empty() || token == ".") {
                // 空字符串（连续斜杆）或当前目录,跳过
                continue;
            } else if(token == "..") {
                // 父目录，弹出栈顶（如果栈非空）
                if(!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                // 有效目录名（包括"..."等），压入栈
                stack.push_back(token);
            }
        }

        // 重建简化路径
        string res;
        for(const string& dir : stack) {
            res += '/' + dir;
        }
        
        // 如果结果为空，返回根目录
        return res.empty() ? "/" : res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "/home/"\n
// @lcpr case=end

// @lcpr case=start
// "/home//foo/"\n
// @lcpr case=end

// @lcpr case=start
// "/home/user/Documents/../Pictures"\n
// @lcpr case=end

// @lcpr case=start
// "/../"\n
// @lcpr case=end

// @lcpr case=start
// "/.../a/../b/c/../d/./"\n
// @lcpr case=end

 */

