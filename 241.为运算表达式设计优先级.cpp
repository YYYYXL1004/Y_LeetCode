/*
 * @lc app=leetcode.cn id=241 lang=cpp
 * @lcpr version=30400
 *
 * [241] 为运算表达式设计优先级
 */

// @lc code=start
class Solution {
public:
    // 备忘录，存取算式string对应的结果
    unordered_map<string, vector<int>> memo;
    vector<int> diffWaysToCompute(string expression) {
        if(memo.count(expression)) return memo[expression];
        vector<int> res;
        for(size_t i = 0; i < expression.size() ; i++) {
            char c = expression[i];
            // 扫描算式中的运算符
            if(c == '-' || c == '+' || c == '*') {
                // 分
                // 以运算符为中心，分割成两个字符串，分别递归训练
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i + 1));

                // 治
                // 通过子问题的结果，合成原问题的结果
                for(int a : left) {
                    for(int b : right) {
                        if(c == '-') {
                            res.push_back(a - b);
                        } else if(c == '+') {
                            res.push_back(a + b);
                        } else if(c == '*') {
                            res.push_back(a * b);
                        }
                    }
                }
            }
        }
        // base case
        // 如果res为空，说明expression是一个数字，没有运算符
        if(res.empty()) {
            res.push_back(stoi(expression));
        }
        // 把结果放进备忘录
        memo[expression] = res;
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "2-1-1"\n
// @lcpr case=end

// @lcpr case=start
// "2*3-4*5"\n
// @lcpr case=end

 */

