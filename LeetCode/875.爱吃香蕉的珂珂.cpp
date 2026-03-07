/*
 * @lc app=leetcode.cn id=875 lang=cpp
 * @lcpr version=30307
 *
 * [875] 爱吃香蕉的珂珂
 */

// @lc code=start
class Solution {
public:
    // 速度为x时，需要f(x)小时可以吃掉所有香蕉
    // f(x)随着x的增加，非严格单调递减
    long long f(vector<int>& piles, int x) {
        long long h = 0;
        for(int i = 0; i < piles.size(); i++) {
            h += piles[i] / x;
            if(piles[i] % x > 0) h++; // 不整除就+1 
        }
        return h;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1; // 最慢的速度
        int right = 1e9 + 1; // 最快的速度
        while(left <= right) { // 找左边界（画函数图可以帮助理解）
            int mid = left + (right - left) / 2;
            // if(f(piles, mid) == h) {
            //     right = mid - 1;
            // } else if(f(piles, mid) < h) {
            //     // 需要让f(x)的值更大一点，所以x变小，边界向左探索
            //     right = mid - 1;
            if(f(piles, mid) <= h) {
                right = mid - 1; // 可以合并多余分支
            } else if(f(piles, mid) > h) {
                left = mid + 1;
            }
        }
        return left;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,6,7,11]\n8\n
// @lcpr case=end

// @lcpr case=start
// [30,11,23,4,20]\n5\n
// @lcpr case=end

// @lcpr case=start
// [30,11,23,4,20]\n6\n
// @lcpr case=end

 */

