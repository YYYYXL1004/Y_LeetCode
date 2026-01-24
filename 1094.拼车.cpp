/*
 * @lc app=leetcode.cn id=1094 lang=cpp
 * @lcpr version=30307
 *
 * [1094] 拼车
 */

// @lc code=start
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 题目说 to 最大为1000
        vector<int> diff(1001, 0);
        
        for(auto& trip : trips) {
            int numPassengers = trip[0], from = trip[1], to = trip[2];
            diff[from] += numPassengers;  // from站上车
            diff[to] -= numPassengers;    // to站下车（乘客在to站已经下车了）
            // 如果to站不下就是diff[to+1] -=了
        }
        
        int current = 0;
        for(int i = 0; i < 1001; i++) {
            current += diff[i];  
            if(current > capacity) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,1,5],[3,3,7]]\n4\n
// @lcpr case=end

// @lcpr case=start
// [[2,1,5],[3,3,7]]\n5\n
// @lcpr case=end

 */

