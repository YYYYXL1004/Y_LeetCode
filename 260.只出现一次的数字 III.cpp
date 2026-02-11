/*
 * @lc app=leetcode.cn id=260 lang=cpp
 * @lcpr version=30307
 *
 * [260] 只出现一次的数字 III
 */

// @lc code=start
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unsigned int xorall = 0;
        // 1：全部异或，得到两个目标数的异或结果
        for(int num : nums) xorall ^= num;

        // 2：找到xorall最低位的 1
        // 说明两个目标数在该位不同 
        // 当 xorAll = -2147483648（即 INT_MIN）时：
        // 它的二进制是 1000...000（最高位是1，其余是0）
        // -xorAll 应该是 2147483648，但 int 最大只能表示 2147483647
        unsigned int diffBit = xorall & (-xorall);

        // 3：根据这一组分组异或
        int a = 0, b = 0;
        for(int num : nums) {
            if((num & diffBit) == 0) {
                a ^= num; // 该位为0的组
            } else {
                b ^= num; // 该组为1的组
            }
        }
        return {a, b};
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,1,3,2,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,0,-2147483648]\n
// @lcpr case=end

// @lcpr case=start
// [0,1]\n
// @lcpr case=end

 */

