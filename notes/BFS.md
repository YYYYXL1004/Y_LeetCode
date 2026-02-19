# BFS（广度优先搜索）

## 核心框架

BFS 用队列逐层扩散，天然适合求最短路径/最少步数问题。

```cpp
int bfs(起点, 终点) {
    queue<T> q;
    unordered_set<T> visited;
    q.push(起点);
    visited.insert(起点);
    int step = 0;

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            auto cur = q.front(); q.pop();
            if(cur == 终点) return step;
            for(auto next : getNeighbors(cur)) {
                if(!visited.count(next)) {
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
        step++;
    }
    return -1;
}
```

关键点：
- `visited` 防止走回头路（图中有环时必须）
- 每层遍历完 `step++`，保证第一次到达终点就是最短路径
- 核心在于如何抽象"状态"和"相邻状态"

## 一、打开转盘锁（752）

4 位密码锁，每次拨动一位（上/下），避开死亡密码，求从 "0000" 到 target 的最少步数。

状态抽象：每个 4 位字符串是一个节点，每次拨动产生 8 个相邻节点。

```cpp
int openLock(vector<string>& deadends, string target) {
    unordered_set<string> deads(deadends.begin(), deadends.end());
    if(deads.count("0000")) return -1;

    unordered_set<string> visited;
    queue<string> q;
    q.push("0000");
    visited.insert("0000");
    int step = 0;

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            string cur = q.front(); q.pop();
            if(cur == target) return step;
            for(string next : getNeighbors(cur)) {
                if(!visited.count(next) && !deads.count(next)) {
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
        step++;
    }
    return -1;
}

// 8 个相邻密码：每一位上拨/下拨
vector<string> getNeighbors(string s) {
    vector<string> neighbors;
    for(int i = 0; i < 4; i++) {
        string up = s, down = s;
        up[i] = up[i] == '9' ? '0' : up[i] + 1;
        down[i] = down[i] == '0' ? '9' : down[i] - 1;
        neighbors.push_back(up);
        neighbors.push_back(down);
    }
    return neighbors;
}
```

## 二、滑动谜题（773）

2×3 棋盘，数字 0 代表空格，通过交换 0 和相邻数字，将棋盘还原为 `[[1,2,3],[4,5,0]]`。

状态抽象：将 2×3 棋盘压缩为长度 6 的字符串，预计算每个位置的相邻位置映射。

```cpp
int slidingPuzzle(vector<vector<int>>& board) {
    string target = "123450";
    string start = "";
    for(auto& row : board)
        for(int x : row) start += to_string(x);

    // 一维索引的相邻关系映射
    // 0 1 2
    // 3 4 5
    vector<vector<int>> mapping = {
        {1,3}, {0,2,4}, {1,5}, {0,4}, {1,3,5}, {2,4}
    };

    queue<string> q;
    unordered_set<string> visited;
    q.push(start);
    visited.insert(start);
    int step = 0;

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            string cur = q.front(); q.pop();
            if(cur == target) return step;
            int idx = cur.find('0');
            for(int adj : mapping[idx]) {
                string next = cur;
                swap(next[idx], next[adj]); // 先拷贝再交换
                if(!visited.count(next)) {
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
        step++;
    }
    return -1;
}
```

注意：`swap` 返回 `void`，不能写 `string s = swap(a, b)`，要先拷贝再原地交换。

## 相关题目

| 题号 | 题目 | 难度 | 备注 |
|------|------|------|------|
| 752 | 打开转盘锁 | 中等 | 字符串状态 BFS，8 个邻居 |
| 773 | 滑动谜题 | 困难 | 棋盘压缩为字符串，预计算邻接关系 |
