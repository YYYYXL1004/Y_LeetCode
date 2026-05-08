/*
问题描述
这天，小明在搬砖。

他一共有 n 块砖，他发现第 i 砖的重量为 w_i，价值为 v_i。他突然想从这些砖中选一些出来从下到上堆成一座塔，
并且对于塔中的每一块砖来说，它上面所有砖的重量和不能超过它自身的价值。

他想知道这样堆成的塔的总价值（即塔中所有砖块的价值和）最大是多少。

输入格式
输入共 n+1 行，第一行为一个正整数 n，表示砖块的数量。
后面 n 行，每行两个正整数 w_i, v_i 分别表示每块砖的重量和价值。

输出格式
一行，一个整数表示答案。

样例输入
5
4 4
1 1
5 2
5 5
4 3

样例输出
10

样例说明
选择第 1、2、4 块砖，从上到下按照 2、1、4 的顺序堆成一座塔，总价值为 4+1+5=10。

评测用例规模与约定
对于 20% 的数据，保证 n <= 10；
对于 100% 的数据，保证 n <= 1000；w_i <= 20；v_i <= 20000。

运行限制
最大运行时间：1s
最大运行内存：512M
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;  cin>>n;
	vector<pair<int, int>> v(n);
	for(int i = 0; i < n; i++) {
		cin>>v[i].first>>v[i].second;
	}
	auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2) {
		return p1.first + p1.second < p2.first + p2.second;
	};
	sort(v.begin(), v.end(), cmp);
	// 根据数据范围：n <= 1000, wi <= 20, vi <= 20000
	// 一块砖能作为塔底，其最大重量也就是它自身的 w 加上承重 v，即 20000 + 20 = 20020
	const int MAX_W = 20050;
	vector<int> dp(MAX_W, 0); // dp[j] 是堆叠总质量为j时的最大价值
	// 从上往下堆砖块
	for(int i = 0; i < n; i++) {
		int w = v[i].first, value = v[i].second; 
		// 0-1 背包倒序遍历
		// 上限：这块砖最多能承受上面有 v 的重量，加上它自己，总重量最高为 v + w
		// 下限：至少要放这块砖自己，也就是 w
		for(int j = w + value; j >= w; j--) {
			dp[j] = max(dp[j], dp[j - w] + value);
		} 
	}
	int ans = 0;
	for(int j = 0; j < MAX_W; j++) {
		ans = max(ans, dp[j]);
	}
	cout<<ans;
	return 0;
}

/*
【总结】
1. 题型模板：承重/堆塔约束问题常用“按 w+v 排序 + 0-1 背包”，保证加入当前砖时，上方总重不超过它的价值。
2. 标准框架：排序后遍历砖块，dp[totW] 记录总重为 totW 的最大价值，转移用 j 从大到小保证每块砖只用一次。
3. 复杂度结论：时间 O(n * Wmax)，空间 O(Wmax)，其中 Wmax 为可达的最大总重量上界。
4. 通用易错点：必须倒序更新 dp，否则会重复使用同一块砖；转移上界要用 w+v 而非全局 n 或 M。
5. 本题特化：由 w_i<=20, v_i<=20000 得到 Wmax<=20020，因此可设 MAX_W=20050。
6. 本题边界：答案是所有 dp[j] 的最大值，不必固定在某个重量点。
*/
