/*
 * @lc app=leetcode.cn id=204 lang=cpp
 * @lcpr version=30307
 *
 * [204] 计数质数
 */

// @lc code=start
class Solution {
public:
    int countPrimes(int n) {
        // 方法一：埃拉托斯特尼筛（埃氏筛） O(n log log n)
        // 对每个质数 p，标记其所有倍数 p², p²+p, p²+2p... 为合数
        // 缺点：一个合数可能被标记多次（比如30 会被 2, 3, 5各标记一次

        // vector<bool> isPrime(n ,true);
        // for(int i = 2; i * i < n; i++) {
        //     if(isPrime[i]) {
                // 关键优化：从 i*i 开始标记，因为 i*2, i*3...i*(i-1) 已经被更小的质数标记过
        //         for(int j = i * i; j < n; j += i) {
        //             isPrime[j] = false;
        //         }
        //     }
        // }

        // int count = 0;
        // for(int i = 2; i < n; i++) {
        //     if(isPrime[i]) count++;
        // }
        // return count;

        // 方法二：欧拉筛（线性筛）O(n)
        // 每个合数只被其最小质因子筛掉一次

        if(n <= 2) return 0;
        vector<bool> isPrime(n, true);
        vector<int> primes;
        for(int i = 2; i < n; i++) {
            if(isPrime[i]) primes.push_back(i);

            // 核心：用当前数 i 和已知的质数相乘， 标记合数
            // 每个合数只会被他的最小质因子筛掉一次
            // for(int j = 0; j < primes.size() && primes[j] * i < n; j++) {
            //     isPrime[primes[j] * i] = false;
            //     // 重要：当 i % primes[j] == 0 时停止
            //     // 此时 primes[j] 是 i 的最小质因子
            //     // 继续循环会导致用更大的质因子标记，违反"每个合数只被最小质因子筛一次"的原则
            //     // 例如：i=6, primes[j]=2 时，6%2==0，停止。避免用 3*6=18 标记（18 应该由 2*9 标记）
            //     if(i % primes[j] == 0) break; 
            // }
            // 推荐这种写法，更简洁
            for(int p : primes) {
                if(p * i >= n) break;
                isPrime[p * i] = false;
                if(i % p == 0) break;
            }
        }
        return primes.size();
    }
};
// @lc code=end



/*
// @lcpr case=start
// 10\n
// @lcpr case=end

// @lcpr case=start
// 0\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

