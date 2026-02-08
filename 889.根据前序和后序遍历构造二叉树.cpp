/*
 * @lc app=leetcode.cn id=889 lang=cpp
 * @lcpr version=30307
 *
 * [889] 根据前序和后序遍历构造二叉树
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
    unordered_map<int, int> postmp; // 存postorder的valToIndex
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        for(int i = 0; i < postorder.size(); i++) postmp[postorder[i]]= i;
        return build(preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& postorder, int postStart, int postEnd) {
        if(preStart > preEnd) return nullptr;

        TreeNode* root = new TreeNode(preorder[preStart]);
        // 只有一个节点时，直接返回
        if(preStart == preEnd) return root;  // 为了保证preStart + 1 <= preEnd,即preStart < preEnd
        // 所以除了preStart>preEnd直接返回nullptr，还要有preStart == preEnd的base case

        // 左子树根节点是 preorder[preStart + 1]
        int leftRootVal = preorder[preStart + 1];
        // 在 postorder 中找到左子树根节点的位置
        int leftRootIndexInPost = postmp[leftRootVal];
        // 计算左子树的节点数量
        int leftSize = leftRootIndexInPost - postStart + 1;
        
        root->left = build(preorder, preStart + 1, preStart + leftSize, 
                          postorder, postStart, leftRootIndexInPost);
        root->right = build(preorder, preStart + leftSize + 1, preEnd, 
                           postorder, leftRootIndexInPost + 1, postEnd - 1);

        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,4,5,3,6,7]\n[4,5,2,6,7,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n[1]\n
// @lcpr case=end

 */

