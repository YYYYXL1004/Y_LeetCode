/*
题目描述
小明的实验室有 N 台电脑，编号 1...N。原本这 N 台电脑之间有 N-1 条数据链接相连，
恰好构成一个树形网络。在树形网络上，任意两台电脑之间有唯一的路径相连。

不过在最近一次维护网络时，管理员误操作使得某两台电脑之间增加了一条数据链接，
于是网络中出现了环路。环路上的电脑由于两两之间不再是只有一条路径，
使得这些电脑上的数据传输出现了 BUG。

为了恢复正常传输。小明需要找到所有在环路上的电脑，你能帮助他吗？

输入描述
第一行包含一个整数 N。
以下 N 行每行两个整数 a, b，表示 a 和 b 之间有一条数据链接相连。

数据范围：
1 <= N <= 1e5
1 <= a, b <= N
输入保证合法。

输出描述
按从小到大的顺序输出在环路上的电脑编号，中间由一个空格分隔。

样例输入
5
1 2
3 1
2 4
2 5
5 3

样例输出
1 2 3 5
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
vector<int> mp[MAXN];
bool found = false;
vector<int> fa(MAXN);      // fa[x] 记录 DFS 树中的父节点
vector<int> visited(MAXN); // 0: 未访问, 1: 已访问
vector<int> cycle;

void dfs(int u, int p) {
	if (found) return;
	fa[u] = p;
	visited[u] = 1;

	for (int v : mp[u]) {
		if (found) return;
		if (v == p) continue;

		if (visited[v] == 1) {
			// 找到返祖边，v 为环起点，u 为当前终点，沿父链回溯得到整环
			found = true;
			int cur = u;
			while (cur != v) {
				cycle.push_back(cur);
				cur = fa[cur];
			}
			cycle.push_back(v);  // 别忘了把环起点也加入答案
			return;
		}

		dfs(v, u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}

	dfs(1, 0);
	sort(cycle.begin(), cycle.end());

	for (int i = 0; i < (int)cycle.size(); i++) {
		if (i) cout << ' ';
		cout << cycle[i];
	}
	return 0;
}

/*
【总结】
1. 核心模型：无向图 DFS 找到第一条“访问过且不是父节点”的返祖边，即可定位唯一环。
2. 正确性关键：原图是“树 + 1 条边”，因此只会多出一个简单环；从当前点沿父链回溯到返祖点，恰好得到该环全部节点。
3. 复杂度：建图 O(N)，DFS O(N)，排序环点 O(k log k)（k 为环长，k <= N），总复杂度 O(N + k log k)。
4. 空间复杂度：邻接表 + 访问/父节点数组，O(N)。
5. 易错点：无向图遍历时必须跳过父节点（v == p），否则会把树边反向误判成环。
6. 易错点：发现环后要及时终止后续 DFS，避免重复回溯污染答案。
*/
