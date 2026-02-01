/*
 * @lc app=leetcode.cn id=88 lang=cpp
 * @lcpr version=30307
 *
 * [88] 合并两个有序数组
 */

// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 方法一：暴力法 - 合并后排序
        // 时间复杂度：O((m+n)log(m+n))，空间复杂度：O(log(m+n))
        /*
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        sort(nums1.begin(), nums1.end());
        */
        
        // 方法二：双指针从后往前 - O(m+n)
        // 时间复杂度：O(m+n)，空间复杂度：O(1)
        int p1 = m - 1;  // nums1 有效元素的末尾
        int p2 = n - 1;  // nums2 的末尾
        int p = m + n - 1;  // nums1 数组的末尾
        
        // 从后往前填充，每次选择较大的元素
        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }
        
        // 如果 nums2 还有剩余元素，复制到 nums1
        // 注意：如果 nums1 有剩余，它们已经在正确位置了
        while (p2 >= 0) {
            nums1[p--] = nums2[p2--];
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,0,0,0]\n3\n[2,5,6]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n[]\n0\n
// @lcpr case=end

// @lcpr case=start
// [0]\n0\n[1]\n1\n
// @lcpr case=end

 */

