#include<bits/stdc++.h>
using namespace std;

// 如果对一棵正宗的 BST 进行 In-order Traversal (中序遍历：左->根->右)
// 一定会得到一个严格递增的有序序列。
struct Node{
    int val;
    int left = -1;
    int right = -1;
};

vector<Node> tree;
// BST插入
int insert(int root, int val) {
    // 递归边界：找到空位了，新建一个节点并返回它的下标
    if(root == -1) {
        tree.emplace_back(val, -1, -1);
        return tree.size() - 1;
    }
    // 左边大，右边小
    if(val > tree[root].val) {
        tree[root].left = insert(tree[root].left, val);
    } else {
        tree[root].right = insert(tree[root].right, val);
    }
    return root;
}

int main() {
    int N;  cin>>N;
    int root = -1;
    for(int i = 0; i < N; i++) {
        int val;  cin>>val;
        root = insert(root, val);// 顺序插入建树
    }
    queue<int> q;  // 队列中是tree的下标
    q.push(root);
    vector<int> ans; // 层序遍历结果
    bool is_wan = true;  // 记录是不是完全二叉树
    bool seen_null = false;  // 是否在队列中遇到过空节点

    while(!q.empty()) {
        int cur = q.front();  q.pop();
        if(cur == -1) {
            seen_null = true;  // 遇到了空节点，立个 Flag
        } else {
            // 如果遇到了实体节点，但之前已经遇到过空节点了 -> 不是完全二叉树！
            if(seen_null) {
                is_wan = false;
            }
            ans.push_back(tree[cur].val);
            // 关键点：不管有没有孩子，统统压入队列！没有孩子就是压入 -1
            q.push(tree[cur].left);
            q.push(tree[cur].right);
        }
    }
    for(int i = 0; i < N; i++) {
        if(i > 0) cout<<" ";
        cout<<ans[i];
    }
    cout<<"\n"<<(is_wan ? "YES" :"NO") << "\n";
    return 0;
}