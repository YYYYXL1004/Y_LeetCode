/*
 * 题目：二叉树的三种遍历
 * 
 * 给定一棵二叉树，计算它的前序、中序、后序遍历结果。
 * 
 * 三种遍历顺序的定义：
 * - 前序遍历：先访问根节点，再递归遍历左子树，最后递归遍历右子树
 * - 中序遍历：先递归遍历左子树，再访问根节点，最后递归遍历右子树
 * - 后序遍历：先递归遍历左子树，再递归遍历右子树，最后访问根节点
 * 
 * 输入：节点值数组 values，边数组 edges
 * 输出：三行遍历结果
 */

#include<iostream>
using namespace std;
#include<vector>

vector<int> preorder;
vector<int> inorder;
vector<int> postorder;
/*
 * 邻接表表示树结构（无向图）
 * tree[i] 存储与节点 i 相邻的所有节点
 * 例如边 (1,2) 会使 tree[1] 包含 2，tree[2] 包含 1
 * 遍历时通过 parent 参数区分父节点和子节点
 */
vector<vector<int>> tree;
vector<int> values;  // values[i] 存储节点 i+1 的值（0-indexed）

void clear() {
    preorder.clear();
    inorder.clear();
    postorder.clear();
    tree.clear();
    values.clear();
}

void traverse(int node, int parent) {
    // 过滤出子节点（排除父节点）
    // 由于是无向图，tree[node] 中包含父节点，需要排除
    vector<int> children;
    for(int child : tree[node]) {
        if(child != parent) {
            children.push_back(child);
        }
    }
    // 前序位置
    preorder.push_back(values[node - 1]);
    // 递归左子树
    if(children.size() >= 1) {
        traverse(children[0], node);
    }
    // 中序位置
    inorder.push_back(values[node - 1]);
    // 递归右子树
    if(children.size() >= 2) {
        traverse(children[1], node);
    }
    // 后序位置
    postorder.push_back(values[node - 1]);
}

void solve(int n, vector<int>& vals, vector<vector<int>>& edges) {
    values = vals;
    tree.resize(n + 1);  // 节点编号从1开始，需要n+1的空间

    // 构建无向图（邻接表）
    // 每条边 (u, v) 双向存储，便于从任意节点遍历
    for(auto& edge : edges) {
        tree[edge[0]].push_back(edge[1]);
        tree[edge[1]].push_back(edge[0]);
    }
    // 从根节点1开始遍历，父节点设为-1表示无父节点
    traverse(1, -1);

    for(int i = 0; i < n; i++) {
        if(i > 0) cout<<" ";
        cout << preorder[i];
    }
    cout << endl;

    for(int i = 0; i < n; i++) {
        if(i > 0) cout<<" ";
        cout << inorder[i];
    }
    cout << endl;

    for(int i = 0; i < n; i++) {
        if(i > 0) cout<<" ";
        cout << postorder[i];
    }
    cout << endl;
}

int main() {
    int n;
    while(cin >> n) {  // 支持多组输入输出
        clear();  // 重置所有全局状态
        
        values.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> values[i];
        }

        vector<vector<int>> edges;
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }

        solve(n, values, edges);
    }
    return 0;
}
/*
 * 示例：
 * 输入：
 * 5
 * 10 20 30 40 50
 * 1 2
 * 1 3
 * 2 4
 * 2 5
 * 
 * 树结构：
 *       1(10)
 *      /    \
 *    2(20)  3(30)
 *   /    \
 * 4(40)  5(50)
 * 
 * 输出：
 * 10 20 40 50 30  (前序)
 * 40 20 50 10 30  (中序)
 * 40 50 20 30 10  (后序)
 */
