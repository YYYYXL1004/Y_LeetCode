/*
 * @lc app=leetcode.cn id=700 lang=cpp
 * @lcpr version=30307
 *
 * [700] 二叉搜索树中的搜索
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
    // 定义：在以 root 为根的 BST 中搜索值为 target 的节点，返回该节点
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) return nullptr;
        // 二分思维
        if(root->val > val) return searchBST(root->left, val);
        if(root->val < val) return searchBST(root->right, val);
        return root;    
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,7,1,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [4,2,7,1,3]\n5\n
// @lcpr case=end

 */

