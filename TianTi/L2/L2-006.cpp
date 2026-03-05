/*
 * L2-006 树的遍历
 * 
 * 题目描述：
 * 给定一棵二叉树的后序遍历和中序遍历，请你输出其层序遍历的序列。
 * 这里假设键值都是互不相等的正整数。
 * 
 * 输入格式：
 * 输入第一行给出一个正整数N（≤30），是二叉树中结点的个数。
 * 第二行给出其后序遍历序列。
 * 第三行给出其中序遍历序列。
 * 数字间以空格分隔。
 * 
 * 输出格式：
 * 在一行中输出该树的层序遍历的序列。
 * 数字间以1个空格分隔，行首尾不得有多余空格。
 * 
 * 输入样例：
 * 7
 * 2 3 1 5 7 6 4
 * 1 2 3 4 5 6 7
 * 
 * 输出样例：
 * 4 1 6 3 5 7 2
 * 
 * 解题思路：
 * 后序: [左子树] [右子树] [根]
 * 中序: [左子树] [根] [右子树]
 * 
 * 构建过程：
 * 1. 后序最后一个元素是根
 * 2. 在中序中找到根的位置，划分左右子树
 * 3. 递归构建左右子树
 * 4. 最后 BFS 层序遍历输出
 */

// ============================================
// 解法一：数组风格（竞赛推荐）
// ============================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int n;
vector<int> postorder, inorder;
unordered_map<int, int> inIndex;  // 值 -> 中序位置
int lch[1005], rch[1005];         // 左右子节点
// unordered_map<int, int> lch, rch; // 树节点很大时使用

// 返回子树的根节点值
int build(int postL, int postR, int inL, int inR) {
    if (postL > postR) return 0;
    
    int root = postorder[postR];  // 后序最后一个就是根
    int k = inIndex[root];        // 根在中序中的位置
    int leftSize = k - inL;       // 左子树节点数
    
    // 递归构建左右子树，用数组记录
    lch[root] = build(postL, postL + leftSize - 1, inL, k - 1);
    rch[root] = build(postL + leftSize, postR - 1, k + 1, inR);
    
    return root;
}

int main() {
    cin >> n;
    postorder.resize(n);
    inorder.resize(n);
    
    for (int i = 0; i < n; i++) cin >> postorder[i];
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
        inIndex[inorder[i]] = i;  // 建立值到位置的映射
    }
    
    int root = build(0, n - 1, 0, n - 1);
    
    // BFS 层序遍历
    queue<int> q;
    q.push(root);
    bool first = true;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!first) cout << " ";
        cout << u;
        first = false;
        
        if (lch[u]) q.push(lch[u]);
        if (rch[u]) q.push(rch[u]);
    }
    cout << endl;
    
    return 0;
}


// ============================================
// 解法二：TreeNode 风格（力扣风格）
// ============================================
#include<bits/stdc++.h>
using namespace std;

vector<int> postOrder, inOrder;
unordered_map<int, int> mp; // 值到中序遍历索引的映射

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* build(int postL, int postR, int inL, int inR) {
    if(postL > postR) return nullptr;

    int rootVal = postOrder[postR];   // 后序最后一个是根
    TreeNode* root = new TreeNode(rootVal);

    int index = mp[rootVal]; // 找到根对应中序索引的值
    int leftLen = index - inL; // 左子树长度

    root->left = build(postL, postL + leftLen - 1, inL, index - 1);
    root->right = build(postL + leftLen, postR - 1, index + 1, inR);
    return root;
}

int main() {
    int n;  cin>>n;
    postOrder.resize(n);
    inOrder.resize(n);
    for(int i = 0; i < n; i++) cin>>postOrder[i];
    for(int i = 0; i < n; i++) {
        cin>>inOrder[i];
        mp[inOrder[i]] = i;
    }

    TreeNode* root = build(0, n - 1, 0, n - 1);
    // 层序遍历
    queue<TreeNode*> q;
    q.push(root);
    bool first = true;
    while(!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();
        if(!first) cout<<" ";
        cout<< cur->val;
        first = false;
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
    return 0;
}

// ============================================
// 两种风格对比：
// 
// | 对比项       | 数组风格                    | TreeNode 风格           |
// |-------------|----------------------------|------------------------|
// | 节点表示     | 节点值直接当下标             | TreeNode* 指针          |
// | 左右孩子     | lch[root], rch[root]       | root->left, root->right|
// | 空节点       | return 0                   | return nullptr         |
// | 内存        | 预分配数组                   | new TreeNode           |
// | 适用场景     | 竞赛、值范围可控              | 力扣、面试               |
// 
// 关键点：
// 1. 哈希表加速查找：unordered_map<int, int> 记录值到中序位置的映射，O(1) 查找
// 2. 递归边界：postL > postR 时返回空
// 3. 左右子树划分：leftSize = k - inL 计算左子树节点数
// 4. 层序遍历：BFS，注意行首尾不能有空格
// ============================================
