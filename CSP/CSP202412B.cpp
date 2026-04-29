#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int n;  cin>>n;
	vector<ll> a(n+1);
	vector<ll> b(n+1);
	for(int i = 0; i <= n; i++) {
		cin>>a[i];
	} 
	for(int i = 1; i <= n; i++) {
		cin>>b[i];
	}
	// c数组记录每一步的能量缺口
    vector<ll> c(n + 1, 0);
    c[0] = a[0];
    for(int i = 1; i <= n; i++) {
        c[i] = c[i - 1] + a[i] - b[i];
    }
    // w = max(c_0, c_1, c_2,...,c_n)
    
	// 如果第i个区域补给没了
    // w_i = max(前i-1个缺口最大值， 第i个及缺口之后的最大值+b_i)
    
    // pref数组记录前缀最大值
    vector<ll> pref(n + 1, 0);
    pref[0] = c[0];
    for (int i = 1; i <= n; i++) {
        pref[i] = max(pref[i - 1], c[i]);
    }
    // suff数组记录后缀最大值
    vector<ll> suff(n + 2, 0); // 多开一位防越界
    suff[n] = c[n];
    for (int i = n - 1; i >= 0; i--) {
        suff[i] = max(suff[i + 1], c[i]);
    }
    // 计算每个区域发生意外的情况
    for (int i = 1; i <= n; ++i) {
        ll max_before = pref[i - 1];
        ll max_after = suff[i] + b[i];
        ll ans = max(max_before, max_after);
        cout << ans << (i == n ? "" : " ");
    }
	return 0;
}