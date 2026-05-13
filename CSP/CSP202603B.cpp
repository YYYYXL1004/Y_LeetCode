/*
题目描述
小 P 计划招募 n 个机器人完成项目，每个机器人负责一项任务 i。
任务完成耗时为 t_i，总耗时为 t_1+t_2+...+t_n。

小 P 可用最多 m 杯咖啡加速。任务 i 最多喝 a_i 杯咖啡，最多缩短 b_i，
缩短后耗时为 t_i-b_i。

任务分为两类：
1) 灵活型：可提供 [0, a_i] 任意实数杯，若给 k_i * a_i 杯，耗时缩短 k_i*b_i (0<=k_i<=1)。
2) 普通型：只能给 0 或 a_i 杯，不能分配半杯。

给定 m，求完成整个项目的最短时间。

输入格式
第一行 n m。
接下来 n 行，每行 o_i t_i a_i b_i。
o_i=0 表示灵活型，o_i=1 表示普通型。保证 t_i>b_i。

输出格式
输出一个实数，表示最短时间。绝对误差 < 0.001。

输入数据 1
3 5
0 2 3 1
0 3 4 2
0 4 5 2

输出数据 1
6.6

输入数据 2
5 62
0 10 2 1
0 10 1 1
1 500 40 360
1 600 50 500
1 400 20 150

输出数据 2
1008.5

数据范围
0 < n <= 200, 0 < m <= 1000
0 < a_i <= 100, 0 < b_i < t_i <= 1e4
*/
#include<bits/stdc++.h>
using namespace std;

struct task{
	double t, a, b;
	task(double t, double a, double b) : t(t),a(a),b(b) {}
};

int main() {
	int n, m;  cin>>n>>m;
	vector<task> v0;  // 灵活 
	vector<task> v1;  // 普通
	double sum = 0.0;
	for(int i = 0; i < n; i++) {
		int type;  cin>>type;
		double t, a, b; 
		cin>>t>>a>>b;
		sum += t;  // 先计算原本的总时间
		if(type == 0) {
			v0.emplace_back(t,a,b);
		} else if(type == 1) {
			v1.emplace_back(t,a,b);
		}
	}
	auto cmp = [](const task& t1, const task& t2) {
		return t1.a / t1.b < t2.a / t2.b;
	};
	sort(v0.begin(), v0.end(), cmp);
	
	vector<double> dp(m+1, 0.0);  // dp[i]分配给普通任务i杯可减少最大时间
	// 0/1背包
	for(const auto& ta : v1) {
		for(int j = m; j >= (int)ta.a; j--) {
			dp[j] = max(dp[j], dp[j-(int)ta.a] + ta.b);
		}
	}
	double maxt = 0.0;  // 总的最大缩减时间
	for(int j = 0; j <= m; j++) {
		double cur_t = dp[j];
		double remain = m-j;  // 剩下的coffee
		for(const auto& ta : v0) {
			if(remain <= 0) break;
			if(remain >= ta.a) {
				cur_t += ta.b;
				remain -= ta.a;
			} else {
				cur_t += (remain / ta.a * ta.b);
				remain = 0.0;
			}
		}
		maxt = max(maxt, cur_t);  // 更新最大缩短时间
	}
	printf("%.6f", sum-maxt);
	return 0;
}

/*
【总结】
1. 通用模板（混合 0/1 + 可分配资源）：把“只能取 0/满额”的任务做 0/1 背包，枚举离散资源消耗 j，再把剩余资源按单位收益从高到低做可分配贪心。
2. 适用特征：资源总量 m 较小；一部分任务只能全选/不选，另一部分可以按比例分配收益。
3. 正确性直觉：0/1 部分用背包保证离散选择最优；可分配部分满足分数背包条件，按收益密度贪心最优；枚举 j 覆盖所有可行资源拆分。
4. 复杂度：设普通任务数 n1、灵活任务数 n0，背包 O(n1*m)；每个 j 线性贪心 O(n0)，总 O(n1*m + m*n0)，空间 O(m)。
5. 通用易错点：普通任务的 a_i 是整数杯数，背包用 int；灵活任务排序要按 b_i/a_i 递减；浮点输出保留足够精度。
6. 本题差异：灵活任务允许 0..a_i 的实数杯数，收益线性，因此可用分数背包贪心。
7. 本题特化：先对灵活任务按 a_i/b_i 升序（等价于 b_i/a_i 降序）排序；使用 emplace_back 处理自定义的结构体要写个构造函数。
*/