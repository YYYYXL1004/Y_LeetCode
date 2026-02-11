/*
 * @lc app=leetcode.cn id=762 lang=cpp
 * @lcpr version=30307
 *
 * [762] 二进制表示中质数个计算置位
 */

// @lc code=start
class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        // 方法一：直接法（最简单）
        // 因为 right <= 10^6 < 2^20，所以二进制位数最多 20 位
        // 0-20 中的质数只有：2, 3, 5, 7, 11, 13, 17, 19
        // 可以用集合或位掩码表示

        // unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
        // int count = 0;
        // for(int i = left; i <= right; i++) {
        //     int bits = __builtin_popcount(i); // 统计 i 二进制中 1 的个数
        //     if(primes.count(bits)) count++;
        // }        
        // return count;

        // // 方法二：位掩码优化（更快）
        // 把质数集合编码成一个整数：2^2 + 2^3 + 2^5 + 2^7 + 2^11 + 2^13 + 2^17 + 2^19
        // = 0b10100010100010101100 = 665772
        int PrimeMask = 0b10100010100010101100;
        int count = 0;
        for(int i = left; i <= right; i++) {
            // int bits = __builtin_popcount(i);
            int bits = countBits(i);
            // 检查 bits 是否在质数集合中：检查第 bits 位是否为 1
            if((PrimeMask >> bits) & 1) count++;
        }
        return count;
    }

    int countBits(int n) {
        int count = 0;
        // while(n) {
        //     count += n & 1; // 检查最低位是不是1
        //     n >>= 1;        // 右移一位
        // }
        while(n) {  // 更快的：Brian Kernighan 算法
            n &= n - 1; // 每次消除最右边的1
            count++; 
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 6\n10\n
// @lcpr case=end

// @lcpr case=start
// 10\n15\n
// @lcpr case=end

 */

