/*
 * @lc app=leetcode.cn id=191 lang=cpp
 * @lcpr version=30307
 *
 * [191] 位1的个数
 */

// @lc code=start
class Solution {
public:
    int hammingWeight(int n) {
        // 方法一：Brian Kernighan 算法（优雅）
        // int count = 0;
        // while(n) {
        //     n &= n - 1;
        //     count++;
        // }
        // return count;

        // 方法二：内置函数(简洁+最快)
        // return __builtin_popcount(n);

        // 方法三：逐位检查(基础)
        int count = 0; 
        while(n) {
            count += n & 1; // 检查最低位
            n >>= 1;       // 右移
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 11\n
// @lcpr case=end

// @lcpr case=start
// 128\n
// @lcpr case=end

// @lcpr case=start
// 2147483645\n
// @lcpr case=end

 */

