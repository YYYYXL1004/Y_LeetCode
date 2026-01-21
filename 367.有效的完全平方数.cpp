/*
 * @lc app=leetcode.cn id=367 lang=cpp
 *
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution {
public:
    bool isPerfectSquare(int num) {
        int l = 1, r = num;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(num / mid > mid) {
                l = mid + 1;
            } else if(num / mid < mid) {
                r = mid - 1;
            } else {
                if(num == mid * mid) return true;
                else return false;
            }
        }
        return false;
    }
};
// @lc code=end

