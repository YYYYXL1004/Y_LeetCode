/*
 * @lc app=leetcode.cn id=773 lang=cpp
 * @lcpr version=30400
 *
 * [773] 滑动谜题
 */

// @lc code=start
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";
        // 将 2x3 的数组转化成字符串作为 BFS 的起点
        string start = "";
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                start += to_string(board[i][j]);
            }
        }
        // BFS框架
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        int step = 0;
        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                string cur = q.front();
                q.pop();
                if(target == cur) {
                    return step;
                }
                // 将数字 0 和相邻的数字交换位置
                for(string neighborBoard : getNeighbors(cur)) {
                    // 防止走回头路
                    if(!visited.count(neighborBoard)) {
                        q.push(neighborBoard);
                        visited.insert(neighborBoard);
                    }
                }
            }
            step++;
        }
        // 遍历后找不到返回-1
        return -1;
    }

    // 返回数字0和周围数字交换位置后的所有可能情况
    vector<string> getNeighbors(string board) {
        // 记录一维字符串相邻索引
        vector<vector<int>> mapping = {
            {1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}
        };

        int idx = board.find('0');
        vector<string> neighbors;
        for(int adj : mapping[idx]) {
            string new_board = board;
            swap(new_board[idx], new_board[adj]);  // swap是直接修改board本身，返回值是void
            // string new_board = swap(board[idx], board[adj]); // 所以要先深拷贝一份，再在拷贝上交换
            neighbors.push_back(new_board);
        }
        return neighbors;
    }

};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[4,0,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3],[5,4,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,1,2],[5,0,3]]\n
// @lcpr case=end

 */

