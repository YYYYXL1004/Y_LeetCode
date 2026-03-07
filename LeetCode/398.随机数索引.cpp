/*
 * @lc app=leetcode.cn id=398 lang=cpp
 * @lcpr version=30307
 *
 * [398] 随机数索引
 */

// @lc code=start
class Solution {
private:
    vector<int> nums;
    mt19937 gen;
    
public:
    Solution(vector<int>& nums) : nums(nums), gen(random_device{}()) {}
    
    // 蓄水池抽样：等概率返回值为 target 的索引
    int pick(int target) {
        int count = 0;
        int res = -1;
        // 遍历数组，对所有等于target的索引进行抽样
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != target) continue;
            count++;
            // 以1/count 的概率选择当前索引
            uniform_int_distribution<int> dis(0, count - 1);
            if(dis(gen) == 0) {
                res = i;
            }
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
// @lc code=end



/*
// @lcpr case=start
// ["Solution","pick","pick","pick"]\n[[[1,2,3,3,3]],[3],[1],[3]]\n
// @lcpr case=end

 */

