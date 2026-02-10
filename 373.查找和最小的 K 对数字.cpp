/*
 * @lc app=leetcode.cn id=373 lang=cpp
 * @lcpr version=30307
 *
 * [373] 查找和最小的 K 对数字
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // 存储三元组 (nums1[i], nums2[j], i)
        // i 记录 nums2元素的索引位置，用于生成下一个节点
        auto cmp = [](const vector<int>& v1, const vector<int>& v2) {
            return (v1[0] + v1[1]) > (v2[0] + v2[1]);
        };

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,7,11]\n[2,4,6]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2]\n[1,2,3]\n2\n
// @lcpr case=end

 */

