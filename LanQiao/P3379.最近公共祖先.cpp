/*
P3379 【模板】最近公共祖先（LCA）

题目描述
如题，给定一棵有根多叉树，请求出指定两个点直接最近的公共祖先。

输入格式
第一行包含三个正整数 N, M, S，分别表示树的结点个数、询问的个数和树根结点的序号。
接下来 N-1 行每行包含两个正整数 x, y，表示 x 结点和 y 结点之间有一条直接连接的边（数据保证可以构成树）。
接下来 M 行每行包含两个正整数 a, b，表示询问 a, b 的最近公共祖先。

输出格式
输出包含 M 行，每行包含一个正整数，依次为每一个询问的结果。

输入输出样例
输入：
5 5 4
3 1
2 4
5 1
1 4
2 4
3 2
3 5
1 2
4 5

输出：
4
4
1
4
4

数据范围
30%: N <= 10, M <= 10
70%: N <= 10000, M <= 10000
100%: 1 <= N, M <= 5 * 10^5, 1 <= x, y, a, b <= N，不保证 a != b

样例说明
1) lca(2,4)=4
2) lca(3,2)=4
3) lca(3,5)=1
4) lca(1,2)=4
5) lca(4,5)=4
*/

#include<bits/stdc++.h>
using namespace std;

int N, M, S;
const int MAXN = 5e5 + 5;
const int LOG = 20;
vector<int> mp[MAXN];
int fa[MAXN][LOG]; // fa[u][i] 是 u 的 2^i 级祖先
// int fa[MAXN];    // 暴力版父节点
int depth[MAXN];

// 方法二：倍增 LCA
void dfs(int u, int p, int d) {
	fa[u][0] = p;
	depth[u] = d;

	for (int i = 1; i < LOG; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];  // 注意这个递推关系
	}

	for (int v : mp[u]) {
		if (v != p) {
			dfs(v, u, d + 1);
		}
	}
}

int lca(int u, int v) {
	if (u == v) return u;
	if (u == S || v == S) return S;
	if (depth[u] < depth[v]) swap(u, v);

	// 让 u 和 v 处于同一深度
	for (int i = LOG - 1; i >= 0; i--) {
		if ((depth[u] - (1 << i)) >= depth[v]) {  // 向上跳2^i层，依旧u比v深
			u = fa[u][i];
		}
		if (depth[u] == depth[v]) break;  // 对齐深度后就可以退出了
	}

	// 如果对齐深度后相遇了，说明原来的 v 就是 u 的祖先，直接下班！（千万别忘了这个边界条件）
	if (u == v) return u;

	// 一起往上跳，找 LCA 的正下方
	for (int i = LOG - 1; i >= 0; i--) {
		if (fa[u][i] != fa[v][i]) {  // 如果 u 和 v 的 2^i 级祖先不同，说明 LCA 在它们之上，u 和 v 都可以跳
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

// 方法一：暴力版 LCA（保留）
// void dfs(int u, int p, int d) {
//     fa[u] = p;
//     depth[u] = d;
//     for (int v : mp[u]) {
//         if (v != p) {
//             dfs(v, u, d + 1);
//         }
//     }
// }
//
// int lca(int u, int v) {
//     if (u == v) return u;
//     if (u == S || v == S) return S;
//     if (depth[u] < depth[v]) swap(u, v); // 让 u 更深
//     while (depth[u] > depth[v]) {
//         u = fa[u];  // 让u向上，深度减少
//     }
//     // 此时u和v在同一深度   
//     while (u != v) { // 同步向上，找交点
//         u = fa[u];
//         v = fa[v];
//     }
//     return u;
// }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M >> S;
	for (int i = 1; i <= N - 1; i++) {
		int x, y;
		cin >> x >> y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}

	dfs(S, 0, 0); // 预处理深度和倍增祖先表

	for (int i = 1; i <= M; i++) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
	return 0;
}

/*
【总结】
1. 通用模板（树上 LCA）：先 DFS 预处理 depth 和祖先表 fa[u][i]，查询时先对齐深度，再从大到小同步跳祖先。
2. 适用信号：树上多次祖先关系查询、两点路径相关问题、需要在 O(logN) 内回答每次询问。
3. 正确性直觉：对齐深度后，u/v 同步上跳且保持“仍在 LCA 下方”，第一次不能再跳时的父节点就是最近公共祖先。
4. 复杂度：预处理 O(NlogN)，单次查询 O(logN)，总计 O((N+M)logN)。
5. 本题差异：根节点由输入给出 S，预处理必须从 S 出发（不是默认 1 号点）。
6. 本题差异：数据规模到 5e5，暴力每次 O(N) 会超时，需用倍增；暴力版可保留作思路对照。
7. 易错点：对齐深度后要先判 u==v；否则在“祖先关系”场景会多跳一层导致答案错误。
8. 易错点：LOG 要覆盖最大深度（本题 2^19 < 5e5 < 2^20，取 LOG=20 可行）。
*/
