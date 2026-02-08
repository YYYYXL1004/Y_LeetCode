/*
 * @lc app=leetcode.cn id=637 lang=cpp
 * @lcpr version=30307
 *
 * [637] 二叉树的层平均值
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            double sum = 0;
            for(int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                sum += cur->val;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            double ans = sum / sz;
            res.push_back(ans);
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
// [3,9,20,15,7]\n
// @lcpr case=end

 */

