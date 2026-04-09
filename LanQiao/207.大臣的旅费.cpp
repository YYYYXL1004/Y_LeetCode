/*
207. 大臣的旅费

题目描述
T 王国修建了 n 个城市之间的 n - 1 条快速路，使得任意城市都能从首都到达，
且不重复经过城市时，从首都到每个城市的路线唯一。也就是说，整个路网是一棵树。

大臣 J 会从一个城市连续赶往另一个城市，中途不休息。若已经连续走了 x 千米，
那么在第 x 到 x + 1 千米这一段的花费为 x + 10。题目要求求出所有城市对之间，
J 一次不停歇赶路时可能产生的最大路费。

输入描述
第一行一个整数 n，表示城市数，1 号城市是首都。
接下来 n - 1 行，每行三个整数 Pi、Qi、Di，表示城市 Pi 和 Qi 之间有一条长度为 Di 的高速路。

输出描述
输出一个整数，表示大臣 J 最多花费的路费。

输入样例
5
1 2 2
1 3 1
2 4 5
2 5 4

输出样例
135

样例说明
大臣 J 从城市 4 到城市 5 时花费最多，为 135。
*/

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> mp;
int maxd = -1;
int max_node;

void dfs(int u, int p, int d) {
	if(d > maxd) {
		maxd = d;
		max_node = u;
	}
	for(auto pa : mp[u]) {
		int v = pa.first, vd = pa.second;
		if(v != p) {
			dfs(v, u, d+vd);
		}
	}
}


int main() {
	int n;  cin>>n;
	mp.resize(n+1);
	for(int i = 1; i < n; i++) {
		int u,v,d;  cin>>u>>v>>d;
		mp[u].emplace_back(v, d);
		mp[v].emplace_back(u, d);
	}
	dfs(1, 0, 0);
	int a_node = max_node; // 找到a节点，直径的一端
	maxd = -1;
	dfs(a_node, 0, 0);
	int b_node = max_node; //找到直径另一端b
	int ans = ((11 + 11 + (maxd-1)) * maxd) / 2;
	cout<<ans;
	return 0;
}

// 【总结】
// 1. 题目的路网满足“连通 + n - 1 条边 + 路径唯一”，本质就是一棵带权树。
// 2. 若一共走 d 千米，总花费为 11 + 12 + ... + (10 + d) = d * (d + 21) / 2，随 d 单调递增。
// 3. 所以“最大路费”可以直接转化为“树上最长简单路径”，也就是带权树直径。
// 4. 两次 DFS 即可求直径：先从任意点找到最远点 a，再从 a 出发找到最远点并得到直径长度 maxd。
// 5. 易错点是不要按边分别算费用，而要先求整条路径总长度，再套等差数列求和公式。
// 6. 如果题目数据范围较大，路径长度和最终费用通常更稳妥的写法是使用 long long。
