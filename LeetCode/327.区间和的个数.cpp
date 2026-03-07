/*
 * @lc app=leetcode.cn id=327 lang=cpp
 * @lcpr version=30307
 *
 * [327] 区间和的个数
 */

// @lc code=start
class Solution {
public:
    // 子数组[i, j] 的和 = preSum[j+1] - preSum[i]   
    // 题目转化成找到多少对 (i, j) 满足 i < j且 lower <= preSum[j]-preSum[i] <= upper
    // 本质上就是在前缀和数组中找"满足条件的元素对"

    // 暴力找元素对 → O(n²) → 超时
    //   "找满足条件的元素对" ≈ "比较元素之间的大小关系"

    // 这不就是 315 和 493 的套路吗？
    //   315：找 nums[i] > nums[j] 的对数
    //   493：找 nums[i] > 2 * nums[j] 的对数
    //   327：找 lower <= preSum[j] - preSum[i] <= upper 的对数
    // 都是：在排序过程中统计满足某种条件的元素对！

    vector<long> temp;
    int count = 0;

    void mergeSort(vector<long>& nums, int lo, int hi, int lower, int upper) {
        if(lo >= hi) return ;
        int mid = lo + (hi - lo) / 2;
        mergeSort(nums, lo, mid, lower, upper);
        mergeSort(nums, mid + 1, hi, lower, upper);
        merge(nums, lo, mid, hi, lower, upper);
    }

    void merge(vector<long>& nums, int lo, int mid, int hi, int lower, int upper) {
        for(int i = lo; i <= hi; i++) temp[i] = nums[i];
        // 维护一个左闭右开区间[start, end) 中的元素 和nums[i]差值在 [lower, upper]之间
        int start = mid + 1, end = mid + 1;
        for(int i = lo; i <= mid; i++) {
            // 如果 nums[i] 对应区间是 [start, end)]
            // 那么 nums[i+1] 对应区间一定会整体右移，类似与滑动窗口
            while(start <= hi && nums[start] - nums[i] < lower) {
                start++; //  找到第一个 >= lower 的位置
            }
            while(end <= hi && nums[end] - nums[i] <= upper) {
                end++;   // 找到第一个 > upper 的位置
            } 
            count += end - start;  // [start, end) 中的元素都满足条件
        }

        int i = lo, j = mid + 1;
        for(int p = lo; p <= hi; p++) {
            if(i == mid + 1) {
                nums[p] = temp[j++];
            } else if(j == hi + 1) {
                nums[p] = temp[i++];
            } else if(temp[i] <= temp[j]) {
                nums[p] = temp[i++];
            } else {
                nums[p] = temp[j++];
            }
        }
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> preSum(nums.size() + 1);
        for(int i = 0; i < nums.size(); i++) { 
            preSum[i + 1] = (long)(nums[i] + preSum[i]);
        }
        // 对前缀和数组进行归并排序
        temp.resize(preSum.size());
        mergeSort(preSum, 0, preSum.size() - 1, lower, upper);
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-2,5,-1]\n-2\n2\n
// @lcpr case=end

// @lcpr case=start
// [0]\n0\n0\n
// @lcpr case=end

 */

