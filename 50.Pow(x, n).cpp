/*
 * @lc app=leetcode.cn id=50 lang=cpp
 * @lcpr version=30400
 *
 * [50] Pow(x, n)
 */

// @lc code=start
class Solution {
public:
    // 快速幂：x^n，递归将 O(n) 降为 O(log n)
    // 核心：x^n = (x^(n/2))^2（偶数），x * x^(n-1)（奇数）
    
    // 快速幂模版
    // 计算 (a ^ b) % k
    // 把 x^b 拆成 x 的若干个 2 的幂次方的乘积，只在对应二进制位为 1 时才乘进结果。
    // long quickPow(long a, long b, long k) {
    //     long res = 1;
    //     a %= k; // 防止 a 大于 k
    //     while(b > 0) {
    //         if((b & 1) == 1) { //当前最低位是 1 吗？是的话把当前的 a 乘进 res
    //             res = (res * a) % k;
    //         } 
    //         a = (a * a) % k; //底数自乘
    //         b >>= 1; // b右移一位，相当于除2
    //     } 
    //     return res;
    // }


    // 方法一：递归版
    // double myPow(double x, int n) {
    //     if(n == 0) return 1;
    //     // n = INT_MIN 时，-n 会整型溢出（INT_MIN 的绝对值比 INT_MAX 大 1）
    //     // 处理方式：先算 x^(-(n+1))，再多除一个 x
    //     if(n == INT_MIN) {
    //         return myPow(1 / x, -(n + 1)) / x;
    //     }
    //     // 负指数：x^(-n) = (1/x)^n
    //     if(n < 0) return myPow(1 / x, -n);

    //     if(n % 2 == 1) { // n 为奇数：x^n = x * x^(n-1)
    //         return x * myPow(x, n - 1);
    //     } else { // n 为偶数：x^n = (x^(n/2))^2
    //         double sub = myPow(x, n / 2);
    //         return sub * sub;
    //     }
    // }

    // 方法二：迭代版（二进制拆分）
    // 把指数 b 看成二进制，从低位到高位逐位检查
    // 例：x^13, 13 = 1101(二进制) = 8+4+1, 所以 x^13 = x^8 * x^4 * x^1
    // 每轮：底数自乘 x → x² → x⁴ → x⁸，刚好对应 2⁰, 2¹, 2², 2³
    // 当前位为 1 时，把对应的底数乘进 res
    double myPow(double x, int n) {
        long b = n; // 用 long 接，避免 n = INT_MIN 时 -n 溢出
        // 负指数：x^(-b) = (1/x)^b
        if(b < 0) {
            x = 1 / x;
            b = -b;
        }
        double res = 1.0;
        while(b > 0) {
            if(b & 1) {     // 当前最低位是 1，把当前底数乘进结果
                res *= x;
            }
            x *= x;         // 底数自乘：x → x² → x⁴ → x⁸ ...
            b >>= 1;        // 右移，检查下一个二进制位
        }
        return res;
    }


};
// @lc code=end



/*
// @lcpr case=start
// 2.00000\n10\n
// @lcpr case=end

// @lcpr case=start
// 2.10000\n3\n
// @lcpr case=end

// @lcpr case=start
// 2.00000\n-2\n
// @lcpr case=end

 */

