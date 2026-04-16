#include<bits/stdc++.h>
using namespace std;

int N;
vector<int> post;
vector<int> tree; // 存完全二叉树（1-indexed），最终结果就是层序遍历
int post_idx = 0; // 追踪当前该读取哪个后序遍历的值

// 在数组下标上进行后序遍历模拟
void build(int u) {
    if(u > N) return ;
    // 后序遍历：左 -> 右 -> 根
    build(2 * u); // 递归左孩子
    build(2 * u + 1); // 递归右孩子
    // 处理根节点：按顺序取走后序遍历序列中的值，填入当前位置
    tree[u] = post[post_idx++]; 
}

int main() {
    cin>>N;
    post.resize(N);
    tree.resize(N+1);
    for(int i = 0; i < N; i++) cin>>post[i];

    build(1); // 从根节点开始模拟(完全二叉树1-based)
    // tree 数组天然就是层序遍历，直接打印！
    for (int i = 1; i <= N; i++) {
        if (i > 1) cout << " ";
        cout << tree[i];
    }
    return 0;
}


// 方法一：计算左子树长度，递归建树
// int N;
// unordered_map<int, int> lch;
// unordered_map<int, int> rch;
// vector<int> post;

// // 根据结点总数，计算左子树长度
// int left_size(int n) {
//     if(n <= 1) return 0;
//     int h = 1;
//     // (1 << h) - 1 就是 2^h - 1，表示高度为 h 的完美二叉树的总节点数
//     // 找到刚好能包住 n 个节点的完美树高度 h
//     while(((1<<h) - 1) < n) {
//         h++;
//     }
//     // 1. 最底层的左半边（属于左子树）的最大容量：2^(h-2)
//     int max_bottom_left = 1<<(h-2);
//     // 2. 实际在最底层的节点总数 = n - 上面所有层的节点总数(即高度为 h-1 的完美树)
//     int actual_bottom = n - ((1 << (h - 1)) - 1);
    
//     // 3. 分配给左子树的底层节点数 = 实际节点数 和 容量上限 的最小值
//     int left_bottom = min(actual_bottom, max_bottom_left);
    
//     // 4. 左子树上面部分的完美树节点数 = 2^(h-2) - 1
//     int left_perfect = (1 << (h - 2)) - 1;
    
//     // 左子树总大小
//     return left_perfect + left_bottom;
// }

// int build(int l, int r, int n) {
//     if(l > r || n == 0)  return 0;
//     int root = post[r];
//     lch[root] = build(l, l + left_size(n)-1, left_size(n));
//     rch[root] = build(l + left_size(n), r-1, n-left_size(n)-1);
//     return root;
// }

// int main() {
//     cin>>N;
//     post.resize(N);
//     for(int i = 0; i < N; i++) cin>>post[i];
//     int root = build(0, N-1, N); // 建树
//     queue<int> q;
//     q.push(root);
//     bool first = true;
//     while(!q.empty()) {
//         int cur = q.front();  q.pop();
//         if(!first) cout<<" ";
//         cout<<cur;
//         first = false;
//         if(lch[cur]) q.push(lch[cur]);
//         if(rch[cur]) q.push(rch[cur]);
//     }
//     return 0;
// }