/*
 * @lc app=leetcode.cn id=384 lang=cpp
 * @lcpr version=30307
 *
 * [384] 打乱数组
 */

// @lc code=start
class Solution {
private:
    vector<int> original;  // 保存原始数组
    vector<int> current;   // 当前数组状态
    
public:
    Solution(vector<int>& nums) {
        original = nums;
        current = nums;
    }
    
    vector<int> reset() {
        current = original;
        return current;
    }
    
    vector<int> shuffle() {
        // Fisher-Yates 洗牌算法（从后往前）
        // 每次从 [0, i] 范围随机选一个与位置 i 交换
        for (int i = current.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);  // [0, i] 的随机数
            swap(current[i], current[j]);
        }
        return current;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
// @lc code=end



/*
// @lcpr case=start
// ["Solution","shuffle","reset","shuffle"]\n[[[1,2,3]],[],[],[]]\n
// @lcpr case=end

 */

