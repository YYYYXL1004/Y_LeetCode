/*
 * @lc app=leetcode.cn id=322 lang=cpp
 * @lcpr version=30400
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    // 方法一：暴力递归（15/189)
    // int coinChange(vector<int>& coins, int amount) {
    //     return dp(coins, amount);
    // }

    // // 定义：要凑出目标金额 amount，至少要 dp(coins, amount) 个硬币
    // int dp(vector<int>& coins, int amount) {
    //     if(amount < 0) return -1;
    //     if(amount == 0) return 0;

    //     int res = INT_MAX;
    //     for(int coin : coins) {
    //         // 计算子问题结果
    //         int subProblem = dp(coins, amount - coin);
    //         if(subProblem == -1) continue;
    //         // 在子问题中选最优解
    //         res = min(res, subProblem + 1);
    //     }

    //     return res == INT_MAX ? -1 : res;
    // }

    // 方法二：带备忘录的递归优化,自顶向下
    // 子问题总数不会超过amount,即O(n),处理一个子问题的时间不变，所以总的时间复杂度为O(kn)
    
    // 1、确定「状态」，也就是原问题和子问题中会变化的变量。由于硬币数量无限，硬币的面额也是题目给定的，
    // 只有目标金额会不断地向 base case 靠近，所以唯一的「状态」就是目标金额 amount。
    // 2、确定「选择」，也就是导致「状态」产生变化的行为。目标金额为什么变化呢，因为你在选择硬币，你每选择一枚硬币，就相当于减少了目标金额。
    // 所以说所有硬币的面值，就是你的「选择」。
    // 3、明确 dp 函数/数组的定义。我们这里讲的是自顶向下的解法，所以会有一个递归的 dp 函数，一般来说函数的参数就是状态转移中会变化的量，
    // 也就是上面说到的「状态」；函数的返回值就是题目要求我们计算的量。就本题来说，状态只有一个，即「目标金额」，题目要求我们计算凑出目标金额所需的最少硬币数量。
    // 所以我们可以这样定义 dp 函数：dp(n) 表示，输入一个目标金额 n，返回凑出目标金额 n 所需的最少硬币数量。

    // vector<int> memo;
    // int coinChange(vector<int>& coins, int amount) {
    //     memo = vector<int>(amount + 1, -666);
    //     // 备忘录初始化为一个不会被取到的特殊值，代表还未被计算
    //     return dp(coins, amount);
    // }

    // int dp(vector<int>& coins, int amount) {
    //     if(amount == 0) return 0;
    //     if(amount < 0) return -1;
    //     // 查备忘录，防止重复计算
    //     if(memo[amount] != -666) return memo[amount];

    //     int res = INT_MAX;
    //     for(int coin : coins) {
    //         int sub = dp(coins, amount - coin);
    //         if(sub == -1) continue;
    //         res = min(res, sub + 1);
    //     }
    //     // 把计算结果放到备忘录
    //     memo[amount] = (res == INT_MAX) ? -1 : res;
    //     return memo[amount];
    // }

    // 方法三：dp table的迭代解法， 自底向上
    // dp 数组的定义：当目标金额为 i 时，至少需要 dp[i] 枚硬币凑出。
    
    
    int coinChange(vector<int>& coins, int amount) {
        // 数组大小为 amount + 1，初始值也为 amount + 1
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        
        for(int i = 0; i < dp.size(); i++) {
            for(int coin : coins) {
                // 子问题无解，跳过
                if(i - coin < 0) continue;
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,5]\n11\n
// @lcpr case=end

// @lcpr case=start
// [2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n0\n
// @lcpr case=end

 */

