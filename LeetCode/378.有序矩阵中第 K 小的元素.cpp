/*
 * @lc app=leetcode.cn id=378 lang=cpp
 * @lcpr version=30307
 *
 * [378] 有序矩阵中第 K 小的元素
 */

// @lc code=start
class Solution {
public:
    // O(k log n)
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 存储三元组 {matrix[i][j], i, j} i,j记录当前索引位置，用于生成下一个节点
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0];
        }; // 让大的沉底，小的在堆顶
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

        for(int i = 0; i < matrix.size(); i++) {
            pq.push({matrix[i][0], i, 0}); // 把每行的第一个元素放进去
        }

        int res = -1;
        // 执行合并多个有序链表的逻辑，找到第 k 小的元素
        while(!pq.empty() && k > 0) {
            vector<int> cur = pq.top(); // 每次弹出的都是全局第 i 小的元素
            pq.pop();
            res = cur[0];
            k--;
            // // 链表中的下一个节点加入优先级队列
            int i = cur[1], j = cur[2]; 
            if(j < matrix[i].size() - 1) {  // 只是加入一个不是剩下的全部加入
                pq.push({matrix[i][j + 1], i, j + 1});
            }  // 保证堆中始终是全局最小的m个元素
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,5,9],[10,11,13],[12,13,15]]\n8\n
// @lcpr case=end

// @lcpr case=start
// [[-5]]\n1\n
// @lcpr case=end

 */

