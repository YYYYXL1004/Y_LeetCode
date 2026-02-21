/*
 * @lc app=leetcode.cn id=787 lang=cpp
 * @lcpr version=30400
 *
 * [787] K 站中转内最便宜的航班
 */

// @lc code=start
class Solution {
public:
    struct State{
        int node;
        int distFromStart;
        int edgeFromStart;
        State(int node, int distFromStart, int edgeFromStart) : node(node), distFromStart(distFromStart), edgeFromStart(edgeFromStart) {}

        bool operator< (const State& other) const {
            return distFromStart > other.distFromStart;
        }
    };

    // 带中转次数限制的 Dijkstra
    // 为什么不能用 distTo 剪枝？
    //   因为距离更短的路径可能中转次数更多，后续无法在 k 次内到达终点。
    //   反之，距离稍长但中转次数少的路径可能才是有效答案。
    //   所以改用 edgeTo（最少边数）来剪枝。
    int dijkstra(vector<vector<pair<int, int>>>& graph, int src, int dst, int k) {
        int n = graph.size();
        vector<int> edgeTo(n, INT_MAX); // edgeTo[i]: 到达节点 i 用过的最少边数

        priority_queue<State> pq;
        pq.emplace(src, 0, 0);
        edgeTo[src] = 0;
        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curNode = cur.node;
            int curDistFromStart = cur.distFromStart;
            int curEdgeFromStart = cur.edgeFromStart;

            // 最小堆保证第一次弹出终点时代价最优
            if(curNode == dst) return curDistFromStart;
            // 这条路径中转次数超了，跳过（不能 return -1，其他路径可能还行）
            if(curEdgeFromStart > k) continue;
            // 之前用更少的边数到过这个节点，当前路径没有优势，跳过
            if(edgeTo[curNode] < curEdgeFromStart) continue;

            // 在弹出时才更新 edgeTo，而不是入队时更新
            // 为什么？因为入队时提前更新可能误杀有效路径：
            //   路径A: 2条边、代价100 先入队，设 edgeTo[X]=2
            //   路径B: 3条边、代价50  入队时被 edgeTo[X]<=3 拦掉
            //   但路径B代价更低，如果 k 够大它才是答案
            // 弹出时更新就没这个问题：代价50的B会先弹出，安全处理
            edgeTo[curNode] = curEdgeFromStart;

            for(auto& neighbor : graph[curNode]) {
                int nextNode = neighbor.first;
                int nextDistFromStart = neighbor.second + curDistFromStart;
                int nextEdgeFromStart = curEdgeFromStart + 1;
                if(edgeTo[nextNode] <= nextEdgeFromStart) continue; // 边数剪枝
                pq.emplace(nextNode, nextDistFromStart, nextEdgeFromStart);
            }
        }
        return -1;
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        // 构建图（邻接表）
        for(auto& edge : flights) {
            int from = edge[0];
            int to = edge[1];
            int price = edge[2];
            graph[from].push_back({to, price});
        }
        return dijkstra(graph, src, dst, k);
    }
};

// @lc code=end



/*
// @lcpr case=start
// 4\n[[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]\n0\n3\n1\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[0,1,100],[1,2,100],[0,2,500]]\n0\n2\n1\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[0,1,100],[1,2,100],[0,2,500]]\n0\n2\n0\n
// @lcpr case=end

 */
