/*
 * @lc app=leetcode.cn id=1022 lang=cpp
 * @lcpr version=30400
 *
 * [1022] 从根到叶的二进制数之和
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
    int path;
    int res;
    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        path = (path << 1) | root->val; // 在后面加上root->val 
        
        if(root->left == nullptr && root->right == nullptr) {
            res += path; // 根节点累加结果
        } 

        traverse(root->left);
        traverse(root->right);
        path = path >> 1; // 后序位置复原，右移一位

    }
    
    int sumRootToLeaf(TreeNode* root) {
        traverse(root);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,0,1,0,1,0,1]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

