/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * @lcpr version=30307
 *
 * [39] 组合总和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    int trackSum = 0;

    void backtrack(vector<int>& nums, int start, int target) {
        if(trackSum == target) {
            res.push_back(track);
            return ;
        }
        if(trackSum > target) return ;

        for(int i = start; i < nums.size(); i++) {
            track.push_back(nums[i]);
            trackSum += nums[i];
            // 递归遍历下一层回溯树， 同一元素可以重复选择
            backtrack(nums, i, target);

            track.pop_back();
            trackSum -= nums[i];
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, 0, target);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,6,7]\n7\n
// @lcpr case=end

// @lcpr case=start
// [2,3,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2]\n1\n
// @lcpr case=end

 */

