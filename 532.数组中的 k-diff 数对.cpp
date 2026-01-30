/*
 * @lc app=leetcode.cn id=532 lang=cpp
 * @lcpr version=30307
 *
 * [532] 数组中的 k-diff 数对
 */

// @lc code=start
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for(int i : nums) mp[i]++;
        int ans = 0;
        for(int i : nums) {
            if(mp[i] == 0) continue;
            if(k == 0) {
                if(mp[i] > 1) ans++;
            } else {
                int a = i + k;
                int b = i - k;
                if(mp[a] > 0) ans++;
                if(mp[b] > 0) ans++;
            }
            mp[i] = 0; // 避免重复计数
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,1,4,1,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,3,1,5,4]\n0\n
// @lcpr case=end

 */

