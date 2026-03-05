/*
 * L2-011 玩转二叉树
 * 
 * 题目描述：
 * 给定一棵二叉树的中序遍历和前序遍历，请你先将树做个镜面反转，
 * 再输出反转后的层序遍历的序列。所谓镜面反转，是指将所有非叶结点的左右孩子对换。
 * 这里假设键值都是互不相等的正整数。
 * 
 * 输入格式：
 * 输入第一行给出一个正整数N（≤30），是二叉树中结点的个数。
 * 第二行给出其中序遍历序列。
 * 第三行给出其前序遍历序列。
 * 数字间以空格分隔。
 * 
 * 输出格式：
 * 在一行中输出该树反转后的层序遍历的序列。
 * 数字间以1个空格分隔，行首尾不得有多多余空格。
 * 
 * 输入样例：
 * 7
 * 1 2 3 4 5 6 7
 * 4 1 3 2 6 5 7
 * 
 * 输出样例：
 * 4 6 1 7 5 3 2
 * 
 * 解题思路：
 * 1. 前序 + 中序 构建二叉树
 *    - 前序: [根] [左子树] [右子树]
 *    - 中序: [左子树] [根] [右子树]
 *    - 前序第一个元素是根，在中序中找到根的位置划分左右子树
 * 
 * 2. 镜面反转 = 层序遍历时先右后左
 *    - 不需要真的交换 lch 和 rch
 *    - 只需在 BFS 时先 push 右孩子，再 push 左孩子
 */

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> inOrder, preOrder;
unordered_map<int, int> mp;  // 值 -> 中序位置
int lch[1005], rch[1005];    // 左右子节点

// 前序 + 中序 构建二叉树
int build(int preL, int preR, int inL, int inR) {
    if(preL > preR) return 0;

    int root = preOrder[preL];   // 前序第一个是根
    int index = mp[root];        // 根在中序中的位置
    int leftLen = index - inL;   // 左子树长度

    lch[root] = build(preL + 1, preL + leftLen, inL, index - 1);
    rch[root] = build(preL + leftLen + 1, preR, index + 1, inR);

    return root;
}

int main() {
    cin >> n;
    inOrder.resize(n);
    preOrder.resize(n);

    for(int i = 0; i < n; i++) {
        cin >> inOrder[i];
        mp[inOrder[i]] = i;  // 建立值到中序位置的映射
    }
    for(int i = 0; i < n; i++) cin >> preOrder[i];

    int root = build(0, n - 1, 0, n - 1);

    // BFS 层序遍历，镜面反转：先右后左
    queue<int> q;
    q.push(root);
    bool first = true;

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        if(!first) cout << " ";
        cout << cur;
        first = false;

        // 镜面反转：先右后左
        if(rch[cur]) q.push(rch[cur]);
        if(lch[cur]) q.push(lch[cur]);
    }

    return 0;
}

// ============================================
// 关键点：
// 
// 1. 前序 vs 后序 构建的区别：
//    - 前序：根在第一个，preOrder[preL]
//    - 后序：根在最后一个，postOrder[postR]
// 
// 2. 镜面反转的两种实现方式：
//    方式一（本题采用）：BFS 时先右后左 push，无需修改树结构
//    方式二：构建时直接交换 lch 和 rch 的赋值
// 
// 3. 前序构建的索引推导：
//    前序: [根] [左子树(len=leftLen)] [右子树]
//           preL  preL+1 ~ preL+leftLen  preL+leftLen+1 ~ preR
//    中序: [左子树] [根] [右子树]
//           inL ~ index-1  index  index+1 ~ inR
// 
// 4. 与 L2-006 的对比：
//    | 对比项    | L2-006（后序+中序） | L2-011（前序+中序） |
//    |----------|-------------------|-------------------|
//    | 根的位置  | postOrder[postR]  | preOrder[preL]    |
//    | 左子树范围 | postL ~ postL+leftLen-1 | preL+1 ~ preL+leftLen |
//    | 右子树范围 | postL+leftLen ~ postR-1 | preL+leftLen+1 ~ preR |
//    | 额外操作  | 无                 | 镜面反转           |
// ============================================
