/*
P1908 逆序对

题目描述
给定一段正整数序列，逆序对定义为满足 a_i > a_j 且 i < j 的有序对。
序列中可能有重复数字。

输入格式
第一行一个整数 n，表示序列长度。
第二行 n 个正整数，表示序列。

输出格式
输出序列中逆序对的数目。

样例
输入：
6
5 4 2 6 3 1
输出：
11

数据范围
1 <= n <= 5 * 10^5，单个元素不超过 10^9。
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e5+5;
int tree[MAXN];
int max_rank; // 离散化后的最大名次

// 单点修改
void add(int x, int k) {
	while(x <= max_rank) {
		tree[x] += k;
		x += (x & -x);
	}
}

// 区间查询: 查询权值在 1-x 范围内的元素总数
int query(int x) {
	ll sum = 0;
	while(x > 0) {
		sum += tree[x];
		x -= (x & -x);
	}
	return sum;
}

int main() {
	int n;  cin>>n;
	vector<int> a(n);
	vector<int> b(n);
	for(int i = 0; i < n; i++) {
		cin>>a[i];
		b[i] = a[i]; // 复制一份用于离散化
	}
	// 离散化三部曲：排序、去重、获取大小
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	max_rank = b.size();
	
	ll ans = 0;
	for(int i = n-1; i >= 0; i--) {
		// 找元素离散化后的rank
		// 因为树状数组下标必须从1开始，所以要 +1
		int rank = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
		// 查询右边严格小于当前元素的个数(rank-1)
		ans += query(rank - 1);
		add(rank, 1); // 把当前元素加到树状数组
	}
	cout<<ans<<"\n";
	return 0;
}

/*
【总结】
1. 通用模板/思路
- 适用特征：统计逆序对或满足“左大右小”关系的对数，且 n 较大。
- 标准框架：离散化值域 -> 从右往左遍历 -> 查询严格小于当前值的计数 -> 累加 -> 将当前值加入树状数组。
- 复杂度：时间 O(n log n)，空间 O(n)。
- 通用易错点：树状数组下标从 1 开始；重复值只能算严格小于；答案需用 long long。

2. 本题差异化补充
- 值域到 10^9，必须先离散化。
- 题目允许重复数字，查询用 rank - 1，避免把相等计入逆序对。
- 数据已加强，需 O(n log n) 方案。
*/