/*
 * @lc app=leetcode.cn id=220 lang=cpp
 * @lcpr version=30400
 *
 * [220] 存在重复元素 III
 */

// @lc code=start
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        int left = 0, right = 0;
        set<long> window; // 利用有序性可以快速查找某个元素的"地板"（小于它的最大元素）和"天花板"（大于它的最小元素）。
        while(right < nums.size()) {
            // 为了防止 i == j，所以在扩大窗口之前先判断是否有符合题意的索引对 (i, j)
            // 此时窗口里只有 [left, right) 区间的元素，索引都小于 right
            // 所以找到的任何元素都满足 i != j  
            // 在window中查找略大于 nums[right] 的那个元素
            auto ceiling = window.lower_bound((long)nums[right]);
            if(ceiling != window.end() && *ceiling - nums[right] <= valueDiff) {
                return true;
            }
            // 查找略小于 nums[right] 的那个元素
            auto floor = ceiling;
            if(floor != window.begin()) {
                --floor;
                if(nums[right] - *floor <= valueDiff) return true;
            } // 只需要比较最接近的较大值和最接近的较小值，不需要遍历
            // while(floor != window.begin()) {
            //     --floor;
            //     if(nums[right] - *floor <= valueDiff) return true;
            // }
            window.insert(nums[right]);
            right++;  // 扩大窗口

            while(right - left > indexDiff) {
                window.erase(nums[left]);
                left++;
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n3\n0\n
// @lcpr case=end

// @lcpr case=start
// [1,5,9,1,5,9]\n2\n3\n
// @lcpr case=end

 */

