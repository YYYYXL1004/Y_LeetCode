/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * @lcpr version=30307
 *
 * [47] 全排列 II
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<char> used;

    // 相比较与普通全排列，对nums进行排序，然后加了一句剪枝
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) {
            res.push_back(track);
            return ;
        }

        for(int i = 0; i < nums.size(); i++) {
            if(used[i]) continue;
            // 新添加的剪枝逻辑，固定相同的元素在排列中的相对位置
            // 如果前面的相邻相等元素没有用过，则跳过当前元素
            if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            track.push_back(nums[i]);
            used[i] = 1;
            backtrack(nums);
            track.pop_back();
            used[i] = 0;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        used.resize(nums.size(), 0);
        sort(nums.begin(), nums.end());
        backtrack(nums);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

 */

