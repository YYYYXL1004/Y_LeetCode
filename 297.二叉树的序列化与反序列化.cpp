/*
 * @lc app=leetcode.cn id=297 lang=cpp
 * @lcpr version=30307
 *
 * [297] 二叉树的序列化与反序列化
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // 方法一：前序遍历解法（推荐）
    // string SEP = ",";   // 分隔符
    // string NUL = "#";   // 空节点标记

    // // Encodes a tree to a single string.
    // // 前序遍历序列化
    // string serialize(TreeNode* root) {
    //     string res;
    //     serializeHelper(root, res);
    //     return res;
    // }

    // void serializeHelper(TreeNode* root, string& res) {
    //     if(root == nullptr) {
    //         res += NUL + SEP;
    //         return ;
    //     }
    //     // 前序位置:先记录当前位置的值
    //     res += to_string(root->val) + SEP;
    //     serializeHelper(root->left, res);
    //     serializeHelper(root->right, res);
    // }

    // // Decodes your encoded data to tree.
    // TreeNode* deserialize(string data) {
    //     // 按分隔符拆分成列表
    //     queue<string> nodes;
    //     string token;
    //     // 方法一：手动分割
    //     // for(char c : data) {
    //     //     if(c == ',') {
    //     //         nodes.push(token);
    //     //         token.clear();
    //     //     } else {
    //     //         token += c;
    //     //     }
    //     // }
    //     // 方法二：借用stringstream分割
    //     stringstream ss(data);
    //     while(getline(ss, token, ',')) { // 这里必须直接用char类型 ','
    //         nodes.push(token);
    //     }
    //     return deserializeHelper(nodes);
    // }

    // // 前序遍历反序列化
    // TreeNode* deserializeHelper(queue<string>& nodes) {
    //     if(nodes.empty()) return nullptr;
    //     string val = nodes.front();
    //     nodes.pop();
    //     // 遇到空节点标记，返回nullptr
    //     if(val == NUL) return nullptr;
    //     TreeNode* root = new TreeNode(stoi(val));
    //     // 递归构造左右子树
    //     root->left = deserializeHelper(nodes);
    //     root->right = deserializeHelper(nodes);
    //     return root;
    // }

    // 方法二：后序遍历
    // string SEP = ",";
    // string NUL = "#";

    // string serialize(TreeNode* root) {
    //     string res;
    //     _serialize(root, res);
    //     return res;
    // }

    // void _serialize(TreeNode* root, string& res) {
    //     if(root == nullptr) {
    //         res += NUL + SEP;
    //         return ;
    //     }

    //     _serialize(root->left, res);
    //     _serialize(root->right, res);
    //     // 后序位置
    //     res += to_string(root->val) + SEP;
    // }

    // TreeNode* deserialize(string data) {
    //     deque<string> nodes; // 使用双端队列才能pop_back()
    //     stringstream ss(data);
    //     string token;
    //     while(getline(ss, token, ',')) {
    //         nodes.push_back(token); // 但是deque不能直接push，需要选择push_front还是push_back
    //     }
    //     return _deserialize(nodes);
    // }

    // TreeNode* _deserialize(deque<string>& nodes) {
    //     if(nodes.empty()) return nullptr;

    //     string val = nodes.back();
    //     nodes.pop_back();
    //     if(val == NUL) return nullptr; // 记得判断空，再stoi
    //     TreeNode* root = new TreeNode(stoi(val));
    //     // 因为先从最后一个位置找的，所以先右子树再左子树
    //     root->right = _deserialize(nodes);
    //     root->left = _deserialize(nodes);

    //     return root;
    // }

    // 方法三：层序遍历
    string SEP = ",";
    string NUL = "#";

    string serialize(TreeNode* root) {
        if(root == nullptr) return "";
        string res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            for(int i =0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                // 层次遍历代码位置
                if(cur ==nullptr) {
                    res += NUL + SEP;
                    continue;
                }
                res += to_string(cur->val) + SEP;
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return res;
    }

    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;
        stringstream ss(data);
        string token;
        getline(ss, token, ','); // 取出第一个节点作为root
        TreeNode* root = new TreeNode(stoi(token));
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();

                if(!getline(ss, token, ',') || token == NUL) {
                    cur->left = nullptr;
                } else {
                    cur->left = new TreeNode(stoi(token));
                    q.push(cur->left);
                }
                if(!getline(ss, token, ',') || token == NUL) {
                    cur->right = nullptr;
                } else {
                    cur->right = new TreeNode(stoi(token));
                    q.push(cur->right);
                }
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,null,null,4,5]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */
