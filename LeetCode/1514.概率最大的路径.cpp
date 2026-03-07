/*
 * @lc app=leetcode.cn id=1514 lang=cpp
 * @lcpr version=30400
 *
 * [1514] 概率最大的路径
 */

// @lc code=start
class Solution {
public:
    struct State{
        int node;
        double probFromStart;
        State(int node, double probFromStart) : node(node), probFromStart(probFromStart) {}
        // 让概率大的先出来
        bool operator <(const State& other) const {
            return probFromStart < other.probFromStart;
        }
    };

    // graph[from] -> {to, prob}
    double dijkstra(vector<vector<pair<int, double>>>& graph, int src, int dst) {
        int n = graph.size();
        vector<double> probTo(n, 0.0);

        priority_queue<State> pq;
        pq.emplace(src, 1.0);
        probTo[src] = 1.0;

        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curNode = cur.node;
            double curProbFromStart = cur.probFromStart;

            if(probTo[curNode] > curProbFromStart) continue;
            if(curNode == dst) return probTo[dst];
            for(auto& neighbor : graph[curNode]) {
                int nextNode = neighbor.first;
                double nextProbFromStart = neighbor.second * curProbFromStart;

                if(probTo[nextNode] >= nextProbFromStart) continue;
                pq.emplace(nextNode, nextProbFromStart);
                probTo[nextNode] = nextProbFromStart;
            }
        }
        return 0.0;
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> graph(n);
        // 构建图
        for(int i = 0; i < edges.size(); i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            double p = succProb[i];
            graph[a].push_back({b, p});
            graph[b].push_back({a, p});
        }

        return dijkstra(graph, start_node, end_node);
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n[[0,1],[1,2],[0,2]]\n[0.5,0.5,0.2]\n0\n2\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[0,1],[1,2],[0,2]]\n[0.5,0.5,0.3]\n0\n2\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[0,1]]\n[0.5]\n0\n2\n
// @lcpr case=end

 */

