#include<bits/stdc++.h>
using namespace std;

int main() {
	int T, M;  cin>>T>>M;
	vector<int> t(M+1); // 初始化M+1,添加一个虚拟层
	vector<int> v(M+1);
	for(int i = 1; i <= M; i++) {
		cin>>t[i]>>v[i];
	}
	vector<int> dp(T+1, 0);
	for(int i = 1; i <= M; i++) {
		for(int j = T; j >= t[i]; j--) {
			// 一维dp要逆向遍历，避免覆盖
			// 并且循环到t[i]，就可以停止，因为时间小于t[i]的装不下当前草药，不用更新
			dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
		}
	}
	cout<<dp[T];
	// 方法二：二维数组
//	// dp[i][j] 表示前 i 个草药，在 j 时间内能采到的最大价值
//	// 初始化为0，因为什么都不采价值就是0
//	// dp[i][j] = max(dp[i-1][j], dp[i-1][j - t[i]] + v[i])
//	vector<vector<int>> dp(M+1, vector<int>(T+1, 0));
//	for(int i = 1; i <= M; i++) {
//		for(int j = 0; j <= T; j++) {
//			if(j < t[i]) {
//				// 当前剩余时间根本不够采第 i 株草药，只能选择不采
//				dp[i][j] = dp[i-1][j];
//			} else {
//				dp[i][j] = max(dp[i-1][j], dp[i-1][j - t[i]] + v[i]);
//			}
//		}
//	}
//	cout<<dp[M][T];
	return 0;
}