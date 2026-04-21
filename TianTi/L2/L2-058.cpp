/*
L2-058 超参数搜索
分数 25
作者 陈越
单位 浙江大学

神经网络模型的超参数是训练前需预先设定的参数，直接影响模型性能。在机器学习过程中需要对超参数进行优化，
给学习器选择一组最优超参数，以提高学习的性能和效果。假设我们记录了一系列不同参数组合在验证集上的性能得分
（如准确率），本题要求：

1) 找出性能得分最高的参数组合编号（按升序输出）。
2) 对每个查询目标性能得分 x，从所有性能得分严格大于 x 的参数组合中，找到得分最小的那一组；
   若该得分对应多个组合，输出编号最小者；若不存在，输出 0。

输入格式：
输入第一行给出正整数 n（1 < n <= 10^5），为参数组合总量。
第二行给出 n 个区间 [0, 10^8] 内的整数，第 i 个数字表示编号为 i 的参数组合性能得分。
随后一行给出正整数 m（<= n/2），为查询次数。
接下来 m 行，每行给出一个查询目标性能得分 x（x 也在 [0, 10^8] 内）。

输出格式：
首先第一行按升序列出所有性能得分最高的参数组合编号，数字间以 1 个空格分隔。
随后每个查询输出一行结果编号；若不存在满足条件的组合，输出 0。

输入样例：
10
87 91 65 72 95 84 77 95 91 85
3
87
75
95

输出样例：
5 8
2
7
0

说明：你给的两份代码与样例都对应“严格大于 x（> x）”的查询语义。
*/

#if 0
// 题解一（暴力 18/25)：
#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;  cin>>n;
	vector<int> v(n+1);
	int maxn = 0;
	for(int i = 1; i <= n; i++) {
		cin>>v[i];
		maxn = max(maxn, v[i]);
	}
	bool first = true;
	for(int i = 1; i <= n; i++) {
		if(v[i] == maxn) {
			if(first) {
				cout<<i;
				first = false;
			}
			else cout<<" "<<i;
		}
	}
	cout<<'\n';
	int m;  cin>>m;
	vector<int> tmp = v;
	sort(tmp.begin()+1, tmp.end());
	while(m--) {
		int x;  cin>>x;
		if(x >= maxn) {
			cout<<"0\n";
			continue;
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			if(tmp[i] > x) {
				ans = tmp[i];
				break;
			}
		}
		for(int i = 1; i <= n; i++) {
			if(ans == v[i]) {
				cout<<i<<"\n";
				break;
			}
		}
	}
	return 0;
}
#endif

#include<bits/stdc++.h>
using namespace std;

// 题解二（正解）：保留原实现
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;  cin>>n;
	vector<int> v(n+1);
	map<int, int> mp;
	int maxn = 0;
	for(int i = 1; i <= n; i++) {
		cin>>v[i];
		maxn = max(maxn, v[i]);
		// map::insert 天然不覆盖已存在的键
		// 这样就保证了同一个分数，记录的永远是第一次出现的那个最小编号
		mp.insert({v[i], i});
	}
	bool first = true;
	for(int i = 1; i <= n; i++) {
		if(v[i] == maxn) {
			if(first) {
				cout<<i;
				first = false;
			}
			else cout<<" "<<i;
		}
	}
	cout<<'\n';
	int m;  cin>>m;
	while(m--) {
		int x;  cin>>x;
		auto it = mp.upper_bound(x);
		if(it == mp.end()) {
			cout<<"0\n";
		} else {
			cout<<it->second<<"\n";
		}
	}
	return 0;
}

// 【总结】
// 1) 题型通用模板（有序阈值查询）：
//    - 先把“值 -> 最早出现位置”建立成有序结构（map / 排序数组 + 二分）。
//    - 查询时用 upper_bound(x) 找到第一个 > x 的值，即“满足条件的最小值”。
//    - 若该值有多次出现，预处理阶段只保留最小编号即可。
//    - 复杂度通常是 O(n log n + m log n)。
//
// 2) 本题差异化要点：
//    - 需要先单独输出“全局最大分数”的所有编号（按原编号升序遍历即可天然有序）。
//    - 查询语义按样例是严格大于 x，不是大于等于 x。
//    - map.insert 不覆盖已有键，正好保证同分时保留最小编号。
//
// 3) 易错点：
//    - 把 > x 写成 >= x 会与样例不符。
//    - 同分时若用赋值覆盖，会丢失最小编号答案。
//    - 最大值行与每次查询输出是两段独立逻辑，不要混在一起判断。
