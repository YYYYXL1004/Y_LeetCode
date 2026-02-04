/*
 * @lc app=leetcode.cn id=528 lang=cpp
 * @lcpr version=30307
 *
 * [528] 按权重随机选择
 */

// @lc code=start
class Solution {
private:
    vector<int> preSum;
    int total;
    
public:
    Solution(vector<int>& w) {
        preSum.resize(w.size());
        preSum[0] = w[0]; // preSum[i]是w[0,1..i]的前缀和
        for(int i = 1; i < w.size(); i++) {
            preSum[i] = w[i] + preSum[i-1];
        }
        total = preSum[w.size() - 1];
    }
    
    int pickIndex() {
        int target = rand() % total + 1; // 生成[1, total]范围内的随机数
        
        // 二分查找：找第一个 >= target 的位置
        int left = 0, right = preSum.size() - 1;
        
        while(left <= right) {  
            int mid = left + (right - left) / 2;
            
            if(preSum[mid] >= target) {  // 比较 preSum[mid] 和 target（数值）
                right = mid - 1;
            } else {
                left = mid + 1;  
            }
        }
        
        return left;
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

