#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 200005;

long long fact[MAXN]; //记录阶乘
long long invFact[MAXN]; //记录阶乘的逆元

// 快速幂 求a^b % mod
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while(b > 0) {
        if(b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
// 预处理阶乘和阶乘逆元，O(N)复杂度
void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    // 费马小定理求最大阶乘的逆元
    invFact[MAXN - 1] = qpow(fact[MAXN - 1], MOD - 2);
    // 倒推求其他阶乘的逆元: 1/(i-1)! = i * 1/i!
    for(int i = MAXN - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}
// O(1) 查询组合数
long long C(int n, int m) {
    if(m < 0 || m > n) return 0;
    // 公式: n! * inv(m!) * inv((n-m)!) % MOD
    return fact[n] * invFact[m] % MOD * invFact[n - m] % MOD;
}
int main() {
    init();
    cout<<C(100, 50) << endl;
    return 0;
}