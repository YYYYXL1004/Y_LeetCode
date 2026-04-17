#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dist[202][202];
int times[202];

int main() {
	int N, M;  cin>>N>>M;
	for(int i = 0; i < N; i++) {
		for(int j = 0 ; j < N; j++) {
			if(i == j) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}
	for(int i = 0; i < N; i++) cin>>times[i];
	while(M--) {
		int i, j, w;  cin>>i>>j>>w;
		dist[i][j] = w;
		dist[j][i] = w;
	}
	int k = 0; // 记录当前已经修好了几个村庄
	int Q;  cin>>Q;
	while(Q--) {
		int x, y, t;  cin>>x>>y>>t;
		// floyd
		while(k < N && times[k] <= t) {
			for(int i = 0; i < N; i++) {
				if(dist[i][k] == INF) continue;
				for(int j = 0; j < N; j++) {
					if(dist[i][j] > dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
			k++; // 这个村庄投入使用，准备看下一个村庄
		}
		if(dist[x][y] == INF || times[x] > t || times[y] > t) cout<<-1<<"\n";
		else cout<<dist[x][y]<<"\n";
	}
	return 0;
}