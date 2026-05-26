#include<bits/stdc++.h>
using namespace std;

int b,c,l,r;
long long f(int x) {
	return x*x + b*x + c;
}

int main() {
	cin>>b>>c>>l>>r;
	long long sum = 0;
	for(int i = l; i <= r; i++) {
		if(i%2 == 0) {
			sum += 2 * f(i);
		}
	}
	cout<<sum;
	return 0;
}