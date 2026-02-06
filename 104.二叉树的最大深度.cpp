/*
 * @lc app=leetcode.cn id=104 lang=cpp
 * @lcpr version=30307
 *
 * [104] 二叉树的最大深度
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
    // 方法一：遍历
    // int res = 0; // 记录最大深度
    // int depth = 0; // 记录当前递归到的节点深度

    // void traverse(TreeNode* root) {
    //     if(root == nullptr) return;
    //     // 前序位置（进入节点）增加深度
    //     depth++;
    //     // 遍历到叶子节点时记录最大深度
    //     if(root->left == nullptr || root->right == nullptr) {
    //         res = max(res, depth);
    //     }
    //     traverse(root->left);
    //     traverse(root->right);
    //     // 后序位置（离开节点）减少深度
    //     depth--;
    // }
    // int maxDepth(TreeNode* root) {
    //     traverse(root);
    //     return res;
    // }

    // 方法二：分治，一颗二叉树的深度可以由子树最大深度推导出来
    // 定义：输入一个节点，返回以该节点为根的二叉树最高高度
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftMax = maxDepth(root->left);
        int rightMax = maxDepth(root->right);

        int res = max(leftMax, rightMax) + 1;
        return res;
    }

};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2]\n
// @lcpr case=end

 */

