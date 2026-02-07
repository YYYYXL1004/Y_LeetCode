/*
 * @lc app=leetcode.cn id=589 lang=cpp
 * @lcpr version=30307
 *
 * [589] N 叉树的前序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> res;
    void traverse(Node* root) {
        if(root == nullptr) return ;
        // 前序位置
        res.push_back(root->val);
        for(Node* child : root->children) {
            traverse(child);
        }
        // 后序位置
    }
    vector<int> preorder(Node* root) {
        traverse(root);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,null,3,2,4,null,5,6]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]\n
// @lcpr case=end

 */

