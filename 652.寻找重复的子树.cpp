/*
 * @lc app=leetcode.cn id=652 lang=cpp
 * @lcpr version=30307
 *
 * [652] 寻找重复的子树
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
    unordered_map<string, int> mp; // 记录所有子树出现的次数
    vector<TreeNode*> res;  // 记录重复的子树根节点 
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        serialize(root);
        return res;
    }

    // 辅助函数，在后序位置得到完整的左右子树信息
    string serialize(TreeNode* root) {
        if(root == nullptr) {
            return "#";
        }
        // 先算左右子树的序列化结果
        string left = serialize(root->left);
        string right = serialize(root->right);

        string myself = left + "," + right + "," + to_string(root->val);

        int freq = mp[myself];
        // 多次重复只会被加入一次
        if(freq == 1) {  // 第二次遇到才加入res
            res.push_back(root);
        }
        // 给子树对应出现次数加一
        mp[myself] = freq + 1;
        return myself;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,null,2,4,null,null,4]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,2,3,null,3,null]\n
// @lcpr case=end

 */

