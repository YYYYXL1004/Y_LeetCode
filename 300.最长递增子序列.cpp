/*
 * @lc app=leetcode.cn id=300 lang=cpp
 * @lcpr version=30400
 *
 * [300] 最长递增子序列
 */

// @lc code=start
class Solution {
public:
    // 1、明确 dp 数组的定义。这一步对于任何动态规划问题都很重要，如果不得当或者不够清晰，会阻碍之后的步骤。
    // 2、根据 dp 数组的定义，运用数学归纳法的思想，假设 dp[0...i-1] 都已知，想办法求出 dp[i]，一旦这一步完成，整个题目基本就解决了。
    // 但如果无法完成这一步，很可能就是 dp 数组的定义不够恰当，需要重新定义 dp 数组的含义；
    // 或者可能是 dp 数组存储的信息还不够，不足以推出下一步的答案，需要把 dp 数组扩大成二维数组甚至三维数组。

    int lengthOfLIS(vector<int>& nums) {
        // 方法一：O（N^2)
        // 定义：dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度,初始化为1
        // vector<int> dp(nums.size(), 1);
        // for(int i = 0; i < dp.size(); i++) {
        //     for(int j = 0; j < i; j++) {
        //         // 寻找 nums[0..i-1] 中比 nums[i] 小的元素
        //         if(nums[i] > nums[j]) {
        //             // 把 nums[i] 接在后面，即可形成长度为 dp[j] + 1，
        //             // 且以 nums[i] 为结尾的递增子序列
        //             dp[i] = max(dp[i], dp[j] + 1);
        //         }
        //     }
        // }

        // int res = 0;
        // for(int i = 0; i < dp.size(); i++) {
        //     res = max(res, dp[i]);
        // }
        // return res;
        
        // 方法2: O(n log n) 优化解法
        // 贪心思想：对于相同长度的递增子序列，我们总是希望结尾元素越小越好
        vector<int> tail;
        // 维护一个 tail 数组，其中 tail[i] 表示长度为 i+1 的递增子序列的最小结尾元素。
        tail.push_back(nums[0]);

        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] > tail.back()) {
                // 如果当前元素大于tail数组的最后一个元素
                // 直接将其加到tail末尾
                tail.push_back(nums[i]);
            } else {
                // 否则，在tail数组中找到第一个大于等于nums[i]的元素
                // 并用nums[i]代替它
                int pos = lower_bound(tail.begin(), tail.end(), nums[i]) - tail.begin();
                tail[pos] = nums[i];
            }
        }
        return tail.size();  // 这里面保存的就是最大递增子序列
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,9,2,5,3,7,101,18]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,0,3,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [7,7,7,7,7,7,7]\n
// @lcpr case=end

 */

