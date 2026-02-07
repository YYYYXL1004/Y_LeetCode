/*
 * @lc app=leetcode.cn id=257 lang=cpp
 * @lcpr version=30307
 *
 * [257] 二叉树的所有路径
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
    vector<string> res;
    vector<string> path;

    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        if(root->left == nullptr && root->right == nullptr) {
            path.push_back(to_string(root->val));
            res.push_back(joinPath(path));
            path.pop_back();
            return ;
        }
        // 前序位置
        path.push_back(to_string(root->val));
        traverse(root->left);
        traverse(root->right);
        // 后序位置
        path.pop_back();
    }

    string joinPath(const vector<string>& path) {
        stringstream ss;
        for(size_t i = 0; i < path.size(); i++) {
            ss << path[i];
            if(i < path.size() - 1) ss << "->";
        }
        return ss.str();
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        traverse(root);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,null,5]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

