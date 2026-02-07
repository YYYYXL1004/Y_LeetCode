/*
 * @lc app=leetcode.cn id=116 lang=cpp
 * @lcpr version=30307
 *
 * [116] 填充每个节点的下一个右侧节点指针
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    // 方法一：层次遍历
    // Node* connect(Node* root) {
    //     queue<Node*> q;
    //     if(root != nullptr) q.push(root);

    //     while(!q.empty()) {
    //         int sz = q.size();
    //         Node* nodePre;
    //         Node* node;
    //         for(int i = 0; i < sz; i++) {
    //             if(i == 0) {
    //                 nodePre = q.front();
    //                 q.pop();
    //                 node = nodePre;
    //             } else {
    //                 node = q.front();
    //                 q.pop();
    //                 nodePre->next = node;   // 本层前一个节点next指向后一个
    //                 nodePre = nodePre->next;
    //             }
    //             if(node->left) q.push(node->left);
    //             if(node->right) q.push(node->right);
    //         }
    //         nodePre->next = NULL; //本层最后一个节点next指向NULL
    //     }
    //     return root;
    // }

    // 方法二：递归
    Node* connect(Node* root) {
        if(root == nullptr) return nullptr;
        traverse(root->left, root->right);
        return root;
    }

    void traverse(Node* node1, Node* node2) {
        if(node1 == nullptr || node2 == nullptr) return ;
        // 前序位置
        // 将传入的两个节点穿起来
        node1->next = node2;

        // 连接相同父节点的两个子节点
        traverse(node1->left, node1->right);
        traverse(node2->left, node2->right);
        // 连接跨越父节点的两个子节点
        traverse(node1->right, node2->left);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5,6,7]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

