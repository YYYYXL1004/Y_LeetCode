/*
 * @lc app=leetcode.cn id=133 lang=cpp
 * @lcpr version=30400
 *
 * [133] 克隆图
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    unordered_set<Node*> visited; // 记录 DFS 遍历过的节点，防止走回头路
    unordered_map<Node*, Node*> originToClone; // 记录原节点到克隆节点的映射

    void traverse(Node* node) {
        if(node == nullptr) return ;
        if(visited.count(node)) return ;
        // 前序位置：标记为已访问
        visited.insert(node);
        // 前序位置 克隆节点
        if(!originToClone.count(node)) {
            originToClone[node] = new Node(node->val);
        }
        Node* cloneNode = originToClone[node];

        // 递归遍历邻居节点，并构建克隆图
        for(Node* next : node->neighbors) {
            traverse(next);
             // 递归之后，邻居节点一定存在 originToClone 中
            Node* cloneNeighbor = originToClone[next];
            cloneNode->neighbors.push_back(cloneNeighbor);
        }
    }
    Node* cloneGraph(Node* node) {
        // DFS 遍历图，顺便构建克隆图
        traverse(node);
        // 从 map 里找到克隆图的对应节点
        return originToClone[node];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,4],[1,3],[2,4],[1,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[]]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

