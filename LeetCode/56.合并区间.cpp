/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * @lcpr version=30403
 *
 * [56] 合并区间
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [](const vector<int>& v1, const vector<int>& v2) {
            return v1[0] < v2[0]; // 按照开始时间，从小到大
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        int st = intervals[0][0];
        int ed = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] <= ed) { // 有重叠
                ed = max(ed, intervals[i][1]);  // 取比较大的右端点
            } else {
                res.push_back({st, ed}); // 没重叠，记录上一个区间
                st = intervals[i][0]; // 更新最新的区间
                ed = intervals[i][1]; 
            }
        }
        res.push_back({st, ed}); // 不要忘记，把循环结束时正在维护的区间也加上
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3],[2,6],[8,10],[15,18]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[4,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,7],[1,4]]\n
// @lcpr case=end

 */

