# CSP 赛前模板速查（打印版）

> 配合 STL 速查表一起带。代码可直接复制粘贴，按需修改。

---

## 零、快读快写 & 常用头

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;  // 两个INF相加不溢出，不要用INT_MAX
const double EPS = 1e-7;     // 浮点数辅助

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // ...
    return 0;
}
```

---

## 一、前缀和 & 差分

### 一维前缀和
```cpp
// 预处理 O(n)，查询 O(1)
// pre[i]是[0..i]的前缀和
vector<ll> pre(n + 1, 0);
for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
// 区间 [l, r] 的和：
ll sum = pre[r] - pre[l - 1];
```

### 二维前缀和
```cpp
// 画 4x4 格子图理解容斥，不要死记公式
vector<vector<ll>> pre(n + 1, vector<ll>(m + 1, 0));
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        pre[i][j] = a[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
//       当前格子 + 上方矩形 + 左方矩形 - 左上重复
// 查询矩形 (x1,y1)-(x2,y2) 的和：
ll sum = pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1];
//         总矩形   - 上方多余  - 左方多余  + 左上多减
```

### 差分数组
```cpp
// diff[i] = a[i] - a[i-1]，即相邻元素的差
// 前缀和还原：a[i] = diff[1] + diff[2] + ... + diff[i]

// 场景：多次"区间 [l, r] 整体加 val"，最后才需要看结果
// 暴力：k 次修改 O(kn)；差分：k 次 O(1) 修改 + 最后一次 O(n) 还原 = O(k+n)

// 对区间 [l, r] 加 val，只需：
diff[l] += val;        // l 开始整体抬高 val
diff[r + 1] -= val;    // r+1 开始抵消，恢复原值
// 例：a = [0,0,0,0,0], 对 [2,4] 加 3
// diff 变为 [0,0,3,0,0,-3]，前缀和还原后 a = [0,0,3,3,3,0]

// 还原：对 diff 求前缀和即得原数组
for (int i = 1; i <= n; i++) a[i] = a[i - 1] + diff[i];
```

### 前缀和 + 哈希表（子数组计数/最值）
```cpp
// 统计和为 k 的子数组个数
// 原理：pre[j]-pre[i]=k 即 [i+1,j] 的和为 k，等价于找之前出现过多少个 pre-k
unordered_map<ll, int> mp;
mp[0] = 1; // 前缀和为 0 出现了 1 次（空前缀，处理从头开始的子数组）
ll pre = 0, cnt = 0;
for (int i = 0; i < n; i++) {
    pre += a[i];
    auto it = mp.find(pre - k);
    if (it != mp.end()) cnt += it->second;
    mp[pre]++;
}
// 变式一：和为 k 的倍数的子数组个数
// mp 改存前缀和 mod k，查找 pre%k 即可
// 注意负数取模：用 ((pre % k) + k) % k，C++ 的 % 结果符号跟被除数
// 变式二：和为 k 的最长子数组长度
// mp 改存每个前缀和首次出现的下标（mp[0]=-1，!mp.count(pre) 时才存，保证存的是最左）
// 变式三：子数组平均数为 k
// 全体元素先减 k（a[i]-=k），问题等价于和为 0 的子数组，直接套模板 k=0
```

---

## 二、树状数组（BIT）

> **必须 1-indexed！** 下标 0 不可用。

### 单点加 + 区间查（基础用法）
```cpp
const int MAXN = 5e5 + 5;
ll tree[MAXN];
// lowbit：取最低位的 1，如 lowbit(12) = lowbit(1100) = 100 = 4
// 决定了树状数组的跳转步长
int lowbit(int x) { return x & (-x); }

// 单点加 val：沿着"管辖范围"逐级向上更新父节点
// x → x+lowbit(x) → ... 直到越界，路径上的节点都包含 x
void update(int x, ll val) {
    for (int i = x; i < MAXN; i += lowbit(i)) tree[i] += val;
}
// 前缀和查询 [1..x]：沿着"管辖范围"逐级向上累加
// x → x-lowbit(x) → ... 直到 0，累加沿途节点
ll query(int x) {
    ll s = 0;
    for (int i = x; i > 0; i -= lowbit(i)) s += tree[i];
    return s;
}
// 区间和 = 前缀和之差
ll rangeSum(int l, int r) { return query(r) - query(l - 1); }
```

### 区间加 + 单点查（维护差分）
```cpp
// 复用同一套 update/query，只是 BIT 里存的是差分数组 diff 而非原数组
// 区间 [l, r] 加 k → 差分上两次单点加：diff[l]+=k, diff[r+1]-=k
update(l, k); update(r + 1, -k);
// 单点查 a[x] → diff 的前缀和 = 原数组值
ll val = query(x);
```

### 区间加 + 区间查（两个 BIT）
```cpp
// 原理：sum(a[1..x]) = (x+1)*Σdiff[i] - Σ(i*diff[i])，拆成两个 BIT 维护
// bit1 维护 diff，bit2 维护 i*diff
ll bit1[MAXN], bit2[MAXN];
void add(ll* bit, int x, ll val) { for (; x < MAXN; x += x & -x) bit[x] += val; }
ll ask(ll* bit, int x) { ll s = 0; for (; x > 0; x -= x & -x) s += bit[x]; return s; }

// 区间 [l, r] 加 k
void rangeAdd(int l, int r, ll k) {
    add(bit1, l, k);     add(bit1, r + 1, -k);
    add(bit2, l, k * l); add(bit2, r + 1, -k * (r + 1));
}
// 前缀和 sum(a[1..x])
ll prefixSum(int x) { return (x + 1) * ask(bit1, x) - ask(bit2, x); }
// 区间和 sum(a[l..r])
ll rangeSum(int l, int r) { return prefixSum(r) - prefixSum(l - 1); }
```

### 逆序对（树状数组 + 离散化）
```cpp
// 从右往左，对每个 a[i] 查询右边有多少个比它小的（query(rank-1)）
// 离散化：值域大（如 10^9）时，映射到 1..m 紧凑名次，BIT 才开得下
// tree 是全局数组，自动零初始化，初始时 BIT 为空（无元素加入）
int n; cin >> n;
vector<int> a(n), b(n);
for (int i = 0; i < n; i++) { cin >> a[i]; b[i] = a[i]; }
// 离散化三部曲：排序、去重、lower_bound 取名次
sort(b.begin(), b.end());
b.erase(unique(b.begin(), b.end()), b.end());
int max_rank = b.size();  // BIT 上界

ll ans = 0;
for (int i = n - 1; i >= 0; i--) {
    int rank = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1; // +1 保证 1-indexed
    ans += query(rank - 1);  // 返回 BIT 中名次在 [1, rank-1] 的元素个数，即值 < a[i] 且在右边的元素个数
    update(rank, 1);         // 把当前元素加入 BIT，tree[rank]表示rank出现的次数
}
cout << ans << "\n";

// 不用离散化：值域本身就是 [1, n] 的排列时，直接用值作下标，省去排序去重
// ll ans = 0;
// for (int i = n - 1; i >= 0; i--) {
//     ans += query(a[i] - 1);
//     update(a[i], 1);
// }
```

---

## 三、并查集

```cpp
int parent[MAXN];  // 初始化：for(int i=0;i<MAXN;i++) parent[i]=i;

// 路径压缩：查找时把沿途节点直接挂到根下，下次查询 O(1)
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}
// _union 命名避免与 C++ 关键字 union 冲突
void _union(int p, int q) {
    int rp = find(p), rq = find(q);
    if (rp == rq) return;  // 已在同一集合
    parent[rq] = rp;       // rq 挂到 rp 下
}
// 使用：_union(u, v);  find(u) == find(v) 判断是否连通
```

### 变式一：按大小合并 + 维护连通分量数
```cpp
int parent[MAXN], sz[MAXN], cnt; // cnt 初始为 n
void init(int n) { for (int i = 0; i <= n; i++) { parent[i] = i; sz[i] = 1; } cnt = n; }
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void _union(int p, int q) {
    int rp = find(p), rq = find(q);
    if (rp == rq) return;
    if (sz[rp] < sz[rq]) swap(rp, rq); // 小树挂大树
    parent[rq] = rp; sz[rp] += sz[rq];
    cnt--;  // 有效合并，连通分量减一
}
```

### 变式二：带权并查集
// 场景：已知若干"相对关系"，推导未知关系或判断矛盾
//   - 食物链：A吃B、B吃C → A和C什么关系？（权值 mod 3）
//   - 判断谎话：甲说乙是好人，乙说甲是坏人 → 谁在说谎？
//   - 带距离的连通：A到B距离3，B到C距离5 → A到C距离8？
// 本质：权值 = 两节点之间的"偏移量"，合并时通过方程推导根节点的新权值
```cpp
// 权值 d[x] = x 到 parent[x] 的距离/偏移量，find 时路径压缩同步更新
int parent[MAXN];
ll d[MAXN];  // 权值
int find(int x) {
    if (parent[x] == x) return x;
    int root = find(parent[x]); // 先递归：让 parent[x] 直接指向 root，同时 d[parent[x]] 已被刷新
    d[x] += d[parent[x]];   // 路径压缩时累加权值：x→root = x→parent + parent→root
    parent[x] = root;       // 路径压缩
    return root;
}
void _union(int p, int q, ll w) {  // p 到 q 的权值为 w
    int rp = find(p), rq = find(q);
    if (rp == rq) return;
    parent[rp] = rq;
    d[rp] = d[q] - d[p] + w;  // 推导：d[p]+w = d[rp]+d[q]，解出 d[rp]
}
// 查询 p 到 q 的权值：必须先 find(p); find(q); 刷新 d[]，再算 d[p]-d[q]
// 不调 find 直接读 d[p]-d[q] 是错的！_union 只更新了根节点，子节点的 d[] 是过期数据
```

### 变式三：扩展域（种类并查集）
// 场景：多种关系（同类/敌人/天敌）并存，"敌人的敌人是朋友"
// 比带权并查集更直观：不用推公式，直接把关系拆成不同域合并
// 食物链问题用扩展域或带权都能做，扩展域更好理解
```cpp
// 把每个点 x 拆成多个域：如 x 表示同类，x+n 表示敌人，x+2n 表示天敌
int parent[MAXN * 3];  // 开 3 倍空间
// 输入"A 和 B 是同类" → 合并 x 与 y，合并 x+n 与 y+n，合并 x+2n 与 y+2n
// 输入"A 吃 B" → 合并 x 与 y+2n，合并 x+n 与 y，合并 x+2n 与 y+n
// 判断矛盾：x 和 y 已在同一集合 → 说明和已知关系矛盾
```

### 变式四：并查集 + map 记敌人（敌人的敌人不一定是朋友）
```cpp
// 场景：朋友关系用并查集维护，敌人关系用 map+set 单独记（如 L2-010 排座位）
// 适用于"敌人的敌人不一定是朋友"，不需要扩展域
int parent[MAXN];
map<int, set<int>> enemy;  // enemy[x] = x 的所有敌人
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void _union(int p, int q) { int rp = find(p), rq = find(q); if (rp != rq) parent[rq] = rp; }
// 输入"p 和 q 是朋友" → _union(p, q)
// 输入"p 和 q 是敌人" → enemy[p].insert(q); enemy[q].insert(p);
// 查询 p 和 q 的关系：
//   find(p)==find(q) → 朋友
//   enemy[find(p)].count(find(q)) → 敌人
//   否则 → 不确定
```

## 四、最短路径

### Dijkstra（堆优化，邻接表）
```cpp
// graph[u] = {{v, w}, ...}  适用于非负权图（不能有负权边！）
// greater<> 让 priority_queue 变成小根堆（距离小的先出）
// 时间复杂度 O((V+E) log V)
vector<ll> dijkstra(vector<vector<pair<int,int>>>& g, int src) {
    int n = g.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        ll d = pq.top().first; int u = pq.top().second; pq.pop();
        // 同一个节点可能被多次 push（不同距离），弹出的是过时记录，跳过
        if (d > dist[u]) continue;  // 剪枝：必须写！否则同一节点重复扩展导致 TLE
        for (auto& e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[v] > d + w) {   // 松弛：发现更短路径
                dist[v] = d + w;
                pq.push({dist[v], v});  // 新距离入堆（旧的不删，靠上面的 continue 跳过）
            }
        }
    }
    return dist;
}
```

### Floyd（全源最短路，邻接矩阵）
```cpp
// k 必须在最外层！表示"经过前 k 个中转点"的最短路
// 初始化 dist[i][i] = 0，其余 INF
for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++) {
        if (dist[i][k] == INF) continue;  // 防 INF+INF 溢出变负数！
        for (int j = 0; j < n; j++)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
```

---

## 五、BFS（网格/图最短步数）

```cpp
// 网格 BFS，四方向（上下左右）
// BFS 天然按层扩展，所以第一次到达终点时的 step 就是最短步数
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(vector<vector<char>>& grid, int sx, int sy) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int,int>> q;
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    q.push({sx, sy}); vis[sx][sy] = true;
    int step = 0;
    while (!q.empty()) {
        int sz = q.size();     // 当前层的节点数
        while (sz--) {         // 逐层扩展，保证 step 就是最短步数
            int x = q.front().first, y = q.front().second; q.pop();
            if (到达终点) return step;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if (vis[nx][ny] || grid[nx][ny] == '#') continue;
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
        step++;
    }
    return -1;
}
```

---

## 六、DFS + 最优性剪枝（记忆化搜索）

> 适合：有限步数/资源内探索所有可达状态，暴力 DFS 超时。

```cpp
// memo[x][y] 记录到达 (x,y) 时剩余资源的历史最大值
// 只有当前剩余资源 k 严格大于历史值才继续搜索，否则剪枝
vector<vector<int>> memo;  // 初始化为 -1

void dfs(int x, int y, int k) {
    if (越界) return;
    if (k <= memo[x][y]) return;  // 剪枝：当前路径不优于历史最优，放弃
    memo[x][y] = k;               // 刷新最优状态，标记此状态已访问
    标记/统计当前格子;
    if (k > 0) {
        for (auto& dir : directions)
            dfs(x + dir.first, y + dir.second, k - 1);
    }
}
```

---

## 七、二分查找

```cpp
// 找满足条件的最小值（左边界）：check(mid)==true 时收缩右端点
int l = 0, r = MAX;
while (l < r) {
    int mid = l + (r - l) / 2;  // 防溢出写法，等价于 (l+r)/2
    if (check(mid)) r = mid;    // mid 满足，答案 <= mid
    else l = mid + 1;           // mid 不满足，答案 > mid
}
// l 即答案

// 找满足条件的最大值（右边界）：check(mid)==true 时收缩左端点
int l = 0, r = MAX;
while (l < r) {
    int mid = l + (r - l + 1) / 2;  // +1 防死循环！当 l+1==r 时 mid=l 而非 r
    if (check(mid)) l = mid;         // mid 满足，答案 >= mid
    else r = mid - 1;                // mid 不满足，答案 < mid
}
// l 即答案
```

---

## 八、动态规划

### 0/1 背包（一维滚动数组）
```cpp
// 物品重量 w[i]，价值 v[i]，容量 C
// 每个物品只能选一次 → 倒序遍历容量，保证 dp[j-w[i]] 还是"上一轮"的值
vector<int> dp(C + 1, 0);
for (int i = 0; i < n; i++)
    for (int j = C; j >= w[i]; j--)  // 倒序！保证每个物品只用一次
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
```

### 完全背包（一维滚动数组）
```cpp
// 每个物品可无限选 → 正序遍历容量，dp[j-w[i]] 可能已经包含了物品 i
vector<int> dp(C + 1, 0);
for (int i = 0; i < n; i++)
    for (int j = w[i]; j <= C; j++)  // 正序！允许重复选取同一物品
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
```

### 最长递增子序列 LIS（O(n log n)）
```cpp
// tail[i] = 长度为 i+1 的递增子序列的最小末尾
// 贪心：尽量让每个长度的末尾尽可能小，为后续元素留更多空间
vector<int> tail;
for (int x : nums) {
    auto it = lower_bound(tail.begin(), tail.end(), x); // 找第一个 >= x 的位置
    if (it == tail.end()) tail.push_back(x);  // x 比所有末尾都大，延长序列
    else *it = x;  // 用 x 替换，保持末尾尽可能小
}
int lis = tail.size();
// 注意：tail 数组本身不一定是合法的 LIS 序列，只保证长度正确
```

### 编辑距离
```cpp
// dp[i][j] = word1[0..i-1] 转 word2[0..j-1] 的最小操作数
vector<vector<int>> dp(m + 1, vector<int>(n + 1));
// 边界：空串转为目标串，需要逐个插入
for (int i = 0; i <= m; i++) dp[i][0] = i;  // 删除 i 个字符
for (int j = 0; j <= n; j++) dp[0][j] = j;  // 插入 j 个字符
for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++) {
        if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];  // 字符相同，不操作
        else dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
        //              替换 word1[i-1]  删除 word1[i-1]  插入 word2[j-1]
    }
```

---

## 九、快速幂 & 组合数

```cpp
const int MOD = 1e9 + 7;
const int MAXN = 200005;
ll fact[MAXN], invFact[MAXN];

// 快速幂：a^b % MOD，O(log b)
// 原理：把 b 拆成二进制，如 a^13 = a^8 * a^4 * a^1
ll qpow(ll a, ll b) {
    ll res = 1; a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;  // 当前位为 1，乘上对应的幂
        a = a * a % MOD; b >>= 1;        // a 翻倍，b 右移
    }
    return res;
}

// 预处理阶乘和逆元（费马小定理：a^(p-2) ≡ a^(-1) (mod p)，p 为质数）
void init() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
    // 从最大的阶乘逆元倒推：invFact[i] = invFact[i+1] * (i+1)
    // 因为 fact[i] * (i+1) = fact[i+1]，所以 invFact[i] = invFact[i+1] * (i+1)
    invFact[MAXN - 1] = qpow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

// 组合数 C(n, m) = n! / (m! * (n-m)!)，用逆元代替除法
ll C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invFact[m] % MOD * invFact[n - m] % MOD;
}
```

---

## 十、质数筛

### 埃氏筛 O(n log log n)
```cpp
// 从 i*i 开始标记（而非 2*i）：小于 i*i 的合数已被更小的质因子筛过
vector<bool> isPrime(n, true);
for (int i = 2; (ll)i * i < n; i++)  // 只需筛到 sqrt(n)
    if (isPrime[i])
        for (int j = i * i; j < n; j += i)  // i 的倍数都是合数
            isPrime[j] = false;
```

### 欧拉筛 O(n)
```cpp
// 核心思想：每个合数只被它的最小质因子筛掉一次
// i % p == 0 时 break：保证 p*i 的最小质因子就是 p，不会被更大的质因子重复筛
vector<bool> isPrime(n, true);
vector<int> primes;
for (int i = 2; i < n; i++) {
    if (isPrime[i]) primes.push_back(i);  // 没被筛掉，说明是质数
    for (int p : primes) {
        if ((ll)p * i >= n) break;
        isPrime[p * i] = false;  // p*i 是合数，标记
        if (i % p == 0) break;   // p 是 i 的最小质因子，停止（避免重复筛）
    }
}
```

---

## 十一、单调栈 & 单调队列

### 单调栈（右侧第一个更大元素）
```cpp
// 栈内存下标，维护从栈底到栈顶元素值单调递减
// 当前元素比栈顶大 → 栈顶元素找到了右侧第一个更大的值
vector<int> ans(n, -1);
vector<int> st;
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[i] > a[st.back()]) {
        ans[st.back()] = a[i];  // a[i] 是栈顶元素右侧第一个更大的
        st.pop_back();
    }
    st.push_back(i);
}
```

### 单调队列（滑动窗口最小值）
```cpp
// 队首始终是当前窗口的最小值，队列内元素单调递增
// 存下标而非值，方便判断是否滑出窗口
deque<int> dq;
for (int r = 0; r < n; r++) {
    // 维护单调性：新元素比队尾小，队尾不可能成为窗口最小，弹出
    while (!dq.empty() && a[dq.back()] >= a[r]) dq.pop_back();
    dq.push_back(r);
    // 队首下标已滑出窗口左边界，弹出
    if (dq.front() <= r - k) dq.pop_front();
    // 窗口形成后，队首就是最小值
    if (r >= k - 1) {
        int mn = a[dq.front()];  // 窗口 [r-k+1, r] 的最小值
    }
}
```

---

## 十二、图 & 树

### 邻接表建图
```cpp
int n, m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n + 1);
for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});  // 无向图加这行
}
```

### 树的直径（两次 DFS/BFS）
```cpp
// 原理：任意节点出发的最远节点一定是直径端点之一，再从该端点出发求最远距离即直径
vector<vector<pair<int,int>>> g;
int maxDist, farNode;

void dfs(int u, int p, int d) {
    if (d > maxDist) { maxDist = d; farNode = u; }  // 记录最远节点
    for (auto& e : g[u])
        if (e.first != p) dfs(e.first, u, d + e.second);  // 不走回头路
}

int diameter() {
    maxDist = -1; dfs(1, 0, 0);  // 第一次：从任意点（如1）找到最远端点 a
    int a = farNode;
    maxDist = -1; dfs(a, 0, 0);  // 第二次：从 a 出发，最远距离就是直径
    return maxDist;
}
```

### LCA（倍增法）
```cpp
// fa[u][i] = u 的第 2^i 级祖先，如 fa[u][0]=父亲, fa[u][1]=祖父, fa[u][2]=曾祖父
// 预处理 O(n log n)，查询 O(log n)
const int LOG = 20;  // 2^20 > 10^6，足够覆盖 10^6 个节点的树
int fa[MAXN][LOG], depth[MAXN];

void dfs(int u, int p) {
    fa[u][0] = p; depth[u] = depth[p] + 1;
    // 倍增递推：u 的 2^i 祖先 = (u 的 2^(i-1) 祖先) 的 2^(i-1) 祖先
    for (int i = 1; i < LOG; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int v : children[u])
        if (v != p) dfs(v, u);
}

int lca(int u, int v) {
    // 第一步：把较深的节点往上跳，使两者同深度
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[fa[u][i]] >= depth[v]) u = fa[u][i];  // 从大步长试起，能跳就跳
    if (u == v) return u;  // 恰好跳到同一节点，就是 LCA
    // 第二步：u 和 v 同时往上跳，跳到 LCA 的下一层（fa[u][0] 就是 LCA）
    for (int i = LOG - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
    return fa[u][0];
}
```

---

## 十三、回溯（子集/组合/排列）

```cpp
// 子集/组合（元素唯一，不可复选）
// start 参数保证不会回头选之前的元素，避免重复（如 [1,2] 和 [2,1]）
void backtrack(vector<int>& nums, int start) {
    res.push_back(track);  // 子集：每个节点都是一个合法子集，都要收集
    for (int i = start; i < nums.size(); i++) {
        track.push_back(nums[i]);
        backtrack(nums, i + 1);  // 下一轮从 i+1 开始，不能重复选当前元素
        track.pop_back();        // 撤销选择，尝试下一个分支
    }
}

// 全排列
// 用 used 数组标记哪些元素已被选过，避免同一元素重复使用
vector<char> used;
void backtrack(vector<int>& nums) {
    if (track.size() == nums.size()) { res.push_back(track); return; }  // 收集完整排列
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;  // 跳过已使用的元素
        track.push_back(nums[i]); used[i] = 1;  // 选择
        backtrack(nums);                          // 递归
        used[i] = 0; track.pop_back();           // 撤销，回溯到选择前的状态
    }
}
```

---

## 十四、位运算常用

```cpp
n & 1              // 判断奇偶：末位为1是奇数，为0是偶数
n >> 1             // 右移 = /2（向下取整）
n & (n - 1)        // 消除最低位的1（Brian Kernighan），如 1100→1000，可用于计数1的个数
n & (-n)           // lowbit，提取最低位的1，如 1100→0100（树状数组核心操作）
__builtin_popcount(n)  // 二进制中 1 的个数，如 popcount(7)=3
__lg(n)            // floor(log2(n))，即最高位1的位置，n>0
(1 << n) - 1       // 低n位全1掩码，如 n=3 → 0b111 = 7，常用于状态压缩
```

---

## 十五、常见坑 Checklist

- [ ] `long long` 够不够？中间乘法 `(ll)a * b` 先转再乘
- [ ] 数组开够了没？比约束大 5~10
- [ ] 树状数组必须 1-indexed
- [ ] 线段树数组开 4 倍
- [ ] 0/1 背包倒序，完全背包正序
- [ ] 浮点判零用 `abs(x) < EPS`，不要 `== 0`
- [ ] 负数取模 `(x % k + k) % k`
- [ ] `getline` 前吃换行 `cin.ignore()`
- [ ] 输出格式：前导零 `%05d`、行末空格
- [ ] 边界：n=0、n=1、空串、全相同
- [ ] 排序比较器必须严格弱序（`<` 不是 `<=`）
- [ ] 图题：有向/无向？重边/自环？
- [ ] 多组数据重置数组/变量
- [ ] `"\n"` 不用 `endl`
- [ ] BFS/DFS 方向数组正确
