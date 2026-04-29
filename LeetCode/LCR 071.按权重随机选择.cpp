/*
 * @lc app=leetcode.cn id=LCR 071 lang=cpp
 * @lcpr version=30403
 *
 * [LCR 071] 按权重随机选择
 */

// @lc code=start
class Solution {
public:
    vector<int> preSum;
    Solution(vector<int>& w) {
        preSum.push_back(w[0]);
        for(int i = 1; i < w.size(); i++) {
            preSum.push_back(preSum.back() + w[i]);
        }
    }
    
    int pickIndex() {
        // 生成 1 到 总权重 之间的随机数 target
        int target = rand() % preSum.back() + 1;
        auto it = lower_bound(preSum.begin(), preSum.end(), target);
        return distance(preSum.begin(), it);
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
// @lc code=end



/*
// @lcpr case=start
// ["Solution","pickIndex"]\n[[[1]],[]]\n["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]\n[[[1,3]],[],[],[],[],[]]\n
// @lcpr case=end

 */

