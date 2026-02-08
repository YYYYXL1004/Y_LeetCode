/*
 * @lc app=leetcode.cn id=662 lang=cpp
 * @lcpr version=30307
 *
 * [662] 二叉树最大宽度
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
    struct Pair { // 记录节点和对应编号
        TreeNode* node;
        unsigned long long id;
        Pair(TreeNode* node, unsigned long long id) : node(node), id(id) {}
    };

    int widthOfBinaryTree(TreeNode* root) {
        queue<Pair> q;
        q.push(Pair(root, 1));
        int maxWidth = 0;
        
        while (!q.empty()) {
            int sz = q.size();
            unsigned long long start = 0, end = 0;
            for(int i = 0; i < sz; i++) {
                Pair cur = q.front();
                q.pop();
                TreeNode* curNode = cur.node;
                unsigned long long curId = cur.id;
                // 记录当前行第一个id和最后一个id
                if(i == 0) start = curId;
                if(i == sz - 1) end = curId;

                if(curNode->left) q.push(Pair(curNode->left, curId * 2));
                if(curNode->right) q.push(Pair(curNode->right, curId * 2 + 1));
            }
            maxWidth = max(maxWidth, (int)(end - start + 1));
            // static_cast<int> 也是强制类型转化
        }
        return maxWidth;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3,2,5,3,null,9]\n
// @lcpr case=end

// @lcpr case=start
// [1,3,2,5,null,null,9,6,null,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,3,2,5]\n
// @lcpr case=end

 */

