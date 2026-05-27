/*
 * 题目: 道具摆放 (蓝桥杯 21264)
 * 链接: https://www.lanqiao.cn/problems/21264/
 *
 * 题意:
 *   N个道具箱初始为 1..N 的排列，目标排列为 P[1..N]。
 *   每次只能交换相邻两个箱子，每次交换灯光闪烁一次。
 *   灯光每 M 次闪烁切换模式，要求调整恰好在某次切换瞬间完成。
 *   即：交换次数必须是 M 的正整数倍。求最少交换次数，无解输出 -1。
 *
 * 关键分析:
 *   1. 相邻交换将目标排列还原为升序的最少次数 = 排列的逆序对数 inv
 *      (用树状数组 / 归并排序 O(NlogN) 求)
 *   2. 每次交换改变排列奇偶性，故可行交换次数集合 = { s | s >= inv 且 s ≡ inv (mod 2) }
 *   3. 需找最小的 s ∈ 上述集合，满足 M | s
 *
 * 算法:
 *   - BIT 求逆序对数 inv
 *   - X = ceil(inv / M) * M  (最小的 >= inv 的 M 的倍数)
 *   - 若 X 与 inv 同奇偶 → 答案 X
 *   - 否则:
 *       M 为偶数 → 无解 (-1)，因为加 M 不改变 X 的奇偶性
 *       M 为奇数 → 答案 X + M (再走一个周期反转奇偶性)
 *
 * 样例:
 *   [3, 1, 2], M=2 → inv=2, X=2, 同奇偶 → 输出 2
 *   [1, 2, 3], M=3 → inv=0 → 输出 0
 *   [1, 3, 2], M=2 → inv=1, X=2, 奇偶不同且 M 偶 → 输出 -1
 */
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5+5;
int tree[MAXN];

int lowbit(int x) {
	return x & -x;
}

void update(int x, int val) {
	for(int i = x; i < MAXN; i+=lowbit(i)) {
		tree[i] += val;
	}
}

int query(int x) {
	ll s = 0;
	for(int i = x; i > 0; i-=lowbit(i)) {
		s += tree[i];
	} 
	return s;
}

int main() {
	ll n,m;  cin>>n>>m;
	vector<int> a(n+1);
	for(int i = 1; i <= n; i++) {
		cin>>a[i];
	}
	ll ans = 0;
	for(int i = n; i >= 1; i--) {
		ans += query(a[i] - 1);  // 右侧严格小于a[i]的数个数
		update(a[i], 1);   		 // 把当前元素加入到BIT
	}
	if(ans == 0) {
		cout<<0;  return 0;
	}
	ll k = (ans + m - 1) / m; // 向上取整，等价于ceil(ans / m)
	ll X = k * m;
	if((X - ans) % 2 == 0) {
		cout<<X;  // 奇偶性相同，可以通过冗余交换配平
	} else { // 奇偶性不同
		if(m % 2 == 0) cout<<-1;  // m是偶数，怎么加m都改变不了X的奇偶性，无解
		else cout<<X+m; 		  // m是奇数，再向前走一个周期就能反转奇偶性，匹配成功 
	}
	return 0;
}