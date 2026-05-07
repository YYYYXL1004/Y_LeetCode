#include<bits/stdc++.h>
using namespace std;

int main() {
	int N, V; cin>>N>>V;
	vector<int> w(N);
	vector<int> v(N);
	for(int i = 0; i < N; i++) {
		cin>>w[i]>>v[i];
	}
	vector<int> dp(V+1, 0);
	for(int i = 0; i < N; i++) {
		for(int j = V; j >= w[i]; j--) {
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
	}
	cout<<dp[V];
	return 0;
}