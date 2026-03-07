/*
 * @lc app=leetcode.cn id=226 lang=cpp
 * @lcpr version=30307
 *
 * [226] 翻转二叉树
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
    // 解法一：遍历
    // void traverse(TreeNode* root) {
    //     if(root == nullptr) return ;
    //     // 交换左右节点
    //     TreeNode* tmp = root->left;
    //     root->left = root->right;
    //     root->right = tmp;

    //     traverse(root->left);
    //     traverse(root->right);
    // }

    // TreeNode* invertTree(TreeNode* root) {
    //     traverse(root);
    //     return root;
    // }

    // 解法二：分治
    // 定义：反转左右子树，并返回反转后的根节点
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;

        // 翻转左右子树
        TreeNode* l = invertTree(root->left);
        TreeNode* r = invertTree(root->right);

        root->left = r;
        root->right = l;       
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,7,1,3,6,9]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,3]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

