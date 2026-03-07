/*
 * @lc app=leetcode.cn id=46 lang=cpp
 * @lcpr version=30307
 *
 * [46] 全排列
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;  \
    // 主函数，输入一组不重复的数字，返回它们的全排列
    vector<vector<int>> permute(vector<int>& nums) {
        list<int> track;                        // 记录「路径]
        vector<char> used(nums.size(), 0);      // 记录访问情况
        // 使用vector<bool> 因为位压缩，访问速度较慢，推荐使用vector<char>
        backtrack(nums, track, used);
        return res;
    }

    // 路径：记录在 track 中
    // 选择列表：nums 中不存在于 track 的那些元素（used[i] 为 false）
    // 结束条件：nums 中的元素全都在 track 中出现
    void backtrack(vector<int>& nums, list<int>& track, vector<char>& used) {
        if(track.size() == nums.size()) { // 结束条件
            res.push_back(vector<int>(track.begin(), track.end()));
            return ;
        }

        for(int i = 0; i < nums.size(); i++) {
            if(used[i]) continue;  // 排除不合法的选择
            // 做选择
            track.push_back(nums[i]);
            used[i] = 1; // 标记被选过
            // 进入下一层决策树
            backtrack(nums, track, used);
            // 复原
            used[i] = 0;
            track.pop_back();
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,1]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

