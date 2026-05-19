#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<#x<<" "<<x<<"\n"

struct drop{
	int x;
	mutable int w;   // mutable允许 set的 const迭代器修改这个非键值 
	bool operator<(const drop& other) const{
		return x < other.x;
	}
};

int main() {
	int c, m, n;  cin>>c>>m>>n;
	set<drop> s;
	for(int i = 0; i < m; i++) {
		int x, w;  cin>>x>>w;
		s.insert({x, w});
	}
	// 优先队列，维护最左边的先爆炸	
	priority_queue<int, vector<int>, greater<int>> pq;
	
	while(n--) {
		int p;  cin>>p;
		auto it = s.find({p,0}); // 按照p找
		if(it != s.end()) {
			it->w++;
			if(it->w == 5) {
				pq.push(p);
			}
		}
		
		while(!pq.empty()) {
			int cur = pq.top();
			pq.pop();
			auto cur_it = s.find({cur, 0});
			if(cur_it == s.end() || cur_it->w < 5) continue;
			
			auto left = cur_it, right = cur_it;
			bool has_left = (cur_it != s.begin());
			if(has_left) {
				left = prev(cur_it);
			}
			right = next(cur_it);
			bool has_right = (right != s.end());
			
			s.erase(cur_it); // 爆开
			
			if(has_left) {
				left->w++;
				if(left->w == 5) pq.push(left->x);
			}
			if(has_right) {
				right->w++;
				if(right->w == 5) pq.push(right->x);
			}
		}
		cout<<s.size()<<"\n";
	}
	return 0;
}



// 方法二：暴力（40/100）
//int c, m, n;
//vector<int> v;
//
//// v[p] >= 5
//void solve(int p) {
//	v[p] = 0;
//	m--;
//	int l = p, r = p;
//	while(l--) {
//		if(l == 0) break;
//		if(v[l] > 0) {
//			v[l]++;
//			break;
//		}
//	}
//	while(r++) {
//		if(r == c + 1) break;
//		if(v[r] > 0) {
//			v[r]++;
//			break;
//		}
//	}
//	if(l != 0 && v[l] >= 5) solve(l);
//	if(r != c+1 && v[r] >= 5) solve(r);
//}
//
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin>>c>>m>>n;
//	v.resize(c+1, 0);
//	for(int i = 0; i < m; i++) {
//		int x, w;  cin>>x>>w;
//		v[x] = w;
//	}
//	while(n--) {
//		int p;  cin>>p;
//		v[p]++;
//		if(v[p] < 5) {
//			cout<<m<<"\n";
//		} else {
//			solve(p);
//			cout<<m<<"\n";
//		}
//	}
//	return 0;
//}