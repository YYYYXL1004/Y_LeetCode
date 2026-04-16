/*
L2-004 这是二叉搜索树吗？
分数 25
作者 陈越
单位 浙江大学

题目描述
一棵二叉搜索树可被递归地定义为具有下列性质的二叉树：对于任一结点，
1. 其左子树中所有结点的键值小于该结点的键值；
2. 其右子树中所有结点的键值大于等于该结点的键值；
3. 其左右子树都是二叉搜索树。

所谓二叉搜索树的“镜像”，即将所有结点的左右子树对换位置后所得到的树。
给定一个整数键值序列，请判断这是否是对一棵二叉搜索树或其镜像进行前序遍历的结果。

输入格式
第一行给出正整数 N（<=1000）。
第二行给出 N 个整数键值，其间以空格分隔。

输出格式
如果输入序列是对一棵二叉搜索树或其镜像进行前序遍历的结果，
先输出 YES，然后在下一行输出该树后序遍历结果。
数字间有 1 个空格，一行首尾不得有多余空格。
若答案是否，则输出 NO。

输入样例 1
7
8 6 5 7 10 8 11

输出样例 1
YES
5 7 6 8 11 10 8

输入样例 2
7
8 10 11 8 6 7 5

输出样例 2
YES
11 8 10 7 5 6 8

输入样例 3
7
8 6 8 5 10 9 11

输出样例 3
NO
*/

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> pre;
vector<int> post;
bool is_mirror = false;

// 前序遍历：【根】-> 【左子树】-> 【右子树】
// 检查[l, r]区间是否符合BST， 若符合，转化成post遍历
void getPost(int l, int r) {
    if(l > r) return ;
    
    int root = pre[l];
    int index = l + 1;
    // 找右子树根节点的过程，也保证了左子树都小于根
    if(!is_mirror) {
        while(index <= r && pre[index] < root) index++;
    } else {
        while(index <= r && pre[index] >= root) index++;
    }  // index是右子树的根
    
    // 检查右子树里有没有非法元素
    for(int i = index; i <= r; i++) {
        if(!is_mirror && pre[i] < root) return ;
        if(is_mirror && pre[i] >= root) return ;
    }
    // 左右子树递归检查
    getPost(l + 1, index - 1);
    getPost(index, r);
    
    // Post-order (后序遍历)：最后加入根节点
    post.push_back(root);
}

int main() {
    cin>>n;
    pre.resize(n);
    for(int i = 0; i < n; i++) {
        cin>>pre[i];
    }
    // 尝试获取post
    getPost(0, n -1);
    if(post.size() == n) {
        cout<<"YES\n";
    } else {
        post.clear();
        is_mirror = true;  // 镜像再试一次
        getPost(0, n -1);
        if(post.size() == n) {
            cout<<"YES\n";
        } else {
            cout<<"NO";
            return 0;
        }
    }
    for(int i = 0; i < post.size(); i++) {
        if(i != 0) cout<<" ";
        cout<<post[i];
    }
    return 0;
}

/*
【总结】
1. 通用模板（由前序判断 BST/镜像 BST 并还原后序）
- 适用特征：给定前序序列，要求判断是否能由某类 BST 生成，并输出后序。
- 标准框架：
  a) 取区间首元素作为根；
  b) 按 BST 规则切分左右子树区间；
  c) 校验右段是否全部合法；
  d) 递归处理左右区间，最后把根加入后序。
- 复杂度结论：每层会扫描当前区间，最坏 O(n^2)，本题 n<=1000 可通过。
- 通用易错点：重复值归属必须和题意一致（本题普通 BST 右子树允许等于根）。

2. 本题差异化补充
- 本题还需判定“镜像 BST”，可复用同一递归模板，只需把比较方向整体翻转。
- 普通 BST 规则是左 < 根、右 >= 根；镜像规则是左 >= 根、右 < 根。
- 输出要求是后序，因此在递归中按 左-右-根 的顺序压入结果。
*/
