/*
 * @lc app=leetcode.cn id=45 lang=cpp
 * @lcpr version=30400
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start
class Solution {
public:
    // 方法二：贪心
    int jump(vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }
        int n = nums.size();
        // jumps 步可以跳到索引区间 [i, end]
        // 在 [i, end] 区间内，最远可以跳到的索引是 farthest
        int end = 0, farthest = 0, jumps = 0;
        for(int i = 0; i < n - 1; i++) {
            // 计算从索引 i 可以跳到的最远索引
            farthest = max(farthest, i + nums[i]);
            if(i == end) {
                // [i, end] 区间是 jumps 步可达的索引范围
                // 现在已经遍历完 [i, end]，所以需要再跳一步
                jumps++;
                end = farthest;
                // 如果已经可以到达终点，则可以直接返回
                if(farthest >= n - 1) return jumps;
            }
        }
        return -1;
    }

    // 方法一：备忘录优化DP O(n^2)
    // vector<int> memo;
    // int jump(vector<int>& nums) {
    //     int n = nums.size();
    //     // 备忘录初始化为n,相当于INT_MAX,因为从0走到n-1最多只需要n-1步
    //     memo = vector<int>(n, n);
    //     return dp(nums, 0);
    // }

    // // 定义：从索引 p 跳到最后一格，至少需要 dp(nums, p) 步
    // int dp(vector<int>& nums, int p) {
    //     int n = nums.size();
    //     if(p >= n - 1) return 0; // base case
    //     if(memo[p] != n) return memo[p];  // 减少重复计算
    //     int steps = nums[p];
    //     // 可以走1到 nums[p]步
    //     for(int i = 1; i <= steps; i++) {
    //         // 穷举每一个选择
    //         // 计算每一个子问题的结果
    //         int subproblem = dp(nums, p + i);
    //         // 取其中最小的作为最终结果
    //         memo[p] = min(memo[p], subproblem + 1);
    //     } 
    //     return memo[p];
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,1,1,4]\n
// @lcpr case=end

// @lcpr case=start
// [2,3,0,1,4]\n
// @lcpr case=end

 */

