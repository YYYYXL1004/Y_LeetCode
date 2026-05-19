# set 进阶：竞赛中的 8 个核心用法

> 基础的 insert/erase/find/count 你已经熟了。这里只讲**能拉开差距的用法**。

---

## 1. Floor / Ceiling：找"刚好比它小/大的元素"

这是 set 最被低估的能力。`lower_bound` + 迭代器偏移就能做到。

```cpp
set<int> s = {10, 20, 30, 40};

// Ceiling：第一个 >= x 的元素（lower_bound 本身就是）
auto ceiling = s.lower_bound(25);  // 指向 30

// Floor：最后一个 <= x 的元素
auto floor = s.upper_bound(25);    // 先找第一个 > 25，即 30
if (floor != s.begin()) {
    --floor;                        // 退一步，指向 20
    // *floor 就是 floor 值
}
```

**实战：LeetCode 220 存在重复元素 III** — 用 set 维护滑动窗口，对每个新元素只比较 floor 和 ceiling 两个最近元素，不需要遍历。

**记住这个模式：**
```cpp
auto it = s.lower_bound(x);
// it 指向第一个 >= x 的元素（ceiling）

if (it != s.begin()) {
    auto prev_it = prev(it);  // prev(it) 等价于 --it，但不改变 it
    // *prev_it 是 floor
}
```

---

## 2. 双 set 技巧：同一数据按两种维度排序

**你刚在 CSP202603C 用过的技巧，但值得抽象成模板。**

核心思路：同一份数据维护两个 set，按不同关键字排序，满足两种查询需求。

```cpp
// CSP202603C：内存分配器
set<pair<ll, ll>> s_len;  // {长度, 起始地址} — 用于 best-fit 查找
set<pair<ll, ll>> s_pos;  // {起始地址, 长度} — 用于 delete 时找相邻块

// 插入时：两边都插
s_len.insert({len, addr});
s_pos.insert({addr, len});

// 删除时：两边都删
s_len.erase({len, addr});
s_pos.erase({addr, len});

// 查找最短可用块：在 s_len 上 lower_bound
auto it = s_len.lower_bound({need_len, -1});
```

**适用场景：** 需要"按 A 排序查找"和"按 B 排序查找"两种操作，且数据会动态增删。典型如：内存分配（按大小/按地址）、事件调度（按时间/按优先级）。

**注意事项：**
- 两个 set 必须同步增删，漏一个就是 bug
- `pair` 的比较是先比 first 再比 second，设计键的顺序很重要
- 删除时用 `erase({val1, val2})` 而不是遍历找

---

## 3. multiset：允许重复的有序集合

`set` 自动去重，但很多场景需要保留重复元素。`multiset` 就是答案。

```cpp
multiset<int> ms;
ms.insert(5);
ms.insert(5);  // 允许插入两次
ms.count(5);   // 返回 2

// 删除：erase(value) 会删掉所有相同值！
ms.erase(ms.find(5));  // 只删一个，find 返回第一个匹配的迭代器
```

**实战：滑动窗口中位数**
```cpp
// 维护两个 multiset：左半部分（大根）和右半部分（小根）
multiset<int> left, right;  // left 存较小的一半，right 存较大的一半

void add(int x) {
    if (left.empty() || x <= *left.rbegin()) {
        left.insert(x);
    } else {
        right.insert(x);
    }
    // 保持平衡：left.size() == right.size() 或 left.size() == right.size() + 1
    while (left.size() > right.size() + 1) {
        right.insert(*left.rbegin());
        left.erase(prev(left.end()));
    }
    while (right.size() > left.size()) {
        left.insert(*right.begin());
        right.erase(right.begin());
    }
}

void remove(int x) {
    // 先判断在哪个集合里
    if (x <= *left.rbegin()) {
        left.erase(left.find(x));  // 只删一个！
    } else {
        right.erase(right.find(x));
    }
    // 再平衡（同上）
}

int getMedian() {
    return *left.rbegin();
}
```

**关键坑：`ms.erase(value)` 删除所有匹配项，只删一个必须 `ms.erase(ms.find(value))`。**

---

## 4. set 管理空闲区间：内存分配 / 区间调度

这是竞赛中 set 的杀手级应用。用 set 维护"空闲段"，每次取最优段并拆分/合并。

**模板：Best-Fit 内存分配**
```cpp
set<pair<ll, ll>> free_blocks;  // {长度, 起始地址}

// 分配长度为 need 的块
auto it = free_blocks.lower_bound({need, -1});
if (it == free_blocks.end()) { /* 分配失败 */ }
auto [len, addr] = *it;
free_blocks.erase(it);
if (len > need) {
    free_blocks.insert({len - need, addr + need});
}
// 使用 [addr, addr + need - 1]

// 释放区间 [addr, addr + len - 1]，需要合并相邻块
// 用另一个按地址排序的 set 找邻居（参考双 set 技巧）
```

**实战：CSP202603C** 就是这个模板的完整实现。

---

## 5. mutable：通过 const 迭代器修改非键字段

set 的迭代器是 const 的（因为修改键会破坏有序性），但有时你需要修改"附加数据"而不碰键。`mutable` 就是为此设计的。

```cpp
struct drop {
    int x;            // 键：决定排序，不可变
    mutable int w;    // 非键：mutable 允许通过 const 迭代器修改
    bool operator<(const drop& other) const { return x < other.x; }
};

set<drop> s;
s.insert({10, 2});
auto it = s.find({10, 0});  // 按 x 查找，w 值无所谓
it->w++;                     // 合法！mutable 允许修改
```

**为什么需要 mutable？**
- 普通 set 迭代器解引用得到的是 `const T&`，直接修改成员会编译报错
- `mutable` 标记的成员绕过 const 检查，但仍保证键（排序依据）不被篡改
- 比"删除再插入"更高效且不会使迭代器失效

**适用场景：** 键是位置/编号等不变量，附加数据是计数/权重等需要频繁更新的值。

**实战：CSP202403D 水滴爆炸** — set 按位置排序，重量 `w` 用 mutable 实现原地 `it->w++`，达到阈值后触发链式反应。配合 priority_queue 维护待爆炸位置，`prev(it)` / `next(it)` 找邻居。

**注意：**
- `mutable` 只能用于非键字段，改键会导致 set 内部结构损坏
- `find({key, 0})` 中附加值填什么都行，只比较键
- 与"删除再插入"的区别：mutable 原地修改，迭代器不失效；删除再插入是 O(log n) 且会使旧迭代器失效

---

## 6. 自定义比较器：让 set 按你的方式排序

```cpp
// 写法一：lambda（推荐，灵活）
auto cmp = [](const State& a, const State& b) {
    return a.dist < b.dist;
};
set<State, decltype(cmp)> s(cmp);

// 写法二：重载 operator<（简单场景）
struct State {
    int node, dist;
    bool operator<(const State& other) const {  // const 必须写
        return dist < other.dist;               // 小的在前
    }
};
set<State> s;
```

**实战：L3-043 门诊预约排队系统** — 用 `set<people, decltype(cmp)>` 按预约号排序维护候诊池。

**注意：** 比较器必须满足**严格弱序**（strict weak ordering）。写 `<=` 会崩溃。如果比较器依赖可变字段，插入后修改该字段会导致 set 内部结构损坏。

---

## 7. set 去重 + 排序 + 压缩：一行替代 sort+unique

```cpp
// 传统做法：sort + unique + erase
vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());

// set 做法：一行搞定
set<int> s(a.begin(), a.end());
vector<int> b(s.begin(), s.end());  // 如果需要 vector
```

**坐标压缩（离散化）：**
```cpp
// 把大范围值映射到紧凑下标
vector<int> a = {100, 50000, 1000000, 100};
set<int> s(a.begin(), a.end());
vector<int> sorted(s.begin(), s.end());

// 值 -> 下标
int idx = lower_bound(sorted.begin(), sorted.end(), val) - sorted.begin();
```

---

## 8. 有序集合 + 动态第 K 大

`set` 本身不支持按秩查找（找第 K 个），但可以用以下方式：

**方式一：遍历（O(K)）**
```cpp
auto it = s.begin();
advance(it, k - 1);  // 第 k 小
```

**方式二：用 `pb_ds` 的有序集合（O(log N)）**
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>,
                         rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<int> os;
os.insert(5);
os.insert(10);
os.insert(3);
*os.find_by_order(1);   // 第 2 小的元素（0-indexed）
os.order_of_key(7);     // 严格小于 7 的元素个数
```

竞赛中用 `pb_ds` 的不多，但如果需要频繁查第 K 大且需要动态插入删除，它比手写平衡树快得多。

---

## 9. 遍历删除的正确姿势

```cpp
// 错误：迭代器失效
for (auto it = s.begin(); it != s.end(); ++it) {
    if (条件) s.erase(it);  // erase 后 it 失效，++it 是未定义行为
}

// 正确：erase 返回下一个迭代器
for (auto it = s.begin(); it != s.end(); ) {
    if (条件) {
        it = s.erase(it);  // erase 返回下一个有效迭代器
    } else {
        ++it;
    }
}

// C++20 更简洁（如果 OJ 支持）
std::erase_if(s, [](int x) { return x % 2 == 0; });
```

---

## 速查：什么时候用 set？

| 场景 | 用什么 |
|------|--------|
| 去重 + 排序 | `set` |
| 动态找 floor/ceiling | `set` + `lower_bound` |
| 滑动窗口最值/中位数 | `multiset` |
| 内存分配/区间合并 | 双 `set`（按大小+按地址） |
| 键不可变、附加值需频繁修改 | `set` + `mutable` |
| 自定义排序的有序容器 | `set<T, decltype(cmp)>` |
| 只需要去重不需要排序 | `unordered_set`（O(1) 更快） |
| 需要重复元素 | `multiset` |
| 需要按秩查找 | `pb_ds::ordered_set` |

---

## 经典题型索引

| 技巧 | 对应题目 |
|------|---------|
| floor/ceiling 查询 | LeetCode 220 存在重复元素 III |
| 双 set 内存分配 | CSP202603C |
| mutable 原地修改附加值 | CSP202403D 水滴爆炸 |
| multiset 滑动窗口中位数 | LeetCode 480 |
| 自定义比较器 set | 天梯赛 L3-043 门诊预约排队 |
| set 去重排序 | 天梯赛 L2-005、L2-024 |
| set 维护连通分量根 | 天梯赛 L2-013、L2-025 |
