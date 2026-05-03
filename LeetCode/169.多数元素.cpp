/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * @lcpr version=30403
 *
 * [169] 多数元素
 */

// @lc code=start
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // 方法一：同归于尽法（摩尔投票法） O(1)空间
        // int cnt = 1;
        // int ans = nums[0];
        // for(int i = 1; i < nums.size(); i++) {
        //     if(cnt == 0) {
        //         ans = nums[i];
        //         cnt++;
        //         continue;
        //     }
        //     if(nums[i] != ans) {
        //         cnt--;
        //     } else {
        //         cnt++;
        //     }
        // }
        // return ans;
        
        // 方法二：哈希表
        // unordered_map<int, int> mp;
        // int n = nums.size();
        // for(int num : nums) {
        //     mp[num]++;
        //     if(mp[num] > n / 2) {
        //         return num;
        //     }
        // }
        // return -1;

        // 方法三：map+vector自定义排序
        map<int, int> mp;
        for(int num : nums) {
            mp[num]++;
        }
        vector<pair<int, int>> v(mp.begin(), mp.end());
        auto cmp = [](const auto& a, const auto& b) {
            return a.second > b.second;
        }; // 自定义按照second排序
        sort(v.begin(), v.end(), cmp);
        return v[0].first;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,1,1,1,2,2]\n
// @lcpr case=end

 */

