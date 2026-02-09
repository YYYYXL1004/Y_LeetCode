/*
 * @lc app=leetcode.cn id=538 lang=cpp
 * @lcpr version=30307
 *
 * [538] 把二叉搜索树转换为累加树
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
    int sum = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        // 先右子树后左子树中序遍历BST，就是降序访问二叉树
        traverse(root->right);
        sum += root->val;
        root->val = sum; // 转化成累加树
        traverse(root->left);
    }

    TreeNode* convertBST(TreeNode* root) {
        traverse(root);
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]\n
// @lcpr case=end

// @lcpr case=start
// [0,null,1]\n
// @lcpr case=end

 */

