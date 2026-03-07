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
    // vector<int> temp; // 辅助数组

    // // 对 nums[lo, hi]排序
    // void mergeSort(vector<int>& nums, int lo, int hi) {
    //     if(lo >= hi) return ; // base case;
    //     // 分：取中点，递归排序左右
    //     int mid = lo + (hi - lo) / 2;
    //     mergeSort(nums, lo, mid);
    //     mergeSort(nums, mid + 1, hi);
    //     // 合并两个有序数组
    //     merge(nums, lo, mid, hi);
    // }

    // void merge(vector<int>& nums, int lo, int mid, int hi) {
    //     // 先把nums[lo, ,hi]复制到辅助数组中，以便合并后的结果可以直接存入nums
    //     for(int i = lo; i <= hi; i++) {
    //         temp[i] = nums[i];
    //     }
    //     // 双指针合并
    //     int i = lo, j = mid + 1;
    //     for(int p = lo; p <= hi; p++) {
    //         if(i == mid + 1) {
    //             // 左半边用完，取右半边
    //             nums[p] = temp[j++];
    //         } else if(j == hi + 1) {
    //             // 右半边用完，去左半边
    //             nums[p] = temp[i++];
    //         } else if(temp[i] <= temp[j]) {
    //             // 左边较小
    //             nums[p] = temp[i++];
    //         } else {
    //             // 右边较小
    //             nums[p] = temp[j++];
    //         }
    //     }
    // }

    // vector<int> sortArray(vector<int>& nums) {
    //     temp.resize(nums.size());
    //     mergeSort(nums, 0, nums.size() - 1);
    //     return nums;
    // }

    // 手撕快速排序
    void quickSort(vector<int>& nums, int lo, int hi) {
        if(lo >= hi) return ;
        // 随机选择 pivot，避免最坏情况
        int randIdx = lo + rand() % (hi - lo + 1);
        swap(nums[lo], nums[randIdx]);

        int pivot = nums[lo];
        // 三路快排：把等于 pivot 的元素聚集在中间，跳过不再递归，处理大量重复元素效率极高
        // lt (less than)：小于区的右边界，初始指向 lo（pivot 自身的位置）
        // i：当前扫描指针，从 lo+1 开始向右扫
        // gt (greater than)：大于区的左边界，初始指向 hi
        // 不变量（循环中始终维护）：
        //   nums[lo  .. lt-1] < pivot   （严格小于区）
        //   nums[lt  .. i-1 ] == pivot  （等于区）
        //   nums[gt+1.. hi  ] > pivot   （严格大于区）
        //   nums[i   .. gt  ]           （待处理区，尚未分类）
        int lt = lo, i = lo + 1, gt = hi;
        // lo: low  hi: high  lt: less than  gt: greater than  i: iterator
        
        while(i <= gt) {  // 处理未分类的元素
            if(nums[i] < pivot) {
                // nums[i] 属于 小于区，把它换到 lt 位置，lt 和 i 都右移
                // lt 处原来是 == pivot 的元素，换到 i 处没问题
                swap(nums[i++], nums[lt++]);
            } else if(nums[i] > pivot) {
                // nums[i] 属于「大于区」把它换到 gt 位置，gt 左移
                // 注意 i 不动！因为换过来的 nums[gt] 还没检查过
                swap(nums[i], nums[gt--]);
            } else {
                // nums[i] == pivot，已在等于区，直接跳过
                i++;
            }
        }
        // 循环结束后：
        // [lo, lt-1] < pivot,  [lt, gt] == pivot,  [gt+1, hi] > pivot
        // 只需递归 [lo, lt-1] 和 [gt+1, hi]，等于区直接跳过！

        quickSort(nums, lo, lt - 1);
        quickSort(nums, gt + 1, hi);
    }

    vector<int> sortArray(vector<int>& nums) {
        srand(time(0));
        quickSort(nums, 0, nums.size() - 1);
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

