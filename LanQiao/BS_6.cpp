/*
蓝桥杯省赛练习：选择根使代价最小

问题描述
给定一棵有 N 个结点的无向树，结点编号为 1..N。第 i 个结点有一个权值 ai。

你需要选择一个结点作为根。设结点 i 在这棵有根树中的深度为 depi（根深度为 0）。
定义代价：
F = sum((ai - depi) * (ai + depi))

请你求出不同根选择下，代价 F 的最小值。

输入格式
第一行输入整数 T，表示测试组数。
每组数据：
第一行一个整数 N。
第二行 N 个整数 a1..aN。
接下来 N-1 行，每行两个整数 u, v，表示无向边。

输出格式
每组输出一个整数，表示最小可能代价。

样例输入
2
3
2 2 2
1 2
2 3
5
1 1 1 1 1
1 2
2 3
3 4
4 5

样例输出
7
-25
*/

#include <bits/stdc++.h>
using namespace std;

#if 0
/*
旧实现（非递归换根DP）已保留在提交历史中。
当前改为递归双DFS版本，便于理解树形DP与换根公式。
*/

const int MAXN = 10005;
vector<int> mp[MAXN];

// DP 状态数组
long long sz[MAXN];    // sz[i]: 以 1 为根时，i 的子树大小
long long sum1[MAXN];  // sum1[i]: 以 1 为根时，i 的子树内所有节点到 i 的距离和
long long sum2[MAXN];  // sum2[i]: 以 1 为根时，i 的子树内所有节点到 i 的距离平方和

long long ans1[MAXN];  // ans1[i]: 以 i 为根时，全树所有节点到 i 的距离和
long long ans2[MAXN];  // ans2[i]: 以 i 为根时，全树所有节点到 i 的距离平方和

int N;
long long max_dep2_sum;

// 第一次 DFS：默认以 1 为根，自底向上算出每个子树的信息 (sz, sum1, sum2)
void dfs1(int u, int fa) {
    sz[u] = 1;
    sum1[u] = 0;
    sum2[u] = 0;

    for (int v : mp[u]) {
        if (v == fa) continue;
        dfs1(v, u);

        // 核心合并逻辑：把子树 v 接到节点 u 上
        sz[u] += sz[v];
        sum1[u] += sum1[v] + sz[v]; // 距离全体 +1
        sum2[u] += sum2[v] + 2 * sum1[v] + sz[v]; // 平方和公式：(d+1)^2 = d^2 + 2d + 1
    }
}

// 第二次 DFS：自顶向下进行“换根”，用父节点 u 的答案推导子节点 v 的答案
void dfs2(int u, int fa) {
    for (int v : mp[u]) {
        if (v == fa) continue;

        // 当根从 u 换到 v 时：
        // ans1 的变化：v子树内(sz[v])距离减1，其他节点(N - sz[v])距离加1
        ans1[v] = ans1[u] - 2 * sz[v] + N;

        // ans2 的变化公式，通过完全平方展开化简得到 O(1) 转移
        ans2[v] = ans2[u] + 2 * ans1[u] - 4 * (sum1[v] + sz[v]) + N;

        max_dep2_sum = max(max_dep2_sum, ans2[v]); // 记录全树最大值

        dfs2(v, u); // 继续往下换根
    }
}

void solve() {
    cin >> N;
    long long sum_a2 = 0;
    for (int i = 1; i <= N; i++) {
        long long a;
        cin >> a;
        sum_a2 += a * a;
        mp[i].clear(); // 清空图
    }

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    // 步骤 1：以 1 为根预处理
    dfs1(1, 0);

    // 步骤 2：初始化根节点 1 的全局答案
    ans1[1] = sum1[1];
    ans2[1] = sum2[1];
    max_dep2_sum = ans2[1];

    // 步骤 3：开始全局换根
    dfs2(1, 0);

    cout << sum_a2 - max_dep2_sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}

// 【总结】
// 1) 公式化简：F = sum(a_i^2 - dep_i^2) = 常数 - sum(dep_i^2)。
// 2) 等价目标：最大化“到所有点的距离平方和”sum(dep_i^2)。
// 3) 先做一次后序DP算子树贡献，再做一次换根DP把答案扩展到所有根。
// 4) 复杂度：每组 O(N)，适合多测树题。
// 5) 易错点：
//    - 全程用 long long；
//    - 换根平方和公式别写错：ans2[v] = ans2[u] + 2*ans1[u] - 4*(sum1[v]+sz[v]) + N。
#endif

/*
骗分题解（部分分策略）：
只比较直径两端 A/B 作为根的结果（启发式，不保证最优，实测可拿较高部分分）。
*/

#if 0
// 旧骗分实现（小数据暴力 + 大数据启发）保留
const int LIMIT = 2000;

static long long calc_dep2_sum_by_root(int root, const vector<vector<int>>& g) {
    int n = (int)g.size() - 1;
    vector<int> dep(n + 1, -1);
    queue<int> q;
    dep[root] = 0;
    q.push(root);

    long long dep2 = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        dep2 += 1LL * dep[u] * dep[u];

        for (int v : g[u]) {
            if (dep[v] != -1) continue;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    return dep2;
}

static pair<int, long long> farthest_from(int s, const vector<vector<int>>& g) {
    int n = (int)g.size() - 1;
    vector<int> dep(n + 1, -1);
    queue<int> q;
    dep[s] = 0;
    q.push(s);

    int farNode = s;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dep[u] > dep[farNode]) farNode = u;

        for (int v : g[u]) {
            if (dep[v] != -1) continue;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }

    long long dep2 = 0;
    for (int i = 1; i <= n; i++) dep2 += 1LL * dep[i] * dep[i];
    return {farNode, dep2};
}

static void solve_partial() {
    int n;
    cin >> n;

    long long sum_a2 = 0;
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a;
        sum_a2 += a * a;
    }

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    long long best_dep2 = 0;

    if (n <= LIMIT) {
        // 小数据精确解：枚举所有根
        for (int r = 1; r <= n; r++) {
            best_dep2 = max(best_dep2, calc_dep2_sum_by_root(r, g));
        }
    } else {
        // 大数据启发式：只看直径两端
        int A = farthest_from(1, g).first;
        auto [B, dep2A] = farthest_from(A, g);
        long long dep2B = farthest_from(B, g).second;
        best_dep2 = max(dep2A, dep2B);
    }

    cout << (sum_a2 - best_dep2) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve_partial();
    return 0;
}

// 【总结】
// 1) 这版是“骗分策略”，不是满分保证解。
// 2) N 小时用 O(N^2) 暴力枚举根，结果精确。
// 3) N 大时用“直径两端 A/B”启发式，通常能拿到一定分数。
// 4) 这版适合赛前树形DP不熟、以部分分为目标的情况。
#endif

#define debug(x) cout << #x << " " << x << "\n"

const int MAXN = 10005;
vector<int> mp[MAXN];
int depth[MAXN];
long long maxd = -1;

int max_node;

void dfs(int u, int p, int d) {
    depth[u] = d;
    if (d > maxd) { // 记录最远点
        max_node = u;
        maxd = d;
    }
    for (int v : mp[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        long long suma = 0, sumda = 0, sumdb = 0;
        for (int i = 1; i <= N; i++) {
            int a;
            cin >> a;
            suma += 1LL * a * a;
            mp[i].clear();
            depth[i] = 0;
        }
        for (int i = 1; i <= N - 1; i++) {
            int u, v;
            cin >> u >> v;
            mp[u].push_back(v);
            mp[v].push_back(u);
        }
        maxd = -1;
        dfs(1, 0, 0); // 以1为根dfs找到a
        int a_node = max_node;  // 节点a
        maxd = -1;
        dfs(a_node, 0, 0); // 以a为根dfs找到b
        for (int i = 1; i <= N; i++) {
            sumda += 1LL * depth[i] * depth[i];
        }

        int b_node = max_node; // 节点b
        maxd = -1;
        dfs(b_node, 0, 0); // 再以b为根，更新一次depth数组
        for (int i = 1; i <= N; i++) {
            sumdb += 1LL * depth[i] * depth[i];
        }
        long long res = suma - max(sumda, sumdb);
        cout << res << "\n";
    }
    return 0;
}

// 【总结】
// 1) 这版是直径端点启发式骗分题解，不保证最优，但实现简单。
// 2) 流程：1 -> A，A -> B（并统计A为根），B -> 全点（统计B为根）。
// 3) 最终用 suma - max(sumda, sumdb)。

