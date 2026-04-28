/*
 * @lc app=leetcode.cn id=852 lang=cpp
 * @lcpr version=30403
 *
 * [852] 山脉数组的峰顶索引
 */

// @lc code=start
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int l = 0, r = arr.size()-1;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(arr[mid] < arr[mid+1]) {  // 还在上坡，说明峰值在右边
                l = mid + 1;
            } else { // 下坡了，说明峰值在左边
                r = mid;
            }
        }
        return l;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,0]\n
// @lcpr case=end

// @lcpr case=start
// [0,2,1,0]\n
// @lcpr case=end

// @lcpr case=start
// [0,10,5,2]\n
// @lcpr case=end

 */

