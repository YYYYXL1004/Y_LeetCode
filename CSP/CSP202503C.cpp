#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll P = 1e9+7;
struct node{
	int ty = 0;  // 1：直接，2：间接
	ll len = 0;      // ty == 1时的长度
	vector<string> v;  // ty == 2
};

unordered_map<string, node> mp;

// 记忆化搜索
ll dfs(string s, unordered_map<string, ll>& memo) {
	if(memo.count(s)) return memo[s];
	if(!mp.count(s)) return 0;
	if(mp[s].ty == 1) return mp[s].len;
	
	ll res = 0;
	for(auto& t : mp[s].v) {
		if(t[0] == '$') res = (res + dfs(t.substr(1), memo)) % P;
		else res = (res + t.length()) % P;
	}
	memo[s] = res;
	return res;
}

int main() {
	ios::sync_with_stdio(false);  cin.tie(0);
	int n;  cin>>n;
	while(n--) {
		int op; string name;
		cin>>op>>name;
		if(op == 3) {
			unordered_map<string, ll> memo;
			cout<<dfs(name, memo) <<"\n";
		} else{
			string s, word;
			getline(cin, s);
			stringstream ss(s);
			vector<string> vv;
			while(ss>>word) {
				vv.push_back(word);
			}
			if(op == 1) {
				unordered_map<string, ll> memo;
				ll res = 0;
				for(auto& t : vv) {
					if(t[0] == '$') res = (res + dfs(t.substr(1), memo)) % P;
					else res = (res + t.length()) % P;
				}
				mp[name] = {1, res, {}};
			} else {
				mp[name] = {2, 0, vv};
			}
		} 
	}
	return 0;
}


// 方法一：暴力模拟40分
//const int P = 1e9+7;
//unordered_map<string, string> mp;
//
//string f(string s) {
//	string word, ans = "";
//	stringstream ss(s);
//	while(ss >> word) {
//		if(word[0] == '$') {
//			string sub = word.substr(1);
//			if(mp.count(sub)) {
//				ans += mp[sub];
//			}
//		} else {
//			ans += word;
//		}
//	}
//	return ans;
//}
//
//int main() {
//	int n;  cin>>n;
//	while(n--) {
//		int op;  cin>>op;
//		if(op == 1) {
//			string a, b, aa;
//			cin>>a;getchar();
//			getline(cin, b);
//			aa = f(b);
//			mp[a] = aa;
//		} else if(op == 2) {
//			string a, b, aa;
//			cin>>a;  getchar();
//			getline(cin, b);
//		} else {
//			string a;  cin>>a;
//			if(mp.count(a)) {
//				cout<<mp[a].length() % P<<"\n";
//			} else {
//				cout<<0<<"\n";
//			}
//		}
//	}
//	return 0;
//}
