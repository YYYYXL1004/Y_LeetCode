/*
 * @lc app=leetcode.cn id=515 lang=cpp
 * @lcpr version=30307
 *
 * [515] 在每个树行中找最大值
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            int maxval = INT_MIN;
            for(int i =0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                maxval = max(maxval, cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res.push_back(maxval);
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3,2,5,3,null,9]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

 */

