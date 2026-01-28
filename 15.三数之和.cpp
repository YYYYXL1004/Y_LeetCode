/*
 * @lc app=leetcode.cn id=15 lang=cpp
 * @lcpr version=30307
 *
 * [15] 三数之和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        // n为3， 从nums[0]开始计算和为0的三元组
        return nSumTarget(nums, 3, 0, 0);
    }
private:
    //  调用此函数前一定要先排序
    //  n 填写想求的是几数之和，start 从哪个索引开始计算（一般填 0），target 填想凑出的目标和
    vector< vector<int> >nSumTarget(vector<int>& nums, int n, int start, long long target) {
        int sz = nums.size();
        vector<vector<int>> res;
        // 至少是2Sum,且数组大小不应该小于n
        if(n < 2 || sz < n) return res;
        if(n == 2) {
            int l = start, r = sz - 1;
            while(l < r) {
                int sum = nums[l] + nums[r];
                int left = nums[l], right = nums[r];
                if(sum == target) {
                    res.push_back({left, right});
                    while(l < r && nums[l] == left) l++; // 去重
                    while(l < r && nums[r] == right) r--;
                } else if(sum < target) {
                    while(l < r && nums[l] == left) l++;
                } else {
                    while(l < r && nums[r] == right) r--;
                }
            }
        } else { // n大于2时，递归运算(n-1)Sum的结果
            for(int i = start; i < sz; i++) {
                // 固定一个数，求剩下数和为target-nums[i]的结果
                vector<vector<int> > sub = nSumTarget(nums, n-1, i+1, target-nums[i]);
                for(vector<int> &arr : sub) {
                    // (n-1)Sum 加上 nums[i] 就是 nSum
                    arr.push_back(nums[i]);
                    res.push_back(arr);
                }
                while(i <sz - 1 && nums[i] == nums[i + 1]) i++; // 去重
            }
        }
        return res;
    } 
};
// @lc code=end



/*
// @lcpr case=start
// [-1,0,1,2,-1,-4]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,0]\n
// @lcpr case=end

 */

