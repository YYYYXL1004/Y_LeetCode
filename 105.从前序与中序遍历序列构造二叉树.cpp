/*
 * @lc app=leetcode.cn id=105 lang=cpp
 * @lcpr version=30307
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
    unordered_map<int, int> mp; // valToIndex
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i =0; i < inorder.size(); i++) {
            mp[inorder[i]] = i; 
        }
        return build(preorder, 0, preorder.size() - 1, 
                    inorder, 0, inorder.size() - 1);
    }

    // 若前序遍历数组为 preorder[preStart..preEnd]，
    // 中序遍历数组为 inorder[inStart..inEnd]，
    // 构造二叉树，返回该二叉树的根节点
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd, 
                    vector<int>& inorder, int inStart, int inEnd) {
        if(preStart > preEnd) return nullptr;
        int rootVal = preorder[preStart];
        int index = mp[rootVal];
        // 找到rootVal在inorder中的位置
        // for(int i = inStart; i <= inEnd; i++) {
        //     if(rootVal == inorder[i]) {
        //         index = i;
        //         break;
        //     }
        // }

        TreeNode* root = new TreeNode(rootVal);
        int leftSize = index - inStart;
        // 注意索引的位置，画图帮助理解
        root->left = build(preorder, preStart + 1, preStart + leftSize, inorder, inStart, index - 1);
        root->right = build(preorder, preStart + leftSize + 1, preEnd, inorder, index + 1, inEnd);
        return root;
    }


};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,15,7]\n[9,3,15,20,7]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n[-1]\n
// @lcpr case=end

 */

