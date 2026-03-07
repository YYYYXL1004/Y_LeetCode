/*
 * @lc app=leetcode.cn id=222 lang=cpp
 * @lcpr version=30307
 *
 * [222] 完全二叉树的节点个数
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
    // 方法一：直接遍历 O(N)
    // int countNodes(TreeNode* root) {
    //     if(root == nullptr) return 0;
    //     return 1 + countNodes(root->left) + countNodes(root->right);
    // }

    // 方法二：一棵完全二叉树的两棵子树，至少有一棵是满二叉树 O(log N * logN)
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        TreeNode *l = root, * r= root;
        int hl = 0, hr = 0;
        while(l != nullptr) {
            l = l->left;
            hl++;
        }
        while(r != nullptr) {
            r = r->right;
            hr++;
        }

        // 如果左右侧高度相等，所以是满二叉树
        if(hl == hr) {
            return pow(2, hl) - 1;
        }
        // 如果不相等，则按照普通二叉树的逻辑计算
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5,6]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

