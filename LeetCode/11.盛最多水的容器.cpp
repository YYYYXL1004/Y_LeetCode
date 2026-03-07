/*
 * @lc app=leetcode.cn id=11 lang=cpp
 * @lcpr version=30307
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int res = 0;
        int left = 0, right = n - 1;
        
        while(left < right) {
            int cur_area = min(height[left], height[right]) * (right-left);
            res = max(res, cur_area);

            // 移动高度较小的指针,因为移动较高的指针不可能得到更大的面积
            if(height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,8,6,2,5,4,8,3,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end

 */

