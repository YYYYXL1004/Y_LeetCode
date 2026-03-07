/*
 * @lc app=leetcode.cn id=684 lang=cpp
 * @lcpr version=30400
 *
 * [684] 冗余连接
 */

// @lc code=start
class Solution {
public:
    vector<int> parent, rk;

    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    // 短秩挂到高秩上
    void _union(int p, int q) {
        int rp = find(p), rq = find(q);
        if(rk[rq] < rk[rp]) parent[rq] = rp;
        else if(rk[rp] < rk[rq]) parent[rp] = rq;
        else {
            parent[rq] = rp;
            rk[rp]++;
        }
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parent.resize(n + 1);
        rk.resize(n + 1, 1);
        for(int i = 1; i <= n; i++) parent[i] = i;
        vector<int> ans;
        for(auto& e : edges) {
            if(find(e[0]) == find(e[1])) ans = e; // 已连通，这条边冗余
            _union(e[0], e[1]);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[1,3],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,4],[1,5]]\n
// @lcpr case=end

 */

