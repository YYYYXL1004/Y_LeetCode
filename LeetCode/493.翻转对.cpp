/*
 * @lc app=leetcode.cn id=493 lang=cpp
 * @lcpr version=30307
 *
 * [493] 翻转对
 */

// @lc code=start
class Solution {
public:
    // 因为本题要求nums[i] > 2 * nums[j]与merge的比较操作不同，没办法在meige中顺便比较
    // 所以必须单独写一个循环来统计
    int count = 0;
    vector<int> temp;

    void mergeSort(vector<int>& nums, int lo, int hi) {
        if(lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);
        // ★ 和315唯一的区别：merge之前先统计翻转对
        // ★ 此时左右两半都已经排好序了！
        // 可以利用有序性用双指针 O(n) 扫描
        // 而不是暴力 O(n²) 比较
        // 右半部分索引原本就满足 i < j，只需要找nums[i] > 2 * nums[j]就行
        int j = mid + 1;
        for(int i = lo; i <= mid; i++) {
            while(j <= hi && (long long)nums[i] > (long long)2 * nums[j]) {
                j++;
            }
            count += j - (mid + 1);
        }

        merge(nums, lo, mid, hi);
    }

    void merge(vector<int>& nums, int lo, int mid, int hi) {
        for(int i = lo; i <= hi; i++) {
            temp[i] = nums[i];
        }
        
        int i = lo, j = mid + 1;
        for(int p = lo; p <= hi; p++) {
            if(i == mid + 1) { // 左边用完，取右边
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
    int reversePairs(vector<int>& nums) {
        temp.resize(nums.size());
        mergeSort(nums, 0, nums.size() - 1);
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,4,3,5,1]\n
// @lcpr case=end

 */

