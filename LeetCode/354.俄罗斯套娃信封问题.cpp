/*
 * @lc app=leetcode.cn id=354 lang=cpp
 * @lcpr version=30400
 *
 * [354] 俄罗斯套娃信封问题
 */

// @lc code=start
class Solution {
public:
    // 先按宽度升序、宽度相同时高度降序排序，然后对高度求最长递增子序列（LIS）。
    // 宽度相同时高度降序是为了避免同一宽度的信封被选中。
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        // 按宽度升序排列，如果宽度一样，则按高度降序排列
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] == b[0] ? b[1] < a[1] : a[0] < b[0];
        };
        sort(envelopes.begin(), envelopes.end(), cmp);
        vector<int> height(n);
        for(int i = 0; i < n; i++) {
            height[i] = envelopes[i][1];
        }
        return LIS(height);
    }

    int LIS(vector<int>& nums) {
        vector<int> tail;
        tail.push_back(nums[0]);
        // 维护tail数组， tail[i]为长度 i + 1的最长递增子序列的最后一个元素
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] > tail.back()) { // 如果目前元素大于tail最后一个元素，更新LIS
                tail.push_back(nums[i]);
            } else { // 如果目前元素小于tail最后一个元素，则替代tail数组中第一个大于等于nums[i]的位置
                // 保障tail的最后元素保证尽量小（贪心
                int pos = lower_bound(tail.begin(), tail.end(), nums[i]) - tail.begin();
                tail[pos] = nums[i];
            }
        }
        return tail.size();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[5,4],[6,4],[6,7],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1],[1,1],[1,1]]\n
// @lcpr case=end

 */

