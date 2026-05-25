#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> mp;
// memo[x][y] 存储到达 (x, y) 时的最大剩余步数
vector<vector<int>> memo;
int n, cnt = 0;

void dfs(int x, int y, int k) {
	if(x > n || x < 1 || y < 1 || y > n) return ;
	
	// 核心剪枝逻如果当前带过来的剩余步数 k，不比之前记录的优，直接 return 截断
	if (k <= memo[x][y]) return;
	
	memo[x][y] = k; 	// 刷新该格子能达到的最优状态
	if(mp[x][y] == 0) {
		mp[x][y] = 1;
		cnt++;
	}
	if(k > 0) {
		dfs(x-2, y+1, k-1); dfs(x-1, y+2, k-1);
		dfs(x+1, y+2, k-1); dfs(x+2, y+1, k-1);
		dfs(x-2, y-1, k-1); dfs(x-1, y-2, k-1);
		dfs(x+1, y-2, k-1); dfs(x+2, y-1, k-1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int k; cin>>n>>k;
	mp.assign(n+1, vector<int>(n+1, 0));
	memo.assign(n+1, vector<int>(n+1, -1));
	int x, y;  cin>>x>>y;
	dfs(x, y, k);
	cout<<cnt;
	return 0;
}

// 方法一：暴搜dfs 80/100
//#include<bits/stdc++.h>
//using namespace std;
//
//vector<vector<int>> mp;
//int n, cnt = 0;
//
//void dfs(int x, int y, int k) {
//	if(x > n || x < 1 || y < 1 || y > n) return ;
//	if(mp[x][y] == 0) {
//		mp[x][y] = 1;
//		cnt++;
//	}
//	if(k > 0) {
//		dfs(x-2, y+1, k-1); dfs(x-1, y+2, k-1);
//		dfs(x+1, y+2, k-1); dfs(x+2, y+1, k-1);
//		dfs(x-2, y-1, k-1); dfs(x-1, y-2, k-1);
//		dfs(x+1, y-2, k-1); dfs(x+2, y-1, k-1);
//	}
//}
//
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int k; cin>>n>>k;
//	mp.assign(n+1, vector<int>(n+1, 0));
//	int x, y;  cin>>x>>y;
//	dfs(x, y, k);
//	cout<<cnt;
//	return 0;
//}