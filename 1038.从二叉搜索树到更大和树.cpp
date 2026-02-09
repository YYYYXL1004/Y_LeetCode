/*
 * @lc app=leetcode.cn id=1038 lang=cpp
 * @lcpr version=30307
 *
 * [1038] 从二叉搜索树到更大和树
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
        traverse(root->right);
        sum += root->val;
        root->val = sum;
        traverse(root->left);
    }
    TreeNode* bstToGst(TreeNode* root) {
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

