/*
 * @lc app=leetcode.cn id=435 lang=cpp
 * @lcpr version=30403
 *
 * [435] 无重叠区间
 */

// @lc code=start
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        auto cmp = [](const vector<int>& v1, const vector<int>& v2) {
            return v1[1] < v2[1]; // 结束时间早的在前面
        };
        sort(intervals.begin(), intervals.end(), cmp);
        int cnt = 1;  // 保留区间个数
        int cur_end = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] >= cur_end) {
                cnt++; // 保留
                cur_end = intervals[i][1];
            }
        }
        return intervals.size() - cnt;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[1,2],[1,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3]]\n
// @lcpr case=end

 */

