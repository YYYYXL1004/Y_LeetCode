/*
 * @lc app=leetcode.cn id=102 lang=cpp
 * @lcpr version=30307
 *
 * [102] 二叉树的层序遍历
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
     // 方法二：适用于带权重的树
    class State{
    public:
        TreeNode* node;
        int depth;
        State(TreeNode* node, int depth): node(node), depth(depth) {}    
    };
    vector<vector<int>> res;
    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        queue<State> q;
        q.push(State(root, 1)); // 根节点的路径权重和是 1
        while(!q.empty()) {
            int sz = q.size();
            vector<int> v;
            for(int i = 0; i < sz; i++) {
                State cur = q.front();
                q.pop();
                v.push_back(cur.node->val);

                if(cur.node->left != nullptr) {
                    q.push(State(cur.node->left, cur.depth+1));
                }
                if(cur.node->right != nullptr) {
                    q.push(State(cur.node->right, cur.depth+1));
                }
            }
            res.push_back(v);
            v.clear();
        }
    }
    
    vector<vector<int>> levelOrder(TreeNode* root) {
        traverse(root);
        return res;
    }
    

    // 方法一：最常用
    // void traverse(TreeNode* root) {
    //     if(root == nullptr) return ;
    //     queue<TreeNode*> q;
    //     q.push(root);
    //     // 记录当前遍历的层数
    //     int depth = 1;
    //     while(!q.empty()) {
    //         int sz = q.size();
    //         vector<int> v;
    //         for(int i = 0; i < sz; i++) {
    //             TreeNode* cur = q.front();
    //             q.pop();
    //             v.push_back(cur->val);

    //             if(cur->left != nullptr) {
    //                 q.push(cur->left);
    //             } 
    //             if(cur->right != nullptr) {
    //                 q.push(cur->right);
    //             } 
    //         }
    //         depth++;
    //         res.push_back(v);
    //         v.clear(); // 清空，存放下一层
    //     }
    // }
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

