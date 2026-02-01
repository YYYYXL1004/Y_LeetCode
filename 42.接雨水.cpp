/*
 * @lc app=leetcode.cn id=42 lang=cpp
 * @lcpr version=30307
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        // 方法一：暴力解法。 O(N^2)时间复杂度，空间复杂度O(1) 322/324
        // int n = height.size();
        // int res = 0;
        // for(int i = 0; i < n; i++) {
        //     int l_max = 0, r_max = 0;
        //     // 找右边最高的柱子
        //     for(int j = i; j < n; j++) {
        //         r_max = max(r_max, height[j]);
        //     }
        //     // 找左边最高的柱子
        //     for(int j = i; j >= 0; j--) {
        //         l_max = max(l_max, height[j]);
        //     }
        //     // 如果自己机会最高的话
        //     // l_max = r_max = height[i]
        //     // res += 0
        //     res += min(l_max, r_max) - height[i]; // 位置i能装的水
        // }
        // return res;

        // 方法二：用备忘录优化。 O(N^2)时间复杂度。空间复杂度O(N) 可以通过本题
        // 推荐使用，不用非要追求方法三
        // int n = height.size();
        // int res = 0;
        // // 开两个备忘录，降低时间复杂度
        // vector<int> l_max(n);
        // vector<int> r_max(n);
        // l_max[0] = height[0];
        // r_max[n-1] = height[n-1];

        // for(int i = 1; i < n; i++) {
        //     l_max[i] = max(height[i], l_max[i-1]);
        // }
        // for(int i = n-2; i >= 0; i--) {
        //     r_max[i] = max(height[i], r_max[i+1]);
        // }

        // for(int i = 0; i < n; i++) {
        //     res += min(l_max[i], r_max[i]) - height[i];
        // }
        // return res;

        // 方法三：双指针优化，空间复杂度降到O(1)
        int left = 0, right = height.size() - 1;
        int l_max = 0, r_max = 0;
        int res = 0;

        while(left < right) {
            l_max = max(l_max, height[left]);
            r_max = max(r_max, height[right]);

            if(l_max < r_max) {
                // 这时候l_max比r_max小
                // left左侧最大的是l_max，不用关心r_max是不是left右侧最大的
                // 因为最终只需要min(l_max, r_max)
                res += l_max - height[left];
                left++;
            } else {
                res += r_max - height[right];
                right--;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,0,2,1,0,1,3,2,1,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [4,2,0,3,2,5]\n
// @lcpr case=end

 */

