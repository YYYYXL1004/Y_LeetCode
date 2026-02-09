/*
 * @lc app=leetcode.cn id=95 lang=cpp
 * @lcpr version=30307
 *
 * [95] 不同的二叉搜索树 II
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
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return vector<TreeNode*>{};
        return build(1, n);
    }

    vector<TreeNode*> build(int lo, int hi) {
        vector<TreeNode*> res;
        if(lo > hi) {
            // 这里需要装一个 null 元素，这样才能让下面的两个内层 for 循环都能进入，正确地创建出叶子节点
            // 举例来说吧，什么时候会进到这个 if 语句？当你创建叶子节点的时候，对吧。
            // 那么如果你这里不加 null，直接返回空列表，那么下面的内层两个 for 循环都无法进入
            // 你的那个叶子节点就没有创建出来，看到了吗？所以这里要加一个 null，确保下面能把叶子节点做出来
            res.push_back(nullptr);
            return res;
        }

        for(int i = lo; i <= hi; i++) {
            // 递归构建左右子树的所有可能
            vector<TreeNode*> leftTree = build(lo, i - 1);
            vector<TreeNode*> rightTree = build(i + 1, hi);
            // 给 root 节点穷举所有左右子树的组合
            for(TreeNode* left : leftTree) {
                for(TreeNode* right : rightTree) {
                    // 创建根节点，连接左右子树
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

