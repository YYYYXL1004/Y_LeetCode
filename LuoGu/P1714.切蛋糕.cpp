/*
P1714 切蛋糕

题目描述
给定长度为 n 的序列 p_i，要求在所有长度不超过 m 的连续子段中，
找到一个子段使元素和最大。

形式化：最大化 sum(p_l ... p_r)，满足 1 <= l <= r <= n 且 r - l + 1 <= m。

输入格式
第一行两个整数 n, m。
第二行 n 个整数 p_i。

输出格式
输出一个整数，表示最大连续子段和（长度 <= m）。

数据范围
1 <= n <= 5 * 10^5，1 <= m <= n，|p_i| <= 500。
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
	int n, m;  cin>>n>>m;
	vector<ll> v(n+1);
	vector<ll> preSum(n + 1, 0);
	for(int i = 1; i <= n; i++) {
		cin>>v[i];
		preSum[i] = preSum[i-1] + v[i];
	}
	deque<int> dq;  // 相当于求滑动窗口中的最小值,让preSum[dq.front()] 一直最小
	ll ans = LLONG_MIN;
	// 在滑动窗口[r - m, r - 1]的范围内，寻找一个最小的preSum[k]作为被减数。
	for(int r = 1; r <= n; r++) {
		while(!dq.empty() && preSum[dq.back()] >= preSum[r-1]) {
			dq.pop_back();
		}
		dq.push_back(r-1);
		if(dq.front() < r - m) {
			dq.pop_front();
		}// preSum [r-m, r-1]
		ans = max(ans, preSum[r] - preSum[dq.front()]);
	} 
	cout<<ans;
	return 0;
}

/*
【总结】
1. 模型
- 设 preSum[i] 为前缀和，则区间 [l, r] 的和为 preSum[r] - preSum[l - 1]。
- 固定右端点 r 后，需要在 k = l - 1 属于 [r - m, r - 1] 中找最小 preSum[k]。

2. 正确性直觉
- 对每个 r，答案候选是 preSum[r] - min(preSum[k])。
- 用单调队列维护滑动窗口内 preSum 的最小值，队头始终是当前最优 k。
- 遍历所有 r，取最大即为全局最优。

3. 复杂度
- 每个下标最多入队出队一次，时间 O(n)，空间 O(n)（前缀和）/ O(m)（队列）。

4. 易错点
- 窗口是 k in [r - m, r - 1]，不要写错边界。
- 需先加入 r - 1 再计算当前 r，才能覆盖长度为 1 的区间。
- 可能全为负数，ans 需初始化为负无穷。
*/
