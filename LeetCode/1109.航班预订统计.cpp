/*
 * @lc app=leetcode.cn id=1109 lang=cpp
 * @lcpr version=30307
 *
 * [1109] 航班预订统计
 */

// @lc code=start
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n);
        vector<int> diff(n);
        int t = bookings.size();  // 有几条booking
        for(int i = 0; i < t; i++) {
            int first = bookings[i][0], last = bookings[i][1], seats = bookings[i][2];
            diff[first-1] += seats;  // 因为first,last索引是从1开始的，所以都要-1
            if(last < n) { // 如果last索引为n
                diff[last] -= seats;
            }
        }
        ans[0] = diff[0];
        for(int i = 1; i < n; i++) { 
            ans[i] = ans[i-1] + diff[i]; // 两个都是0-based的，所以ans[i]是diff[0..i]的和
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,10],[2,3,20],[2,5,25]]\n5\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,10],[2,2,15]]\n2\n
// @lcpr case=end

 */

