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
        // 和最小的在最上面
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        
        // 因为是按照非递减排序获得的nums1，所以理论上答案肯定在前k个nums1数里面组成数对
        for(int i = 0; i < min((int)nums1.size(), k); i++) { 
            pq.push({nums1[i], nums2[0], 0});
        }

        vector<vector<int>> res;
        while(!pq.empty() && k > 0) {  // 只需要保存前k个弹出的最小值即可
            vector<int> cur = pq.top();
            pq.pop();
            k--;
            // 链表中的下一个节点加入优先队列
            int next_index = cur[2] + 1;
            if(next_index < nums2.size()) {  // 全部加入
                pq.push({cur[0], nums2[next_index], next_index});
            }
            res.push_back({cur[0], cur[1]});
        }
        return res;
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

