/*
 * @lc app=leetcode.cn id=315 lang=cpp
 * @lcpr version=30307
 *
 * [315] 计算右侧小于当前元素的个数
 */

// @lc code=start
class Solution {
public:
    // 归并排序天然保证：
    // 1. 同组内的比较 → 在更深层的递归中已经完成 ✓
    // 2. 跨组的比较   → 在当前层 merge 中完成 ✓
    // 3. 不重复不遗漏 → 每对元素恰好在某一层被比较一次 ✓
    vector<int> count; // 记录结果
    vector<int> index;  // 每个元素的原始索引
    vector<int> tempIndex;  // 辅助数组（索引
    vector<int> temp;  // 辅助数组（值

    void mergeSort(vector<int>& nums, int lo, int hi) {
        if(lo >= hi) return ;
        int mid = lo + (hi - lo) / 2;
        // 在这个过程中，左半边内部和右半边内部的大小关系已经统计完了
        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);
        // 合并时，只需统计"跨组"的大小关系
        merge(nums, lo, mid, hi);
    }
    // 每一层的merge只负责比较左边和右边的元素，不用考虑左边元素内部的关系
    void merge(vector<int>& nums, int lo, int mid, int hi) {
        for(int i = lo; i <= hi; i++) {
            temp[i] = nums[i];
            tempIndex[i] = index[i];
        }

        int i = lo, j = mid + 1;
        for(int p = lo; p <= hi; p++) {
            if(i == mid + 1) { // 左边用完，取右边
                nums[p] = temp[j];
                index[p] = tempIndex[j];
                j++;
            } else if(j == hi + 1) { // 右边用完，取左边 说明右边元素全都比 temp[i]小
                nums[p] = temp[i];
                index[p] = tempIndex[i];  
                count[tempIndex[i]] += j - mid - 1;  // 就是 hi - mid
                i++;
            } else if(temp[i] <= temp[j]) {
                nums[p] = temp[i];
                index[p] = tempIndex[i];
                // 右边已经被取走的 [mid+1, j-1] 都比 temp[i] 小
                count[tempIndex[i]] += j - mid - 1;
                i++;
            } else{
                // temp[i] > temp[j]，取右边
                // 先不统计，让 j 继续走，等取左边时一起
                nums[p] = temp[j];
                index[p] = tempIndex[j];
                j++;
            }
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        count.resize(n ,0);
        index.resize(n);
        tempIndex.resize(n);
        temp.resize(n);

        for(int i = 0; i < n; i++) index[i] = i;
        mergeSort(nums, 0, n - 1);
        return count;
    }

    // // 暴力只能 62/66
    // vector<int> countSmaller(vector<int>& nums) {
    //     vector<int>res(nums.size());
    //     for(int i = 0; i < nums.size() ; i++) {
    //         int count = 0;
    //         for(int j = i; j < nums.size(); j++) {
    //             if(nums[i] > nums[j]) count++;
    //         }
    //         res[i] = count;
    //     }
    //     return res;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [5,2,6,1]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n
// @lcpr case=end

// @lcpr case=start
// [-1,-1]\n
// @lcpr case=end

 */

