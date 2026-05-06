#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int T, M;  cin>>T>>M;
	vector<int> t(M+1);
	vector<int> v(M+1);
	for(int i = 1; i <= M; i++) cin>>t[i]>>v[i];
	vector<ll> dp(T+1);
	for(int i = 1; i <= M; i++) {
		// 完全背包是正向遍历
		for(int j = t[i]; j <= T; j++) {
			// 这里用到的dp[j-t[i]] 是已经被当前物品i更新过的数据
			dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
		}
	}
	cout<<dp[T];
	return 0;
}