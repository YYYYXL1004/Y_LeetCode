/*
P3374 【模板】树状数组 1

题目描述：
如题，已知一个数列，你需要进行下面两种操作：
1. 将某一个数加上 x；
2. 求出某区间每一个数的和。

输入格式：
第一行包含两个正整数 n, m，分别表示该数列数字的个数和操作的总个数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 m 行每行包含 3 个整数，表示一个操作，具体如下：
1 x k：将第 x 个数加上 k；
2 x y：输出区间 [x,y] 内每个数的和。

输出格式：
输出包含若干行整数，即为所有操作 2 的结果。

输入样例：
5 5
1 5 4 2 3
1 1 3
2 2 5
1 3 -1
1 4 2
2 1 4

输出样例：
14
16

数据范围：
1 <= n, m <= 5 * 10^5，1 <= x <= y <= n，-2^31 <= k < 2^31。
数据保证任意时刻任意子区间和都在 [-2^31, 2^31) 范围内。
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define debug(x) cout<<#x<<" "<<x<<"\n"

const int MAXN = 5e5+5;
ll tree[MAXN];

int lowbit(int x) {
	return x & (-x);
}

void update(int x, ll val) {
	for(int i = x; i < MAXN; i += lowbit(i)) {
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
	int n, m;  cin>>n>>m;
	for(int i = 1; i <= n; i++) {
		ll x;  cin>>x;
		update(i, x);
	}
	while(m--) {
		ll op, x, y;
		cin>>op>>x>>y;
		if(op == 1) {
			update(x, y);
		} else if(op == 2) {
			cout<<query(y) - query(x-1)<<"\n";
		}
	}
	return 0;
}

// 【总结】
// 题型通用模板：
// 1. 看到“单点修改 + 区间求和”可直接使用树状数组（Fenwick Tree）。
// 2. 用 tree[] 维护前缀信息：update(pos, delta) 负责把影响沿 lowbit 链向上累加。
// 3. 前缀和 query(r) 可在 O(log n) 得到，区间和由 query(r)-query(l-1) 转化。
// 4. 复杂度：每次操作 O(log n)，总复杂度 O((n+m)log n)，空间 O(n)。
//
// 本题差异化补充：
// 1. n,m 可达 5e5，朴素逐项修改或逐项求和会超时，必须用对数级结构。
// 2. k 可能为负，update 直接加 delta 仍然成立。
// 3. 题目保证区间和在 32 位范围内；实现中用 long long 更稳妥。
