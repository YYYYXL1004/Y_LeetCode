/*
 * @lc app=leetcode.cn id=72 lang=cpp
 * @lcpr version=30400
 *
 * [72] 编辑距离
 */

// @lc code=start
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // base case
        for(int i = 1; i <= m; i++) dp[i][0] = i; //s2到头，需要把s1剩下字符全部删除
        for(int j = 1; j <= n; j++) dp[0][j] = j; //s1到头了，需要插入s2剩下的字符
        // 自底向上求解
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(word1[i-1] == word2[j-1]) { //索引偏移i,所以都要减一
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({
                        dp[i-1][j-1] + 1,
                        dp[i-1][j] + 1,
                        dp[i][j-1] + 1,
                    });
                }
            }
        }
        return dp[m][n];
    }

    // 方法一：带备忘录的递归
    // vector<vector<int>> memo;
    // int minDistance(string word1, string word2) {
    //     int n = word1.size(), m = word2.size();
    //     // 备忘录初始化为特殊值，代表还未计算
    //     memo = vector<vector<int>>(n, vector<int>(m, -1));
    //     return dp(word1, n - 1, word2, m - 1);
    // }
    // // 定义：返回 s1[0..i] 和 s2[0..j] 的最小编辑距离
    // int dp(string& s1, int i, string& s2, int j) {
    //     if(i == -1) return j + 1; // s1到头了，需要插入s2剩下的字符
    //     if(j == -1) return i + 1; // s2到头，需要把s1剩下字符全部删除
    //     if(memo[i][j] != -1) return memo[i][j];
    //     if(s1[i] == s2[j]) {
    //         memo[i][j] = dp(s1, i - 1, s2, j - 1); // 跳过
    //     } else {
    //         memo[i][j] = min({
    //             dp(s1, i - 1, s2, j - 1) + 1, // 替换 
    //             dp(s1, i - 1, s2, j) + 1, // 删除
    //             dp(s1, i, s2, j - 1) + 1 // 插入
    //         });
    //     }
    //     return memo[i][j];
    // }
};
// @lc code=end



/*
// @lcpr case=start
// "horse"\n"ros"\n
// @lcpr case=end

// @lcpr case=start
// "intention"\n"execution"\n
// @lcpr case=end

 */

