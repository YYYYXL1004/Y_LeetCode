/*
 * @lc app=leetcode.cn id=450 lang=cpp
 * @lcpr version=30307
 *
 * [450] 删除二叉搜索树中的节点
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // 在以root为根的BST中删除值为key的节点， 返回完成删除后的根节点
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return nullptr;
        if(root->val == key) {
            // 叶子节点，或者只有一个子树的情况
            if(root->left == nullptr) return root->right;
            if(root->right == nullptr) return root->left;
            // 找到右子树最小的点或者左子树最大的点作为新的root
            TreeNode* minNode = getMin(root->right);
            // 删除右子树最小的节点
            root->right = deleteNode(root->right, minNode->val);
            minNode->left = root->left;
            minNode->right = root->right;
            root = minNode;
        } else if(root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if(root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }

    TreeNode* getMin(TreeNode* node) {
        // BST最右侧的节点值最小
        while(node->left != nullptr) node = node->left;
        return node;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,3,6,2,4,null,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [5,3,6,2,4,null,7]\n0\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */

