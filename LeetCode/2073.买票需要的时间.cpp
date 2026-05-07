/*
 * @lc app=leetcode.cn id=2073 lang=cpp
 * @lcpr version=30403
 *
 * [2073] 买票需要的时间
 */

// @lc code=start
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        // int res = 0;
        // for(int i = 0; i < tickets.size(); i++) {
        //     if(i <= k) {
        //         // 前面的人最多买 ticket[k]张票
        //         res += min(tickets[k], tickets[i]);
        //     } else {
        //         // 后面的人最多买 ticket[k]-1张票
        //         res += min(tickets[k] - 1, tickets[i]);
        //     }
        // }
        // return res;

        // 方法二：直接队列模拟
        queue<int> q;
        // 把下标存在队列
        for(int i = 0; i < tickets.size(); i++) {
            q.push(i);
        }
        int time = 0;
        while(!q.empty()) {
            int cur = q.front();  // 队首下标
            q.pop();
            // 队首买票
            tickets[cur]--;
            time++;
            if(tickets[cur] == 0 && cur == k) return time;
            if(tickets[cur] > 0) { // 还需要买票就继续排队
                q.push(cur);
            }
        }
        return time;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,2]\n2\n
// @lcpr case=end

// @lcpr case=start
// [5,1,1,1]\n0\n
// @lcpr case=end

 */

