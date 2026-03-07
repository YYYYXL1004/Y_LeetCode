/*
 * @lc app=leetcode.cn id=78 lang=cpp
 * @lcpr version=30307
 *
 * [78] 子集
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    // 记录回溯算法的递归路径
    vector<int> track;

    // 回溯算法核心函数，遍历子集问题的回溯树
    void backtrack(vector<int>& nums, int start) {
        // 前序位置：每个节点的值都是一个子集
        // 不像全排列要等到叶子节点，子集问题每个节点都是答案
        res.push_back(track);

        // 注意这里是从start开始,不回头
        // start 表示从哪个下标开始选，避免选到前面的元素
        for(int i = start; i < nums.size(); i++) {
            // 做选择
            track.push_back(nums[i]);
            // 通过 start 参数控制树枝的遍历，避免产生重复的子集
            backtrack(nums, i + 1); 
            // 撤销选择
            track.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

