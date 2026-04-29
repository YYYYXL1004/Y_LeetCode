#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, k;  cin>>n>>k;
	while(k--) {
		int x,y;  cin>>x>>y;
		string s;  cin>>s;
		for(int i = 0; i < s.size(); i++) {
			if(s[i] == 'f') {
				if(y+1 <= n) y++; 
			} else if(s[i] == 'b') {
				if(y-1 >= 1) y--;
			} else if(s[i] == 'l') {
				if(x-1 >= 1) x--;
			} else if(s[i] == 'r') {
				if(x+1 <= n) x++;
			}
		}
		cout<<x<<" "<<y<<"\n";
	}
	return 0;
}
