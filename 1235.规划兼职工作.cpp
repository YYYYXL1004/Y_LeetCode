/*
 * @lc app=leetcode.cn id=1235 lang=cpp
 * @lcpr version=30307
 *
 * [1235] 规划兼职工作
 */

// @lc code=start
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<array <int, 3>> jobs(n);
        // 使用array<int, 3> 保证内存连续性
        for(int i = 0; i < n; i++) {  // 0-based
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        // 按结束时间排序
        sort(jobs.begin(), jobs.end(), [](const auto &a, const auto &b) { return a[1] < b[1]; });
        // 提取结束时间用于二分
        vector<int> ends(n);
        for(int i = 0; i < n; i++) {
            ends[i] = jobs[i][1];  // 提取结束时间
        }

        // dp[i]表示考虑前i个工作时的最大收益
        // dp大小设为n+1， dp[0] = 0处理边界
        vector<int> dp(n+1, 0);

        for(int i = 1; i <= n; i++) { // dp是1-based, jobs是 0-based
            // 当前工作开始时间
            int currStart = jobs[i-1][0];
            int currProfit = jobs[i-1][2];

            // 二分查找
            // 在ends数组的前 i-1个元素，寻找第一个 > currStart的位置
            auto it = upper_bound(ends.begin(), ends.end() + i - 1, currStart);
            // 下标转化：
            // it 指向第一个 > currStart 的位置
            // it - begin 得到该位置的 index
            // 我们需要的是它“前一个”位置（即 <= currStart 的最后一个位置）对应的 DP 值
            // 有趣的是：因为 dp 是 1-based (dp[0]是空)，而 ends 是 0-based
            // distance(begin, it) 算出来的整数值，刚好对应 dp 数组中“上一个合法状态”的下标
            int prevIdx = distance(ends.begin(), it);

            dp[i] = max(dp[i-1], dp[prevIdx] + currProfit);
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,3]\n[3,4,5,6]\n[50,10,40,70]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,6]\n[3,5,10,6,9]\n[20,20,100,70,60]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,1]\n[2,3,4]\n[5,6,4]\n
// @lcpr case=end

 */

