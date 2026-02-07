/*
 * @lc app=leetcode.cn id=114 lang=cpp
 * @lcpr version=30307
 *
 * [114] 二叉树展开为链表
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
    // 因为需要原地操作root，所以不能使用遍历
    // 虚拟头节点，dummy.right 就是结果
    // TreeNode* dummy = new TreeNode(-1);
    // // 用来构建链表的指针
    // TreeNode* p = dummy;

    // void traverse(TreeNode* root) {
    //     if (root == nullptr) {
    //         return;
    //     }
    //     // 前序位置
    //     p->right = new TreeNode(root->val);
    //     p = p->right;

    //     traverse(root->left);
    //     traverse(root->right);
    // }

    // 定义：将以 root 为根的树拉平为链表
    void flatten(TreeNode* root) {
        if(root == nullptr) return ;

        // 先把左右子树拉平
        flatten(root->left);
        flatten(root->right);

        // 1. 后序位置保存左右子树，此时已经是一条链表了
        TreeNode* l = root->left;
        TreeNode* r = root->right;
        // 2. 连接root和拉平后的左子树
        root->left = nullptr;
        root->right = l;
        // 3.遍历到连接后的最底部，然后连接r
        TreeNode* p =root;
        while(p->right != nullptr) {
            p = p->right;
        }
        p->right = r;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,5,3,4,null,6]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

