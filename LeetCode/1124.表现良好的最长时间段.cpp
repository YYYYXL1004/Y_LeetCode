/*
 * @lc app=leetcode.cn id=1124 lang=cpp
 * @lcpr version=30403
 *
 * [1124] 表现良好的最长时间段
 */

// @lc code=start
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        unordered_map<int, int> preMap; // 记录前缀和第一次出现的索引

        int preSum = 0;
        int maxlen = 0;

        for(int i = 0; i < n; i++) {
            // 大于8h 就加一， 算子数组和大于0的长度
            preSum += (hours[i] > 8 ? 1 : -1);
            if(preSum > 0) {
                // 如果当前前缀和大于0，说明从开头到现在位置一定满足条件，且是最长的
                maxlen = i + 1;
            } else {
                // 如果 <= 0，就要找之前的preSum-1了
                if(preMap.count(preSum-1)) {
                    // 每次最次加1，所以就找preSum-1,最容易满足
                    maxlen = max(maxlen, i - preMap[preSum-1]);
                }
            }
            if(!preMap.count(preSum)) {
                preMap[preSum] = i; // 第一次出现记录
            }
        }
        return maxlen;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [9,9,6,0,6,6,9]\n
// @lcpr case=end

// @lcpr case=start
// [6,6,6]\n
// @lcpr case=end

 */

