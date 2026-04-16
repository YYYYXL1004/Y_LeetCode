/*
L3-002 特殊堆栈
分数 30
作者 陈越
单位 浙江大学

堆栈是一种经典的后进先出的线性结构，相关的操作主要有“入栈”（在堆栈顶插入一个元素）和“出栈”（将栈顶元素返回并从堆栈中删除）。
本题要求你实现另一个附加的操作：“取中值”——即返回所有堆栈中元素键值的中值。
给定 N 个元素，如果 N 是偶数，则中值定义为第 N/2 小元；若是奇数，则为第 (N+1)/2 小元。

输入格式：
输入的第一行是正整数 N（<=10^5）。随后 N 行，每行给出一句指令，为以下 3 种之一：

Push key
Pop
PeekMedian

其中 key 是不超过 10^5 的正整数；Push 表示“入栈”；Pop 表示“出栈”；PeekMedian 表示“取中值”。

输出格式：
对每个 Push 操作，将 key 插入堆栈，无需输出；
对每个 Pop 或 PeekMedian 操作，在一行中输出相应的返回值。若操作非法，则对应输出 Invalid。

输入样例：
17
Pop
PeekMedian
Push 3
PeekMedian
Push 2
PeekMedian
Push 1
PeekMedian
Pop
Pop
Push 5
Push 4
PeekMedian
Pop
Pop
Pop
Pop

输出样例：
Invalid
Invalid
3
2
2
1
2
4
4
5
3
Invalid
*/

#if 0
// 原暴力解（17/30）
#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	stack<int> s;
	vector<int> v;
	v.push_back(-1);
	int N;  cin>>N;
	while(N--) {
		string str;  cin>>str;
		if(str == "Pop") {
			if(s.empty()) {
				cout<<"Invalid"<<"\n";
			} else {
				auto it = find(v.begin(), v.end(), s.top());
				v.erase(it);
				cout<<s.top()<<"\n";
				s.pop();
			}
		} else if(str == "PeekMedian") {
				if(s.empty()) {
				cout<<"Invalid"<<"\n";
			} else {
				sort(v.begin()+1, v.end());
				int sz = v.size() - 1;
				if(sz % 2 == 0) {
					cout<<v[sz/2]<<"\n";
				} else {
					cout<<v[(sz+1)/ 2]<<"\n";
				}
			}
		} else {
			int x;  cin>>x;
			s.push(x);
			v.push_back(x);
		}
	}
	return 0;
}
#endif

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
int tree[MAXN];

// 获取最低位1
int lowbit(int x) {
    return x & (-x);
}
// 单点更新，将值域包括x的tree[] 数字频次+val
void update(int x, int val) {
    for(int i = x; i < MAXN; i+=lowbit(i)) {
        tree[i] += val;
    }
}
// 区间查询，统计当前集合中 <= x的数字个数
int query(int x) {
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i)) {
        sum += tree[i];
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    stack<int> s;
    int N;  cin>>N;
    while(N--) {
        string str;  cin>>str;
        if(str == "Pop") {
            if(s.empty()) {
                cout<<"Invalid"<<"\n";
            } else {
                update(s.top(), -1);
                cout<<s.top()<<"\n";
                s.pop();
            }
        } else if(str == "PeekMedian") {
                if(s.empty()) {
                cout<<"Invalid"<<"\n";
            } else {
                int k = (s.size() + 1) / 2; // 奇偶通用求中点下标（1-based）
                int l = 1, r = MAXN;
                while(l <= r) {
                    int mid = l + (r - l) /2;
                    if(query(mid) < k) {
                        l = mid + 1;
                    } else if(query(mid) >= k) {
                        r = mid - 1;
                    }
                }
                cout<<l<<"\n";
            }
        } else {
            int x;  cin>>x;
            s.push(x);
            update(x, 1);
        }
    }
    return 0;
}

// 【总结】
// 题型通用模板：
// 1. 当题目是“栈操作 + 动态第 k 小”时，可用“栈 + 频次数组结构”拆分维护。
// 2. 栈负责顺序语义（Push/Pop），树状数组负责值域频次统计。
// 3. 第 k 小通过“前缀个数 >= k”的最小下标查找得到。
// 4. 复杂度：Push/Pop 为 O(logV)，PeekMedian 为 O(logV * logV)（二分 + 前缀查询）。
//
// 本题差异化补充：
// 1. key 范围不超过 1e5，适合直接开值域树状数组。
// 2. 中值下标统一用 k = (size + 1) / 2，覆盖奇偶两种情况。
// 3. 相比暴力排序，正解把多次查询从高代价重排降到对数级，能通过满分数据。
