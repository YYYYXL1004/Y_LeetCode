#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 500005;

/* 
 * 【手写链表维护子节点】
 * 抛弃 vector 带来的拷贝开销，利用物理数组模拟链表，实现 O(1) 的子节点转移。
 * head[u]: 节点 u 的第一个子文件夹的编号
 * tail[u]: 节点 u 的最后一个子文件夹的编号
 * nxt[v]:  节点 v 的下一个“兄弟”文件夹的编号
 * sz[u]:   节点 u 当前直接包含的子文件夹数量
 */
int head[MAXN], tail[MAXN], nxt[MAXN], sz[MAXN];
long long d[MAXN]; // 记录每个文件夹的数据量

/*
 * 【DFS 序与树状数组相关】
 * in_time[u]:  进入节点 u 的时间戳（子树区间的左端点）
 * out_time[u]: 离开节点 u 的时间戳（子树区间的右端点）
 * bit[MAXN]:   树状数组，里面存的是“深度的差分数组”，用于支持 O(logN) 的区间加减
 */
int in_time[MAXN], out_time[MAXN], timer = 0;
int bit[MAXN];
int n, m;

// 树状数组标准操作：单点修改（结合差分思想，这里是对差分数组进行操作）
void add(int idx, int val) {
    // 每次向后跳 lowbit，更新所有包含该位置的父区间
    for (; idx <= n; idx += idx & -idx) bit[idx] += val;
}

// 树状数组标准操作：前缀和查询
// 因为 bit 存的是差分数组，查前缀和得到的就是经过无数次修改后，当前位置的“真实深度”
int query(int idx) {
    int sum = 0;
    // 每次向前跳 lowbit，累加所有相关的子区间
    for (; idx > 0; idx -= idx & -idx) sum += bit[idx];
    return sum;
}

/*
 * 跑 DFS 序：将复杂的树形结构“拍扁”成一维数组的连续区间。
 * 同时利用差分数组，初始化每个节点的初始深度。
 */
void dfs(int u, int dep) {
    in_time[u] = ++timer; // 打上入栈时间戳，这也是节点 u 在一维数组上的索引位置
    
    // 【核心差分操作】：在 [in_time[u], in_time[u]] 这个单点区间加上初始深度 dep
    // 使得 query(in_time[u]) 的初始值恰好为 dep
    add(in_time[u], dep);
    add(in_time[u] + 1, -dep); // 截断影响，防止误伤后排队伍
    
    // 顺着链表遍历当前节点的所有直接子节点
    for (int v = head[u]; v; v = nxt[v]) {
        dfs(v, dep + 1); // 子节点深度 +1
    }
    
    out_time[u] = timer; // 子节点全部遍历完，打上出栈时间戳，划定管辖边界
}

int main() {
    // 解绑标准输入输出流，这是应对 5*10^5 数据量防止 TLE 的基本操作
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 读入父子关系，并构建“左儿子右兄弟”的链表
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p; // i 的父亲是 p
        
        if (!head[p]) {
            head[p] = i; // 如果 p 还没有儿子，i 就是大儿子（链表头）
        } else {
            nxt[tail[p]] = i; // 如果 p 已经有儿子了，把 i 接在目前最后一个儿子的后面
        }
        tail[p] = i; // 更新 p 的最后一个儿子为 i（链表尾）
        sz[p]++;     // p 的直接子文件夹数量 +1
    }

    // 读入每个文件夹的初始数据量
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }

    // 从根节点 1 开始跑一遍 DFS，预处理出所有人的 [in, out] 区间和初始深度
    dfs(1, 1);

    // 开始处理 M 次操作
    while (m--) {
        int op, x;
        cin >> op >> x;
        
        if (op == 1) {
            // 操作 1：合并操作 (将 x 的所有直接子文件夹销毁，孙子提拔为儿子)
            long long added_d = 0;
            int new_sz = 0;
            int new_head = 0, new_tail = 0; // 用来临时存放新的儿子链表
            
            int curr = head[x]; // 从 x 的第一个直接子文件夹开始遍历
            
            while (curr) {
                // 1. 回收该子文件夹的数据量
                added_d += d[curr];
                
                // 2. 【降维打击】：curr 马上就要被销毁了，它里面包着的所有子孙文件夹，深度全部 -1
                // 利用 DFS 序转化为一维数组上的区间修改 [in_time[curr], out_time[curr]] - 1
                add(in_time[curr], -1);         // 区间起点 -1
                add(out_time[curr] + 1, 1);     // 区间终点后截断，+1 抵消影响
                
                // 3. O(1) 链表拼接：把 curr 的子文件夹集体转移给 x
                if (head[curr]) {
                    // 如果 curr 有儿子，就把 curr 的儿子链表接到 x 的新儿子链表后面
                    if (!new_head) {
                        new_head = head[curr]; 
                    } else {
                        nxt[new_tail] = head[curr];
                    }
                    new_tail = tail[curr];
                    new_sz += sz[curr]; // 更新 x 拥有的子文件夹数量
                }
                
                // 继续处理 x 的下一个直接子文件夹
                curr = nxt[curr];
            }
            
            // 4. 正式更新 x 的状态，废弃旧的儿子链表，挂上新的儿子链表
            d[x] += added_d;
            head[x] = new_head;
            tail[x] = new_tail;
            sz[x] = new_sz;
            
            cout << sz[x] << " " << d[x] << "\n";
            
        } else {
            // 操作 2：查询操作 (经过多次合并后，x 现在的深度是多少)
            // 直接利用树状数组查询 in_time[x] 的单点前缀和即可
            cout << query(in_time[x]) << "\n";
        }
    }
    return 0;
}





// 方法一：暴力（40/100)

//const int MAXN = 5e5+5;
//
//vector<int> adj[MAXN];
//unordered_map<int, int> mp;
//vector<int> depth;
//
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int n, m;  cin>>n>>m;
//	for(int i = 2; i <= n; i++) {
//		int x;  cin>>x;
//		adj[x].push_back(i);
//	}	
//	for(int i = 1; i <= n; i++) {
//		int data;  cin>>data;
//		mp[i] = data;
//	}
//	depth.assign(n+1, 0);
//	depth[1] = 1;
//	queue<int> q;
//	q.push(1);
//	while(!q.empty()) {
//		int sz = q.size();
//		for(int i = 0; i < sz; i++) {
//			int cur = q.front();  q.pop();
//			for(auto node : adj[cur]) {
//				q.push(node);
//				depth[node] = depth[cur] + 1;
//			}
//		}
//	}
//	while(m--) {
//		int op, x;  cin>>op>>x;
//		if(op == 1) {
//			vector<int> tmp;
//			for(int i = 0; i < adj[x].size(); i++) {
//				int curr = adj[x][i];
//				mp[x] += mp[curr];
//				tmp.insert(tmp.end(), adj[curr].begin(), adj[curr].end());
//				queue<int> q;
//				q.push(curr);
//				while(!q.empty()) {
//					int sz = q.size();
//					for(int i = 0; i < sz; i++) {
//						int cur = q.front();  q.pop();
//						for(auto node : adj[cur]) {
//							q.push(node);
//							depth[node]--;
//						}
//					}
//				}
//			}
//			adj[x].clear();
//			adj[x].insert(adj[x].begin(), tmp.begin(), tmp.end());
//			cout<<adj[x].size()<<" "<<mp[x]<<"\n";
//		} else {
//			cout<<depth[x]<<"\n";
//		}
//	}
//	return 0;
//}