/*
 * @lc app=leetcode.cn id=407 lang=cpp
 * @lcpr version=30307
 *
 * [407] 接雨水 II
 */

// @lc code=start
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.empty() || heightMap[0].empty()) return 0;
        int m = heightMap.size(), n = heightMap[0].size();
        if(m <= 2 || n <= 2) return 0; // 2*2没办法积水
        
        // 核心思想：
        // 1. 水桶原理：一个位置能装多少水，取决于他周围最低的"围栏"高度
        // 2. 从外向内：从边界开始（边界没有办法装水），逐步向内部扩展
        // 3. 贪心策略：每次选择当前最低的边界点进行扩展
        //     - 保证内部的点被访问时，外围已经形成了围栏
        //     - 当前积水量 = max(0, 围栏高度 - 当前高度)
        
        // 【BFS执行过程详解】
        // 假设矩阵：
        //   3  3  3  3  3
        //   3  2  2  2  3
        //   3  2  1  2  3
        //   3  2  2  2  3
        //   3  3  3  3  3
        //
        // 步骤1：初始化 - 所有边界（外圈的3）都加入队列
        //   队列: [(3,(0,0)), (3,(0,1)), ... 所有边界的3]
        //   这些点都标记为visited，不会再被处理
        //
        // 步骤2：从队列中取出最小的（任意一个3，假设是(0,1)）
        //   检查它的邻居：向下是(1,1)，高度为2，未访问
        //   - 积水 = max(0, 3-2) = 1
        //   - 将(1,1)加入队列，高度记为max(3,2)=3（水位）
        //   - 标记(1,1)为已访问
        //
        // 步骤3：继续取出最小的边界点，重复上述过程
        //   所有高度为3的边界点会先处理完
        //   然后处理高度为3的"新边界"（原来高度2的格子，现在水位3）
        //
        // 步骤4：最终处理到中心点(2,2)，高度1
        //   此时周围都是水位3的格子
        //   积水 = max(0, 3-1) = 2
        //
        // 关键：优先队列保证总是从最低的"围栏"向内扩展
        //      这样内部的点被访问时，外围的"水位线"已经确定

        // 优先队列：存储{高度， {行，列}} 自动按照高度从小到大排列
        // 这样每次都能去除当前最低的边界点
        priority_queue<pair<int, pair<int, int>>,
                      vector<pair<int, pair<int, int>> >, 
                      greater<pair<int, pair<int, int>>> >pq;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 初始化：所有边界点加入队列
        // 边界点是“外围栏”，他们自己不积水，但决定内部可以积多少水
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i == 0 || j == 0 || i == m - 1 ||j == n - 1) {
                    pq.push({heightMap[i][j], {i, j}});
                    visited[i][j] = true;
                }
            }
        }

        int water = 0;
        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 上下左右
        
        // BFS扩展过程
        while(!pq.empty()) {
            // 【关键1】每次取出当前最低的边界点
            // 这保证了：当处理一个内部点时，它周围所有更低的边界都已经被处理过
            // 因此当前的height就是该内部点能达到的最低"水位线"
            auto curr = pq.top(); // pair<int, pair<int, int> >
            pq.pop();
            int height = curr.first; // 当前边界点的高度，代表围栏的高度
            int x = curr.second.first;
            int y = curr.second.second;

            // 【关键2】向四个方向扩展
            // 每个边界点只向内部扩展一次（通过visited控制）
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];

                if(nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;  // 立即标记，防止重复处理
                    
                    // 【关键3】计算积水
                    // height是当前"围栏"的高度（可能是实际地面，也可能是水位）
                    // heightMap[nx][ny]是新格子的实际地面高度
                    water += max(0, height - heightMap[nx][ny]);

                    // 【关键4】新格子成为边界
                    // 新边界的高度 = max(围栏高度, 实际地面高度)
                    // - 如果地面低：水填到围栏高度，新边界高度=围栏高度
                    // - 如果地面高：没有积水，新边界高度=地面高度
                    pq.push({max(height, heightMap[nx][ny]), {nx, ny}});
                }
            }    
        }
        return water;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]\n
// @lcpr case=end

 */

