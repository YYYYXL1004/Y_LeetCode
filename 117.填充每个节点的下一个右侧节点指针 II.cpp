/*
 * @lc app=leetcode.cn id=117 lang=cpp
 * @lcpr version=30307
 *
 * [117] 填充每个节点的下一个右侧节点指针 II
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
    Node* connect(Node* root) {
        if(root == nullptr) return root;
        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            Node* pre = nullptr; // 遍历一层
            for(int i = 0; i < sz; i++) {
                Node* cur = q.front();
                q.pop();
                // 链接当前层所有节点的 next 指针
                if(pre != nullptr) {
                    pre->next = cur;
                }
                pre = cur;

                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            pre = nullptr; // 遍历完一层，置空
        }
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5,null,7]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

