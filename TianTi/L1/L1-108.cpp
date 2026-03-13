#include<bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    cin >> N;
    
    // 方法1：位运算（推荐）
    // 不断右移直到只剩最高位
    while ((N & (N - 1)) != 0) {
        N = N & (N - 1);  // 清除最低位的1
    }
    cout << N << endl;
    
    return 0;
}

/*
 * 方法2：用 1LL << i（更稳妥的幂运算）
 * 
 * int main() {
 *     long long N;
 *     cin >> N;
 *     long long ans = 1;
 *     while (ans * 2 <= N) {
 *         ans *= 2;
 *     }
 *     cout << ans << endl;
 *     return 0;
 * }
 */

/*
 * 方法3：log2 + pow（需要处理精度） 1LL << k  ≡  2^k
 * 
 * int main() {
 *     long long N;
 *     cin >> N;
 *     int k = (int)log2(N);
 *     cout << (1LL << k) << endl;  // 注意用 1LL
 *     return 0;
 * }
 */

/*
 * ==================== 本题知识点 ====================
 * 
 * 【题目本质】找小于等于 N 的最大的 2 的幂
 * 
 * 2 的幂特点：二进制只有一个 1
 * 1 = 1
 * 2 = 10
 * 4 = 100
 * 8 = 1000
 * ...
 * 
 * 【方法1：位运算】
 * N & (N - 1) 清除最低位的 1
 * 不断执行直到只剩一个 1
 * 
 * 【方法2：倍增】
 * 从 1 开始不断乘 2，直到超过 N
 * 
 * 【方法3：log2】
 * k = log2(N) 得到最高位的位置
 * 答案 = 2^k = 1 << k
 * 注意：用 1LL << k 防止溢出
 * 
 * 【常见坑】
 * 1. pow() 返回 double，有精度问题
 * 2. 1 << 31 可能溢出，用 1LL << 31
 * 3. N 最大 10^9，int 够用，但 long long 更安全
 */
