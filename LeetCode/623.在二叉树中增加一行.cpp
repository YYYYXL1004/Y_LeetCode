/*
 * @lc app=leetcode.cn id=623 lang=cpp
 * @lcpr version=30404
 *
 * [623] 在二叉树中增加一行
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
    int targetVal, targetDepth;
    int curDepth = 0;

    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        curDepth++;
        if(curDepth == targetDepth - 1) {
            TreeNode* newleft = new TreeNode(targetVal);
            TreeNode* newright = new TreeNode(targetVal);
            newleft->left = root->left;
            newright->right = root->right;
            root->left = newleft;
            root->right = newright;
        }

        traverse(root->left);
        traverse(root->right);

        curDepth--;
    }


    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        targetDepth = depth;
        targetVal = val;

        if(depth == 1) {
            TreeNode* newroot = new TreeNode(val);
            newroot->left = root;
            return newroot;
        }

        traverse(root);
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,6,3,1,5]\n1\n2\n
// @lcpr case=end

// @lcpr case=start
// [4,2,null,3,1]\n1\n3\n
// @lcpr case=end

 */
