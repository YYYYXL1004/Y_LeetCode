/*
 * @lc app=leetcode.cn id=144 lang=cpp
 * @lcpr version=30307
 *
 * [144] 二叉树的前序遍历
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
//     vector<int> res;
//     vector<int> preorderTraversal(TreeNode* root) {
//         traverse(root);
//         return res;
//     }
//     void traverse(TreeNode* root) {
//         if(root == nullptr)  return ;
//         res.push_back(root->val);
//         preorderTraversal(root->left);
//         preorderTraversal(root->right);
//     }

        // 解法二：分治（不常用，时间复杂度不太确定
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> res;
            if(root == nullptr) return res;

            res.push_back(root->val);
            // 后面接着左子树的前序遍历结果
            vector<int> left = preorderTraversal(root->left);
            res.insert(res.end(), left.begin(), left.end());

            vector<int> right = preorderTraversal(root->right);
            res.insert(res.end(), right.begin(), right.end());
            return res;
        }
};
// @lc code=end



/*
// @lcpr case=start
// [1,null,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5,null,8,null,null,6,7,9]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

