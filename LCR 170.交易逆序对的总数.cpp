/*
 * @lc app=leetcode.cn id=LCR 170 lang=cpp
 * @lcpr version=30307
 *
 * [LCR 170] 交易逆序对的总数
 */

// @lc code=start
class Solution {
public:
    // 315 是站在【左边元素】的角度统计：
    //   取左边时 → count += j - mid - 1
    //   右边用完时 → 也要统计（因为左边元素还没被统计）

    // 剑指51 是站在【右边元素】的角度统计：
    //   取右边时 → count += mid - i + 1
    //   右边用完时 → 已经都统计完了，不用加
    int count = 0;
    vector<int> temp;

    void mergeSort(vector<int>& nums, int lo, int hi) {
        if(lo >= hi) return ;
        int mid = lo + (hi - lo) / 2;
        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);
        merge(nums, lo, mid, hi);
    }
    //  逆序对的统计是站在【右边元素】的角度：
    // 取右边 temp[j] 时：
    //   说明 temp[j] 比左边 [i, mid] 都小
    //   → 这些都是逆序对 → count += mid - i + 1

    // 右边用完（j == hi + 1）时：
    //   右边的每个元素在之前被取走时，已经统计过了！
    //   不需要再统计了

    void merge(vector<int>& nums, int lo, int mid, int hi) {
        for(int i = lo; i <= hi; i++) temp[i] = nums[i];
        int i = lo, j = mid + 1;
        for(int p = lo; p <= hi; p++) {
            if(i == mid +1) {
                nums[p] = temp[j++];
            } else if(j == hi + 1) {
                nums[p] = temp[i++];
                count += j - mid - 1;  // 站在左边元素考虑
            } else if(temp[i] <= temp[j]) {
                nums[p] = temp[i++];
                count += j - mid - 1;  // 站在左边元素考虑
            } else {
                // temp[i] > temp[j] 
                // 左边 [i, mid] 的值都比 temp[j]大
                // 所以有 mid - i + 1个逆序对
                nums[p] = temp[j++];
                // count += mid - i + 1;   // 站在右边元素考虑，和左边其实是等价的
            }
        }
    }

    int reversePairs(vector<int>& record) {
        temp.resize(record.size());
        mergeSort(record, 0, record.size() - 1);
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [7,5,6,4]\n
// @lcpr case=end

 */

