/*
 * @lc app=leetcode.cn id=90 lang=cpp
 * @lcpr version=30307
 *
 * [90] 子集 II
 */

// @lc code=start
class Solution {
public:
    // 带重复元素的子集问题
    vector<vector<int>> res;
    vector<int> track;

    void backtrack(vector<int>& nums, int start) {
        res.push_back(track);

        for(int i = start; i < nums.size(); i++) {
            // 剪枝：遇到相同的只遍历第一条 
            // start 是当前层的"入口"，i 在当前层内移动：
            // i == start：入口位置，不管是什么值都要尝试（进入新层）
            // i > start：层内移动，遇到和前面相同的值就跳过（同层去重）

            if(i > start && nums[i] == nums[i-1]) continue;

            track.push_back(nums[i]);
            backtrack(nums, i + 1);
            track.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

