#include<bits/stdc++.h>
using namespace std;

//int main() {
//	int k;  cin>>k;
//	while(k--) {
//		double x,y,z;
//		cin>>x>>y>>z;
//		double ans = (z-x)/y * 10.0;
//		// 转换时加上 1e-9 修正二进制带来的负向误差
//		int dd = (int)(ans + 1e-9);
//		double ff = (ans - (double)dd)* 10.0;
//		int ddf = (int)(ff + 1e-9);
//		cout<<dd+1<<" "<<ddf+1<<"\n";
//	}
//	return 0;
//}

int main() {
	int k;  cin>>k;
	while(k--) {
		int x,y,z;
		cin>>x>>y>>z;
		int v = 100 * (z - x) / y; // 因为y是100因子，所以一定是整数
		int row = v / 10 + 1; 
		int col = v % 10 + 1; // 个位数
		cout<<row<<" "<<col<<"\n";
	}
	return 0;
}
