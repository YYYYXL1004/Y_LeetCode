/*
 * @lc app=leetcode.cn id=547 lang=cpp
 * @lcpr version=30400
 *
 * [547] 省份数量
 */

// @lc code=start
class Solution {
public:
    vector<int> parent;
    int count;

    void _union(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ) return ;
        parent[rootQ] = rootP;
        count--; // 联通分量减一
    }

    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        parent.resize(n + 1);
        count = n; //初始为n
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                // 如果两个城市是相连的，那么它们属于同一个连通分量
                if(isConnected[i][j] == 1) {
                    _union(i, j);
                }
            }
        }
        return count;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,1,0],[1,1,0],[0,0,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,0,0],[0,1,0],[0,0,1]]\n
// @lcpr case=end

 */

