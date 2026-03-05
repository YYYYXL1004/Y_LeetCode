/*
 * @lc app=leetcode.cn id=988 lang=cpp
 * @lcpr version=30400
 *
 * [988] 从叶结点开始的最小字符串
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
    string path;
    string res;
    void traverse(TreeNode* root) {
        if(root == nullptr)  return ;
        path += root->val + 'a'; // 前序位置添加
        if(root->left == nullptr && root->right == nullptr) {
            reverse(path.begin(), path.end()); // 翻转比较
            if(res == "" || path < res) {
                res = path;
            }
            // 比较后复原
            reverse(path.begin(), path.end());
            // path.pop_back();
            // return ;  //好像返回有否都对，加上剔除两次无意义的递归
        }

        traverse(root->left);
        traverse(root->right);
        path.pop_back();
    }

    string smallestFromLeaf(TreeNode* root) {
        traverse(root);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,2,3,4,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [25,1,3,1,3,0,2]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,1,null,1,0,null,0]\n
// @lcpr case=end

 */

