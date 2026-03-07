/*
 * @lc app=leetcode.cn id=172 lang=cpp
 * @lcpr version=30400
 *
 * [172] 阶乘后的零
 */

// @lc code=start
class Solution {
public:
    // 阶乘末尾零的个数 = 阶乘中因子 10 的个数 = min(因子2的个数, 因子5的个数)
    // 因为因子 2 远多于因子 5，所以只需要数因子 5 的个数
    //
    // n! 中因子 5 的个数 = n/5 + n/25 + n/125 + ...
    //   n/5:   能被 5 整除的数，每个贡献 1 个 5
    //   n/25:  能被 25 整除的数，额外再贡献 1 个 5（25 = 5×5）
    //   n/125: 能被 125 整除的数，再额外贡献 1 个 5
    //   ...依此类推，直到 5^k > n
    //

    // 朴素解法：
    // int trailingZeroes(int n) {
    //     int res = 0;
    //     long divisor = 5;
    //     while (divisor <= n) {
    //         res += n / divisor;
    //         divisor *= 5;
    //     }
    //     return res;
    // }

    // 优化版
    // 巧妙之处：不需要维护 divisor 变量，每轮让 d 自己除以 5 即可
    // d = n → d/5 就是 n/5
    // d = n/5 → d/5 就是 n/25
    // d = n/25 → d/5 就是 n/125 ...
    int trailingZeroes(int n) {
        int res = 0;
        for(int d = n; d / 5 > 0; d = d / 5) {
            res += d / 5;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 5\n
// @lcpr case=end

// @lcpr case=start
// 0\n
// @lcpr case=end

 */

