/*
 * @lc app=leetcode.cn id=LCR 084 lang=cpp
 * @lcpr version=30402
 *
 * [LCR 084] 全排列 II 
 */

// @lc code=start
class Solution {
public:
    vector<int> track;
    vector<vector<int>> res;
    vector<char> used;

    void backtrace(vector<int>& nums) {
        if(track.size() == nums.size()) {
            res.push_back(track);
            return ;
        }

        for(int i = 0; i < nums.size(); i++) {
            if(used[i]) continue;
            // Pruning (剪枝) 核心逻辑：同一树层不能用相同的元素
            // !used[i - 1] 表示前一个相同的元素刚刚在同一层被回溯撤销了
            if(i != 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            track.push_back(nums[i]);
            used[i] = 1;
            backtrace(nums);
            used[i] = 0; 
            track.pop_back(); 
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        used.resize(nums.size());
        backtrace(nums);
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

