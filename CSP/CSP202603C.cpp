/*
题目背景
西西艾弗岛操作系统有动态链接接口与对外广播功能，需要模拟其内存与对象传输行为。

初始建构
有一段容量为 10^100 的全局内存，地址从 0 开始。每个字节有两种状态：
e_i 表示是否被占用，x_i 表示是否存储对象，初始均为 0。
系统中有 n 个进程，初始均未对接任何接口。

操作定义
new p L：为进程 p 新建接口与队列（容量 L）。分配器按最优适应原则在空闲段中
选择长度 >= L 且最短的段（若有多段取左端点最小），将 [l, l+L-1] 分配给队列。
输出该队列起始地址 l。

send p：进程 p 向其所有接口各发送一个对象。对每个队列区间 [a,b]：
若之前从未发送过，则存入 a；否则上次存入位置为 t，若 t<b 存入 t+1，否则存入 a。
输出本次所有新发送对象地址之和。

delete p i：删除进程 p 的第 i 个接口及队列，释放区间 [a,b]（e/x 置 0）。
进程 p 编号大于 i 的接口编号减 1，队列与地址不变。该操作无输出。

题目描述
给定 q 个操作，按顺序模拟并按要求输出每次 new 与 send 的结果。

输入格式
第一行 n q。
接下来 q 行为操作，格式为 new p L / send p / delete p i。

输出格式
对每个 new 与 send 操作输出一行一个整数。

输入数据 1
2 13
new 1 2
new 1 3
send 1
delete 1 1
new 1 4
send 1
new 2 3
send 2
delete 1 2
new 1 3
send 1
delete 1 1
send 1

输出数据 1
0
2
2
5
8
9
9
5
9
6

样例 1 解释
每次新建的起始地址依次为 0,2,5,9,5；
每次发送的新对象地址和依次为 2,8,9,9,6。

数据范围
保证操作有意义。1<=n<=100, 1<=q<=8000, 1<=L_m<=5*10^5，
除操作名称外所有输入为非负整数。
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 2e18; 

struct Q{
	ll st, len, cnt;  // 队列起始地址st, 长度len, 第cnt次发送
	// pos = st + (cnt mod len)  这是send cnt次的队列头
};

vector<Q> p[105]; // p[i]存储进程 i 的队列
//  两个集合内的空闲块是对应的，数量一定相等
set<pair<ll, ll>> s_len;  // 维护空闲块 {长度，起始地址} 按长度排序
set<pair<ll, ll>> s_pos;  // 维护空闲块 {起始地址，长度} 按起始地址排序

int main() {
	int n, q;  cin>>n>>q;
	// 初始化一个无限大内存
	s_len.insert({INF, 0});
	s_pos.insert({0, INF});
	while(q--) {
		string op;  cin>>op;
		if(op == "new") {
			int id; ll l;
			cin>>id>>l;
			auto it = s_len.lower_bound({l, -1});
			ll cur_len = it->first, cur_st = it->second;
			s_len.erase(it);  s_pos.erase({cur_st, cur_len}); // 移除两个空闲块
			if(cur_len > l) { // 把剩下的空闲块添加
				s_len.insert({cur_len - l, cur_st + l});
				s_pos.insert({cur_st + l, cur_len - l});
			}
			p[id].push_back({cur_st, l, 0});
			cout<<cur_st<<"\n";
		} else if(op == "send") {
			int id;   cin>>id;
			ll sum = 0;
			for(auto& cur : p[id]) {  // 注意，这里不要加const，因为要修改p[id]里的cnt
				int pos = cur.st + (cur.cnt % cur.len); // 本次需要添加的地址
				cur.cnt++;
				sum += pos;
			}
			cout<<sum<<"\n";
		} else if(op == "delete") {
			int id, idx;  cin>>id>>idx;
			idx--; // 题目是1-based 转成 0-based
			
			ll st = p[id][idx].st, len = p[id][idx].len;
			p[id].erase(p[id].begin()+idx); // 移除
			ll new_st = st, new_len = len; 
			// 检查右合并
			auto it = s_pos.lower_bound({st, -1});
			if(it != s_pos.end() && it->first == st + len) {
				new_len = len + it->second; // 新长度
				s_len.erase({it->second, it->first});
				it = s_pos.erase(it);  // 删除并拿到下一个元素迭代器
			}
			// 检查左合并
			it = s_pos.lower_bound({st, -1});
			if(it != s_pos.begin()) {
				--it;  // 退一格找左侧相邻
				if(it->first + it->second == st) {
					new_st = it->first;
					new_len += it->second;
					s_len.erase({it->second, it->first});
					it = s_pos.erase(it);
				}
			}
			// 合并完成，插入
			s_len.insert({new_len, new_st});
			s_pos.insert({new_st, new_len});
		}
	}
	return 0;
}



// 40分题解  不加delete操作
//int main() {
//	int n, q;  cin>>n>>q;
//	vector<deque<queue<int>>> v(n+1);
//	int idx = 0; // 全局索引
//	while(q--) {
//		string op; cin>>op;
//		if(op == "new") {
//			int p, l;  cin>>p>>l;
//			queue<int> qq;
//			cout<<idx<<"\n";
//			for(int i = 0 ; i < l; i++) {
//				qq.push(idx);
//				idx++;
//			}
//			v[p].push_back(qq);
//		} else if(op == "send") {
//			int p;  cin>>p;
//			int sum = 0;
//			for(int i = 0; i < v[p].size(); i++) {
//				int cur = v[p][i].front();
//				sum += cur;
//				v[p][i].pop();
//				v[p][i].push(cur);
//			}
//			cout<<sum<<"\n";
//		}
//	}
//	return 0;
//}

/*
【总结】
1. 通用模板（内存分配模拟）：用有序集合维护空闲段，new 时做 best-fit 取最短可用段并拆分，delete 时按起点找相邻段并合并。
2. 适用特征：动态分配/释放、需要最优适应策略，且空闲段需要快速查找与合并。
3. 标准框架：维护两套集合（按长度、按起点）；new 用长度集 lower_bound，delete 用起点集检查左右相邻；send 线性遍历接口队列。
4. 复杂度结论：new/delete 为 O(log B)，B 为空闲段数；send 为 O(k)（k 为进程接口数），总复杂度 O(q log B + 总发送遍历)。
5. 通用易错点：best-fit 的长度优先与左端点次序；合并时要同步更新两集合；地址与长度要用 long long。
6. 本题差异：内存容量极大但只需维护空闲段；send 是环形写入，允许覆盖旧对象。
7. 本题特化：记录队列起点/长度/发送次数，位置用 st + (cnt % len) 计算；delete 后接口编号重排但队列地址不变。
*/