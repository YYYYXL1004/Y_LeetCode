/*
 * @lc app=leetcode.cn id=111 lang=cpp
 * @lcpr version=30307
 *
 * [111] 二叉树的最小深度
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
    // 方法一：DFS 全部遍历一遍
    // int mindepth = INT_MAX;
    // int mydepth = 0; // 当前深度

    // void traverse(TreeNode* root) {
    //     if(root == nullptr) return ;
    //     mydepth++; // 前序位置深度++
    //     if(root->left == nullptr && root->right == nullptr) { // 只有左右都无节点，为叶子结点时才更新最小深度
    //         mindepth = min(mindepth, mydepth);
    //     }
    //     traverse(root->left);
    //     traverse(root->right);
    //     mydepth--; // 后序位置深度--
    // }
    // int minDepth(TreeNode* root) {
    //     if(root == nullptr) return 0;
    //     traverse(root);
    //     return mindepth;
    // }

    // 方法二：BFS
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int mindepth = 1; // 初始最小深度为1
        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left == nullptr && cur->right == nullptr) {
                    return mindepth;
                }
                // 这里必须判断是否为空，因为队列会累积空节点
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right !=nullptr) q.push(cur->right);
            }
            mindepth++;
        }
        return mindepth;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [2,null,3,null,4,null,5,null,6]\n
// @lcpr case=end

 */

