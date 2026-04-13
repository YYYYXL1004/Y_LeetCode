/*
P1886 【模板】单调队列 / 滑动窗口

题目描述
有一个长为 n 的序列 a，以及一个大小为 k 的窗口。现在这个窗口从左边开始向右滑动，
每次滑动一个单位，求出每次滑动后窗口中的最小值和最大值。

输入格式
输入一共有两行，第一行有两个正整数 n, k；
第二行有 n 个整数，表示序列 a。

输出格式
输出共两行，第一行为每次窗口滑动的最小值；
第二行为每次窗口滑动的最大值。

输入样例
8 3
1 3 -1 -3 5 3 6 7

输出样例
-1 -3 -3 -3 3 3
3 3 5 5 6 7

说明/提示
对于 100% 的数据，1 <= k <= n <= 10^6，a_i in [-2^31, 2^31)。
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	vector<int> ans_min, ans_max;
	ans_min.reserve(n - k + 1);
	ans_max.reserve(n - k + 1);

	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}

	deque<int> dq_min, dq_max; // 分别存储最小和最大值对应的索引
	for(int r = 0; r < n; r++) {
		// 1: 先清理队尾，保持单调递减，队头就是当前窗口最大值索引
		while(!dq_max.empty() && v[dq_max.back()] <= v[r]) {
			dq_max.pop_back();
		}
		// 2: 新元素索引入队
		dq_max.push_back(r);
		// 3: 老将退役，去掉窗口左边界之外的索引
		if(dq_max.front() <= r - k) { // 有效区间是 [r - k + 1, r]
			dq_max.pop_front();
		}
		// 4: 窗口形成后记录答案
		if(r >= k - 1) {
			ans_max.push_back(v[dq_max.front()]);
		}

		// 同理求最小值：维护一个单调递增队列
		while(!dq_min.empty() && v[dq_min.back()] >= v[r]) {
			dq_min.pop_back();
		}
		dq_min.push_back(r);
		if(dq_min.front() <= r - k) {
			dq_min.pop_front();
		}
		if(r >= k - 1) {
			ans_min.push_back(v[dq_min.front()]);
		}
	}

	for(int i = 0; i < (int)ans_min.size(); i++) {
		if(i) cout << ' ';
		cout << ans_min[i];
	}
	cout << "\n";
	for(int i = 0; i < (int)ans_max.size(); i++) {
		if(i) cout << ' ';
		cout << ans_max[i];
	}

	return 0;
}

/*
【总结】
1. 通用模板（固定长度滑动窗口最值）
- 适用特征：数组区间长度固定为 k，窗口每次右移 1 位，要求每个窗口的最小/最大值。
- 标准框架：
  a) 队列里存索引，不直接存值；
  b) 入队前弹出队尾中“不可能成为答案”的元素，维持单调性；
  c) 入队当前索引；
  d) 弹出过期队头（索引 < 左边界）；
  e) 当窗口成形后，队头就是答案。
- 复杂度结论：每个元素最多进队出队各一次，总时间 O(n)，空间 O(k)。
- 通用易错点：
  a) 过期判断写错，应基于当前 r 推出左边界 r - k + 1；
  b) 队列存值会导致无法判断是否过期；
  c) 重复值处理不统一会影响稳定性。

2. 本题差异化补充
- 本题要同时输出最小值和最大值，因此维护两个队列：一个单调递增（最小），一个单调递减（最大）。
- 过期条件可写为 front <= r - k，等价于 front < r - k + 1。
- 为了让新元素覆盖旧的相等元素，最大队列用 <= 弹队尾，最小队列用 >= 弹队尾。
*/
