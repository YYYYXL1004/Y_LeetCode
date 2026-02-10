/*
 * @lc app=leetcode.cn id=347 lang=cpp
 * @lcpr version=30307
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start
class Solution {
public:
    // O(N log k)
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp; // val出现的频率
        for(int v : nums) mp[v]++;
        auto cmp = [](pair<int,int>& p1, pair<int,int>& p2) {
            return p1.second > p2.second; // 队列按照元素出现频率从小到大排序
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        for(auto& m : mp) {
            pq.push(m);
            if(pq.size() > k) {
                pq.pop(); // 弹出堆顶最小元素，维护队列内是 k 个频率最大的元素
            }
        }
        vector<int> res(k);
        for(int i = 0; i < k; i++) {
            res[i] = pq.top().first;
            pq.pop();
        }

        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,2,2,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,2,1,2,3,1,3,2]\n2\n
// @lcpr case=end

 */

