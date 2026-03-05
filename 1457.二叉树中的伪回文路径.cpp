/*
 * @lc app=leetcode.cn id=1457 lang=cpp
 * @lcpr version=30400
 *
 * [1457] 二叉树中的伪回文路径
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
    int cnt[10] = {0};
    int res;

    void traverse(TreeNode* root) {
        if(root == nullptr) return ;
        cnt[root->val]++;
        
        if(root->left == nullptr && root->right == nullptr) {
            int flag = 0;
            for(int i = 0; i < 10; i++) { // 只要有一个数字出现次数为奇数，且其他都是偶数，就能构成伪回文
                if(cnt[i] % 2 != 0) {
                    flag++;
                }
            }
            if(flag <= 1) res++; // 出现次数全是偶数或者只有一个奇数
        }

        traverse(root->left);
        traverse(root->right);
        cnt[root->val]--;
    }

    int pseudoPalindromicPaths (TreeNode* root) {
        traverse(root);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,1,3,1,null,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,1,1,3,null,null,null,null,null,1]\n
// @lcpr case=end

// @lcpr case=start
// [9]\n
// @lcpr case=end

 */

