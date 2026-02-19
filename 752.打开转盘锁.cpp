/*
 * @lc app=leetcode.cn id=752 lang=cpp
 * @lcpr version=30400
 *
 * [752] 打开转盘锁
 */

// @lc code=start
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        // 记录需要跳过的死亡密码
        unordered_set<string> deads(deadends.begin(), deadends.end());
        if(deads.count("0000")) return -1;

        // 记录已经穷举过的密码，防止走回头路
        unordered_set<string> visited;
        // BFS框架
        queue<string> q;
        int step = 0;
        q.push("0000");
        visited.insert("0000");

        while(!q.empty()) {
            int sz = q.size();
             // 将当前队列中的所有节点向周围扩散
            for(int i = 0; i < sz; i++) {
                string cur = q.front();
                q.pop();

                if(cur == target) return step;
                // 将一个节点的合法相邻节点加入队列
                for(string neighbors : getNeighbors(cur)) {
                    if(!visited.count(neighbors) && !deads.count(neighbors)) {
                        q.push(neighbors);
                        visited.insert(neighbors);
                    }
                }
            }
            step++;
        }
        // 如果穷举完都没找到目标密码，那就是找不到了
        return -1;
    }

    // 把s[j]上拨动一次
    string plusOne(string s, int j) {
        if(s[j] == '9') s[j] = '0';
        else s[j] += 1;
        return s;
    }
    // 把s[j]下拨动一次
    string minusOne(string s, int j) {
        if(s[j] == '0') s[j] = '9';
        else s[j] -= 1;
        return s;
    }
    
    // 将 s 的每一位向上拨动一次或向下拨动一次，8 种相邻密码
    vector<string> getNeighbors(string s) {
        vector<string> neighbors;
        for (int i = 0; i < 4; i++) {
            neighbors.push_back(plusOne(s, i));
            neighbors.push_back(minusOne(s, i));
        }
        return neighbors;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["0201","0101","0102","1212","2002"]\n"0202"\n
// @lcpr case=end

// @lcpr case=start
// ["8888"]\n"0009"\n
// @lcpr case=end

// @lcpr case=start
// ["8887","8889","8878","8898","8788","8988","7888","9888"]\n"8888"\n
// @lcpr case=end

 */

