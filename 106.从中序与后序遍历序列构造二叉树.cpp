/*
 * @lc app=leetcode.cn id=106 lang=cpp
 * @lcpr version=30307
 *
 * [106] 从中序与后序遍历序列构造二叉树
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
    unordered_map<int, int> mp; // 存inorder的valToIndex
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for(int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }
        return build(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& inorder, int inStart, int inEnd,
                    vector<int>& postorder, int postStart, int postEnd) {
        if(postStart > postEnd) return nullptr;

        int rootVal = postorder[postEnd];
        int index = mp[rootVal];

        TreeNode* root = new TreeNode(rootVal);
        int leftsize = index - inStart;

        root->left = build(inorder, inStart, index - 1, postorder, postStart, postStart + leftsize - 1);
        root->right = build(inorder, index + 1, inEnd, postorder, postStart + leftsize, postEnd - 1);
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [9,3,15,20,7]\n[9,15,7,20,3]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n[-1]\n
// @lcpr case=end

 */

