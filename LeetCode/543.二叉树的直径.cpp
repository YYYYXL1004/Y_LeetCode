/*
 * @lc app=leetcode.cn id=543 lang=cpp
 * @lcpr version=30307
 *
 * [543] 二叉树的直径
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
    int maxDiameter = 0; // 记录最大直径
    int diameterOfBinaryTree(TreeNode* root) {
        maxDepth(root);
        return maxDiameter;
    }

    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftMax = maxDepth(root->left);
        int rightMax = maxDepth(root->right);
        // 后序位置，顺便计算最大直径
        int myDiameter = leftMax + rightMax;  // 此时的直径
        maxDiameter = max(maxDiameter, myDiameter);

        return 1 + max(leftMax, rightMax); // 明确函数定义，返回最大深度
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

 */

