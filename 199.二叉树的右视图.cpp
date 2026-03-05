/*
 * @lc app=leetcode.cn id=199 lang=cpp
 * @lcpr version=30400
 *
 * [199] 二叉树的右视图
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
    // 方法二：BFS 层序遍历
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;

        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            TreeNode* last = q.front(); // 每一层头部就是最右侧的元素
            for(int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();

                if(cur->right != nullptr) q.push(cur->right); //先右再左
                if(cur->left != nullptr) q.push(cur->left);
            }
            res.push_back(last->val);
        }
        return res;
    }


    // 方法一：DFS，递归遍历
    // vector<int> rightSideView(TreeNode* root) {
    //     traverse(root);
    //     return res;
    // }

    // vector<int> res;
    // int depth = 0;

    // void traverse(TreeNode* root) {
    //     if(root == nullptr) return ;
        
    //     depth++; 
    //     if(res.size() < depth) {
    //         res.push_back(root->val); // 把此层第一个节点放到res中
    //     }
    //     traverse(root->right);
    //     traverse(root->left); // 先遍历右再左

    //     depth--; // 后序位置还原
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,null,5,null,4]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,null,null,null,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,3]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

