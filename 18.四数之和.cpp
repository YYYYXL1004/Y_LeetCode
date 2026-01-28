/*
 * @lc app=leetcode.cn id=18 lang=cpp
 * @lcpr version=30307
 *
 * [18] 四数之和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return nSumTarget(nums, 4, 0, target);
    }
private:
    vector<vector<int> >nSumTarget(vector<int>& nums, int n, int start, long target) {
        int sz = nums.size();
        vector<vector<int> > res;
        if(n < 2 || sz < n) return {};
        if(n == 2) {
            int l = start, r = sz - 1;
            while(l < r) {
                int left = nums[l], right = nums[r];
                int sum = left + right;
                if(sum == target) {
                    res.push_back({left, right});
                    while(l < r && nums[l] == left) l++;
                    while(l < r && nums[r] == right) r--;
                } else if(sum < target) {
                    while(l < r && nums[l] == left) l++;
                } else {
                    while(l < r && nums[r] == right) r--;
                }
            }
        } else {
            for(int i = start; i < sz; i++) {
                // 固定一个i, 在剩下的数中找 n-1 Sum = target-nums[i]
                vector<vector<int>> sub = nSumTarget(nums, n - 1, i + 1, target - nums[i]);
                for(auto& arr : sub) {
                    arr.push_back(nums[i]);
                    res.push_back(arr);
                }
                while(i <sz - 1 && nums[i] == nums[i+1]) i++;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,0,-1,0,-2,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [2,2,2,2,2]\n8\n
// @lcpr case=end

 */

