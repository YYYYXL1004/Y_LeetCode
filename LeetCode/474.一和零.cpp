/*
 * @lc app=leetcode.cn id=474 lang=cpp
 * @lcpr version=30403
 *
 * [474] 一和零
 */

// @lc code=start
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // dp[j][k] 最多有 j个0 和 k个1的最大子集长度
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(const string& str : strs) {
            int cnt0 = 0, cnt1 = 0; // 该字符串0 1的个数
            for(char s :str) {
                if(s == '0') cnt0++;
                else cnt1++;
            }
            // 二维费用的 0/1背包，两个容量维度全部逆向遍历
            for(int j = m; j >= cnt0; j--) {
                for(int k = n; k >= cnt1; k--) {
                    // 装 or 不装
                    dp[j][k] = max(dp[j][k], dp[j-cnt0][k-cnt1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["10","0001","111001","1","0"]\n5\n3\n
// @lcpr case=end

// @lcpr case=start
// ["10","0","1"]\n1\n1\n
// @lcpr case=end

 */

