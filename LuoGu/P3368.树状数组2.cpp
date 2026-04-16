/*
题目描述
如题，已知一个数列，你需要进行下面两种操作：
1. 将某区间每一个数加上 x；
2. 求出某一个数的值。

输入格式
第一行包含两个整数 N、M，分别表示该数列数字的个数和操作的总个数。
第二行包含 N 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 M 行每行包含 2 或 4 个整数，表示一个操作，具体如下：
操作 1：1 x y k，含义：将区间 [x, y] 内每个数加上 k；
操作 2：2 x，含义：输出第 x 个数的值。

输出格式
输出包含若干行整数，即为所有操作 2 的结果。

输入输出样例
输入：
5 5
1 5 4 2 3
1 2 4 2
2 3
1 1 5 -1
1 3 5 7
2 4

输出：
6
10

数据范围
对于 30% 的数据：N <= 8，M <= 10；
对于 70% 的数据：N <= 1e4，M <= 1e4；
对于 100% 的数据：1 <= N, M <= 5e5，1 <= x, y <= N，
保证任意时刻序列中任意元素的绝对值都不大于 2^30。
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e5 + 5;
ll tree[MAXN];
int n, m;

int lowbit(int x) {
	return x & (-x);
}

void update(int x, ll val) {
	for(int i = x; i <= n; i += lowbit(i)) {
		tree[i] += val;
	}
}

ll query(int x) {
	ll sum = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		sum += tree[i];
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	ll cur = 0, last = 0;
	for(int i = 1; i <= n; i++) {
		cin >> cur;
		update(i, cur - last); // 存差分数组 d[i] = a[i] - a[i-1]
		last = cur;
	}

	while(m--) {
		int op;
		cin >> op;
		if(op == 1) {
			int x, y;
			ll k;
			cin >> x >> y >> k;
			update(x, k);
			if(y + 1 <= n) update(y + 1, -k);
		} else if(op == 2) {
			int x;
			cin >> x;
			cout << query(x) << "\n";
		}
	}
	return 0;
}

/*
【总结】
1. 通用模板（区间加 + 单点查询）
- 适用特征：操作是“区间整体加值”，查询是“某个位置当前值”。
- 标准做法：把原数组转为差分数组 d，区间 [l, r] 加 k 等价于 d[l] += k, d[r+1] -= k。
- 数据结构：用树状数组维护差分数组的前缀和，query(x) 即 a[x]。

2. 正确性直觉
- 原值满足 a[x] = d[1] + d[2] + ... + d[x]。
- 每次区间加只改动差分的两个端点，树状数组维护这些改动后的前缀和，因此 query(x) 始终得到当前位置真实值。

3. 复杂度
- 建树（按输入逐项转差分并 update）：O(n log n)。
- 每次操作：O(log n)。
- 总复杂度：O((n + m) log n)，空间 O(n)。

4. 易错点
- 注意 d[r+1] -= k 时要判断 r+1 是否越界。
- 差分值和答案都可能较大，建议用 long long。
- 树状数组是 1 下标，循环边界要与题目下标一致。

5. 本题差异化补充
- 本题只查单点，不查区间和，所以“树状数组维护差分”比“维护原数组前缀和”更直接。
- 题目数据范围到 5e5，朴素区间修改会超时，必须使用对数级更新/查询。
*/
