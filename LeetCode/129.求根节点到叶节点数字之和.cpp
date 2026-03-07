/*
 * @lc app=leetcode.cn id=129 lang=cpp
 * @lcpr version=30400
 *
 * [129] 求根节点到叶节点数字之和
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
    int sum;
    string path = "";

    void traverse(TreeNode* root) {
        if(root == nullptr) return ;

        // path += root->val + '0';
        path += to_string(root->val);
        if(root->left == nullptr && root->right == nullptr) {
            sum += stoi(path); //到达叶子节点，求和
        }

        traverse(root->left);
        traverse(root->right);

        path.pop_back(); // 删除最后一个字符
        // path.erase(path.length() - 1, 1); // erase(pos, count)：从位置 pos 开始删除 count 个字符
    }

    int sumNumbers(TreeNode* root) {
        traverse(root);
        return sum;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [4,9,0,5,1]\n
// @lcpr case=end

 */

