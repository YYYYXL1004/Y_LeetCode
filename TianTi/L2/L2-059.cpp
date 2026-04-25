/*
L2-059 森林藏宝图

分数 25
作者 陈越
单位 浙江大学

姥姥手里有一张森林藏宝图（别问怎么得到的），图中标记了森林的入口，还画了通往多个藏宝地的小路。
画这张藏宝图的人，还贴心地为每条小路标记了一个“安全系数”，是区间 [0,100] 中的整数。

为了方便规划，姥姥给每个有分叉的路口、以及每个藏宝地都做了编号，其中森林的入口编号为 0。
略加研究后，姥姥有了一个重要的发现：如果我们一路向前不走回头路，那么从 0 号入口到每个藏宝地的路径都是存在且唯一的！
换言之，我们不可能从两条不同的岔路殊途同归地走到同一个藏宝地。
此外，从入口沿任何一条小路一直走到尽头，都会到达一个藏宝地。

姥姥不打算冒太大风险，所以只打算沿着安全系数比较大的路走。
本题请你求：如果只考虑“途经最小安全系数最大”的路径，有可能取到哪些宝藏？
即从 0 号入口到该藏宝地路径上，所有小路安全系数的最小值最大。

输入格式：
输入在第一行给出图中标记的顶点总数 n（1 < n <= 10^5）。
森林入口编号为 0，其它节点（分叉路口和藏宝地）的编号从 1 到 n-1。
随后 n-1 行，第 i（1 <= i < n）行给出编号为 i 的节点的前驱节点编号 j、以及从 j 到 i 这条小路的安全系数 s_ji（0 <= s_ji <= 100）。
一行中的数字间以空格分隔。

注：节点 i 的“前驱节点”是指从 0 出发到达 i 之前经过的那个节点。
由于从 0 到每个藏宝地路径唯一，所以每个节点的前驱节点也唯一。

输出格式：
第一行输出“解”的途经最小安全系数的最大值。
第二行按非递减顺序输出所有满足该最优值的藏宝地编号，编号间以一个空格分隔，行首尾不得有多余空格。

输入样例：
9
0 30
0 10
0 0
1 8
1 15
2 20
4 40
5 10

输出样例：
10
6 8
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
struct node{
	int to, p;
};
vector<node> adj[MAXN];
vector<pair<int, int>> ans; // 叶子节点->最小安全系数

void dfs(int root, int cur_min) {
	if(adj[root].empty()) {
		ans.emplace_back(root, cur_min);
		return ;
	}
	// int tmp = cur_min;
	for(auto n : adj[root]) {
		int v = n.to, an = n.p;
		// cur_min = min(cur_min, an);
		dfs(v, min(cur_min, an));  // 直接在传参时计算，当前层的 cur_min 保持不变，无需复原
		// cur_min = tmp; // 复原
	}
}

int main() {
	int n;  cin>>n;
	for(int i = 1; i < n; i++) {
		int x,y;  cin>>x>>y;
		adj[x].emplace_back(i, y);
	}
	dfs(0, 101);
	auto cmp = [](const pair<int,int>& p1, const pair<int,int>& p2) {
		if(p1.second == p2.second) return p1.first < p2.first;
		return p1.second > p2.second;
	};
	sort(ans.begin(), ans.end(), cmp);
	int minn = ans[0].second;
	cout<<minn<<"\n";
	cout<<ans[0].first;
	for(int i = 1; i < ans.size(); i++) {
		if(ans[i].second != minn) break;
		cout<<" "<<ans[i].first;
	}
	cout<<"\n";
	return 0;
}

// 【总结】
// 一、题型通用模板（树上“最大化路径最小值” / Maximin）
// 1. 适用特征：从根到目标路径唯一，评价函数是“路径上的最小边权”，目标是让这个最小值尽量大。
// 2. 标准做法：DFS/BFS 传递 bottleneck，设 f[v] = min(f[parent], w(parent,v))。
// 3. 终点统计：对候选终点（本题是叶子）收集 (编号, f[v])，先取最大 f，再筛出所有同最优值节点。
// 4. 复杂度：每条边访问一次，时间 O(n)，空间 O(n)（邻接表 + 递归栈/队列）。
// 5. 通用易错点：
//    - 初值要设为“比边权上界更大”的值，避免首条边被错误截断。
//    - 传递最小值时不要污染兄弟分支状态（参数传值或回溯复原）。
//
// 二、本题差异化补充
// 1. 输入直接给出“前驱 -> 当前点”，天然是一棵以 0 为根的有向树，可直接建 children 邻接表。
// 2. 宝藏点等价于叶子节点，因此只在 adj[root].empty() 时收集答案。
// 3. 先按最小安全系数降序、编号升序排序；取首个最优值后连续输出同值编号即可。
