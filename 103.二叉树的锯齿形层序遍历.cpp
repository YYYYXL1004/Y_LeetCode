/*
 * @lc app=leetcode.cn id=103 lang=cpp
 * @lcpr version=30307
 *
 * [103] 二叉树的锯齿形层序遍历
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        while(!q.empty()) {
            int sz = q.size();
            vector<int> level;
            for(int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                level.push_back(cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            if(depth % 2 == 0) reverse(level.begin(), level.end());
            res.push_back(level);
            depth++;
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

