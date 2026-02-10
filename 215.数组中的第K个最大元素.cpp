/*
 * @lc app=leetcode.cn id=215 lang=cpp
 * @lcpr version=30307
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
class Solution {
public:
    // 方法一： 直接使用优先队列 O(Nlogk)
    // int findKthLargest(vector<int>& nums, int k) {
    //     // 小顶堆，堆顶是最小元素
    //     priority_queue<int, vector<int>, greater<int>> pq;

    //     for(auto& e : nums) {
    //         pq.push(e);
    //         // 堆中元素多于k时，删除堆顶（最小元素）
    //         if(pq.size() > k) {
    //             pq.pop();
    //         } 
    //     }
    //     // 最后pq留下 nums中最大的k个元素
    //     // 堆顶是最大元素中最早的那个，也就是第k个最大元素
    //     return pq.top();
    // }

    // 方法二 ：快速排序变体：快速选择
    // 只往一侧递归，所以期望时间 N + N/2 + N/4 + ... = O(2N) = O(N)
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0));
        // 第k的元素等于  升序排列后下标为 n-k
        int targetIdx = nums.size() - k;
        return quickSelect(nums, 0, nums.size() - 1, targetIdx);
    }

    int quickSelect(vector<int>& nums, int lo, int hi, int target) {
        // base case：当前搜索区间只剩一个元素，那么这个元素必然就是我们要找的第target大的元素
        if(lo == hi) return nums[lo];
        // 随机选择 pivot, 换到lo
        swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
        int pivot = nums[lo];

        int lt = lo, i = lo + 1, gt = hi;
        while(i <= gt) {
            if(nums[i] < pivot) {
                swap(nums[i++], nums[lt++]);
            } else if(nums[i] > pivot) {
                swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
        // 循环结束:［lo，lt-1] < pivot，[lt， gt] == pivot，[gt+1，hi] > pivot
        
        // 快速选择:只递归 target 所在的那一侧
        if(target < lt) {   
            return quickSelect(nums,lo, lt - 1, target);
        } else if(target > gt) {
            return quickSelect(nums, gt + 1, hi, target);
        } else {
            // target 落在等于区[lt，gt]，直接命中!
            return nums[target];
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,1,5,6,4]\n2\n
// @lcpr case=end

// @lcpr case=start
// [3,2,3,1,2,4,5,5,6]\n4\n
// @lcpr case=end

 */

