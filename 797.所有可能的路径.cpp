/*
 * @lc app=leetcode.cn id=797 lang=cpp
 * @lcpr version=30400
 *
 * [797] 所有可能的路径
 */

// @lc code=start
class Solution {
public:
    // DFS,没有环，不用标记visited[]
    vector<vector<int>> res;
    vector<int> path;

    void traverse(vector<vector<int>>& graph, int s) {
        path.push_back(s); // 添加节点 s 到路径
        int n = graph.size();
        if(s == n - 1) {  // 到达终点
            res.push_back(vector<int>(path));
            path.pop_back();
            return ;
        }

        for(int v : graph[s]) {
            traverse(graph, v);
        }

        path.pop_back();
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        traverse(graph, 0);
        return res;
    }

    //  BFS(空间复制开销大) 本题更推荐使用DFS
    // vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    //     vector<vector<int>> res;
    //     int n = graph.size();
    //     queue<vector<int>> q;  // 放整个路径
    //     q.push({0});

    //     while(!q.empty()) {
    //         vector<int> path = q.front();
    //         q.pop();
    //         int last = path.back();
    //         if(last == n - 1) {  // 找到一条路径
    //             res.push_back(path);
    //             continue;
    //         }

    //         for(int next : graph[last]) {
    //             vector<int> newPath(path); // 复制现有的路径
    //             newPath.push_back(next);
    //             q.push(newPath);
    //         }
    //     }
    //     return res;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[3],[3],[]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,3,1],[3,2,4],[3],[4],[]]\n
// @lcpr case=end

 */

