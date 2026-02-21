/*
 * @lc app=leetcode.cn id=743 lang=cpp
 * @lcpr version=30400
 *
 * [743] 网络延迟时间
 */

// @lc code=start
class Solution {
public:
    struct State{
        int node;
        int distFromStart;
        State(int node, int distFromStart) : node(node), distFromStart(distFromStart) {}

        // priority_queue 内部比较时会把元素当作 const 对象来调用 operator<，
        // 如果你不加末尾 const，编译会报错。
        bool operator < (const State& other) const { // 一个const都不能省略
            return distFromStart > other.distFromStart;
        }
    };
    // graph[from] -> (to, weight)
    vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int src) {
        int n = graph.size();
        vector<int> distTo(n + 1, INT_MAX); 

        priority_queue<State> pq;
        pq.emplace(src, 0);
        distTo[src] = 0;

        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curNode = cur.node;
            int curDistFormStart = cur.distFromStart;

            if(distTo[curNode] < curDistFormStart) continue; // 剪枝，已经有比目前更短的路径，跳过
            // 遍历邻居
            for(auto& neighbor : graph[curNode]) {
                int nextNode = neighbor.first;
                int nextDistFromStart = neighbor.second + curDistFormStart;

                if(distTo[nextNode] <= nextDistFromStart) continue; //剪枝
                pq.emplace(nextNode, nextDistFromStart);
                distTo[nextNode] = nextDistFromStart; //更新
            }
        }
        return distTo;
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        // 构建图（邻接表）
        for(auto& edge : times) {
            int from = edge[0];
            int to = edge[1];
            int w = edge[2];
            graph[from].push_back({to, w});
        }

        vector<int> distTo = dijkstra(graph, k);
        int res = 0;
        for(int i = 1; i <= n; i++) {
            if(distTo[i] == INT_MAX) return -1; //有未到达的节点
            res = max(res, distTo[i]);
        }
        return res;
    }


    // Dijkstra 算法中优先队列的节点状态
    // 记录「哪个节点」以及「从起点到该节点的当前最短距离」
    // struct State{
    //     int node; // 当前节点ID
    //     int distFromStart; // 从起点s到当前node的最小路径权重和
    //     State(int node, int distFromStart) : node(node), distFromStart(distFromStart) {}

    //     // 重载 < 运算符，使 priority_queue 变成最小堆
    //     // 默认 priority_queue 是最大堆，这里反转比较逻辑：
    //     // distFromStart 越大优先级越低（沉到堆底），越小越先弹出
    //     bool operator < (const State& other) const {
    //         return distFromStart > other.distFromStart;
    //     }
    // };

    // /**
    //  * Dijkstra 算法：计算从 src 出发到所有节点的最短路径
    //  * 
    //  * 核心思想（贪心 + BFS）：
    //  *   每次从优先队列中取出「距离起点最近」的节点，用它去松弛（relax）相邻节点。
    //  *   因为使用最小堆，第一次弹出某个节点时，该距离一定是最短距离。
    //  * 
    //  * 时间复杂度：O(E log V)，E 为边数，V 为节点数
    //  * 空间复杂度：O(V + E)
    //  * 
    //  * @param graph 邻接表，graph[u] = {(v, w), ...} 表示 u->v 权重为 w
    //  * @param src   起点编号
    //  * @return distTo 数组，distTo[i] 表示从 src 到 i 的最短距离，不可达则为 INT_MAX
    //  */
    // vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int src) {
    //     int n = graph.size();
    //     // distTo[i] 记录从 src 到节点 i 的当前已知最短距离
    //     // 初始化为 INT_MAX 表示尚未到达
    //     vector<int> distTo(n, INT_MAX);

    //     // 最小堆：每次弹出距离起点最近的节点
    //     priority_queue<State> pq;
    //     pq.emplace(src, 0); // 起点到自身距离为 0，等价于 pq.push(State(src, 0))
    //     distTo[src] = 0;

    //     while(!pq.empty()) {
    //         // 取出当前距离起点最近的节点
    //         State cur = pq.top();
    //         pq.pop();
    //         int curNode = cur.node;
    //         int curDistFormStart = cur.distFromStart;

    //         // 剪枝：如果当前弹出的距离已经大于已知最短距离，
    //         // 说明这是一个过时的记录（之前被更优路径更新过了），直接跳过
    //         if(distTo[curNode] < curDistFormStart) {
    //             continue;
    //         }

    //         // 松弛操作：遍历 curNode 的所有邻居，尝试更新最短路径
    //         for(auto& neighbor : graph[curNode]) {
    //             int nextNode = neighbor.first;   // 邻居节点
    //             int nextDistFromStart = curDistFormStart + neighbor.second; // 经过 curNode 到达 nextNode 的距离

    //             // 如果经过 curNode 到 nextNode 的路径并不比已知路径更短，跳过
    //             if(distTo[nextNode] <= nextDistFromStart) {
    //                 continue;
    //             }
    //             // 找到更短路径，更新 distTo 并将新状态加入优先队列
    //             pq.emplace(nextNode, nextDistFromStart);
    //             distTo[nextNode] = nextDistFromStart;
    //         }
    //     }
    //     return distTo;
    // }

    // int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    //     // 节点编号是从 1 开始的，所以要一个大小为 n + 1 的邻接表
    //     vector<vector<pair<int, int>>> graph(n + 1);
    //     // 构造邻接表：将边列表转换为 graph[from] = {(to, weight), ...}
    //     for(auto& edge : times) {
    //         int from = edge[0];
    //         int to = edge[1];
    //         int w = edge[2];
    //         graph[from].push_back({to, w});
    //     }

    //     // 从节点 k 出发，求到所有节点的最短路径
    //     vector<int> distTo = dijkstra(graph, k);

    //     // 题意：所有节点都收到信号的最短时间 = 所有最短路径中的最大值
    //     int res = 0;
    //     for(int i = 1; i <= n; i++) {
    //         if(distTo[i] == INT_MAX) return -1; // 有节点不可到达，返回 -1
    //         res = max(res, distTo[i]);
    //     }
    //     return res;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,1,1],[2,3,1],[3,4,1]]\n4\n2\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,1]]\n2\n1\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,1]]\n2\n2\n
// @lcpr case=end

 */

