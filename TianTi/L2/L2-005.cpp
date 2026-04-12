/*
L2-005 集合相似度
分数 25
作者 陈越
单位 浙江大学

给定两个整数集合，它们的相似度定义为：Nc / Nt x 100%。
其中 Nc 是两个集合都有的不相等整数的个数，Nt 是两个集合一共有的不相等整数的个数。
你的任务就是计算任意一对给定集合的相似度。

输入格式：
输入第一行给出一个正整数 N（<=50），是集合的个数。随后 N 行，每行对应一个集合。
每个集合首先给出一个正整数 M（<=10^4），是集合中元素的个数；然后跟 M 个 [0,10^9] 区间内的整数。

之后一行给出一个正整数 K（<=2000），随后 K 行，每行对应一对需要计算相似度的集合的编号（集合从 1 到 N 编号）。
数字间以空格分隔。

输出格式：
对每一对需要计算的集合，在一行中输出它们的相似度，为保留小数点后 2 位的百分比数字。

输入样例：
3
3 99 87 101
4 87 101 5 87
7 99 101 18 5 135 18 99
2
1 2
1 3

输出样例：
50.00%
33.33%
*/

#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<#x<<" "<<x<<"\n"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int N,M,K;  cin>>N;
	vector<set<int>> v(N+1);
	for(int i = 1; i <= N; i++) {
		cin>>M;
		int x;
		while(M--) {
			cin>>x;
			v[i].insert(x);
		}
	}
	cin>>K;
	while(K--) {
		int x, y;  cin>>x>>y;
		// 方法一：直接使用库函数 set_intersection,set_union构造交并集，会超时一个测试点（21/25）
		
		// set<int> inters, uni;
		// // 交集，同时在x和y中出现
		// set_intersection(v[x].begin(), v[x].end(), v[y].begin(), v[y].end(), inserter(inters, inters.begin()));
		// // 并集，在x或y中出现
		// set_union(v[x].begin(), v[x].end(), v[y].begin(), v[y].end(), inserter(uni, uni.begin()));
		// int nc = inters.size(), nt = uni.size();
		
		// 方法二：双指针直接计算2个set的交并集大小，不用构造（更快）
		int nc = 0; // 记录相等数目
		auto i = v[x].begin(), j = v[y].begin();
		while(i != v[x].end() && j != v[y].end()) {
			if(*i < *j) i++;
			else if(*i > *j) j++;
			else {
				i++;
				j++;
				nc++;
			}
		}
		int nt = (int)v[x].size() + (int)v[y].size() - nc; // 记录并集数目
		double ans = (double)nc / (double)nt * 100.0;
		printf("%.2lf%%\n", ans);
	}
	return 0;
}

// 【总结】
// 1) 题型通用模板（两个有序集合统计交并）
// - 适用特征：给两个集合（或去重后的有序序列），要交集大小/并集大小/相似度。
// - 标准框架：双指针同时扫，谁小谁前进；相等时交集计数 +1 并同时前进。
// - 并集大小公式：|A U B| = |A| + |B| - |A n B|。
// - 复杂度：每次查询 O(|A|+|B|)，额外空间 O(1)。
// - 通用易错点：并集不能直接相加；输出百分号要用 %%；保留两位小数。
//
// 2) 本题差异化补充
// - 每个集合输入可能有重复数字，先放进 set 自动去重，保证后续比较正确。
// - 若用库函数构造交并集容器，常数较大；本题只要大小，直接计数更快。
// - 查询次数 K 最多 2000，避免重复构造容器是通过本题的关键优化点。
