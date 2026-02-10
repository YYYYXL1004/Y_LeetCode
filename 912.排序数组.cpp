/*
 * @lc app=leetcode.cn id=912 lang=cpp
 * @lcpr version=30307
 *
 * [912] 排序数组
 */

// @lc code=start
class Solution {
public:
    // 手撕归并排序
    vector<int> temp; // 辅助数组

    // 对 nums[lo, hi]排序
    void mergeSort(vector<int>& nums, int lo, int hi) {
        if(lo >= hi) return ; // base case;
        // 分：取中点，递归排序左右
        int mid = lo + (hi - lo) / 2;
        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);
        // 合并两个有序数组
        merge(nums, lo, mid, hi);
    }

    void merge(vector<int>& nums, int lo, int mid, int hi) {
        // 先把nums[lo, ,hi]复制到辅助数组中，以便合并后的结果可以直接存入nums
        for(int i = lo; i <= hi; i++) {
            temp[i] = nums[i];
        }
        // 双指针合并
        int i = lo, j = mid + 1;
        for(int p = lo; p <= hi; p++) {
            if(i == mid + 1) {
                // 左半边用完，取右半边
                nums[p] = temp[j++];
            } else if(j == hi + 1) {
                // 右半边用完，去左半边
                nums[p] = temp[i++];
            } else if(temp[i] <= temp[j]) {
                // 左边较小
                nums[p] = temp[i++];
            } else {
                // 右边较小
                nums[p] = temp[j++];
            }
        }
    }

    vector<int> sortArray(vector<int>& nums) {
        temp.resize(nums.size());
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [5,1,1,2,0,0]\n
// @lcpr case=end

 */

