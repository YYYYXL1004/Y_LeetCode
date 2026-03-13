# STL 速查表

> 刷题时忘了就翻这个，不要死记硬背！

## 一、string

### 1. 查找 find
```cpp
size_t pos = s.find("abc");        // 查找子串，返回起始下标
size_t pos = s.find("abc", 2);     // 从下标2开始查找
size_t pos = s.find('a');          // 查找字符
// 返回值：找到返回下标，找不到返回 string::npos

if (s.find("x") != string::npos) { 找到了 }
// ⚠️ 错误：if (s.find("x") < 0)  因为 size_t 永远 >= 0
```

### 2. 截取 substr（不改变原串）
```cpp
s.substr(2);            // 从下标2截取到末尾
s.substr(2, 3);         // 从下标2截取3个字符
```

### 3. 插入 insert（改变原串）
```cpp
s.insert(2, "abc");             // 在下标2处插入字符串"abc"
s.insert(2, 3, 'x');            // 在下标2处插入3个字符'x'
s.insert(2, "abc", 1, 2);       // 在下标2处插入"abc"的[1,2)子串，即"bc"
```

### 4. 删除 erase（改变原串）
```cpp
s.erase(2);                // 删除下标2及之后的所有字符
s.erase(2, 3);             // 从下标2开始删除3个字符
s.erase(s.begin() + 2);    // 删除迭代器位置的字符
```

### 5. 替换 replace（改变原串）
```cpp
s.replace(2, 3, "abc");    // 从下标2开始删除3个字符，插入"abc"
```

### 6. 其他
```cpp
s.length() / s.size()      // 长度
s.empty()                  // 是否为空
s.clear()                  // 清空
s += "abc"                 // 末尾追加
```

---

## 二、vector

### 1. 访问
```cpp
a[i]                  // 下标访问
a.front() / a.back()  // 首尾元素
```

### 2. 插入 insert（改变原容器）
```cpp
a.insert(a.begin() + 2, 5);                    // 在下标2处插入元素5
a.insert(a.begin() + 2, 3, 5);                 // 在下标2处插入3个元素5
a.insert(a.begin() + 2, b.begin(), b.end());   // 插入另一个vector
```

### 3. 删除 erase（改变原容器）
```cpp
a.erase(a.begin() + 2);                // 删除下标2的元素
a.erase(a.begin() + 2, a.begin() + 5); // 删除[2,5)区间
```

### 4. 末尾操作
```cpp
a.push_back(5);    // 末尾添加
a.pop_back();      // 末尾删除
```

### 5. 大小
```cpp
a.size()           // 元素个数
a.empty()          // 是否为空
a.clear()          // 清空
a.resize(10);      // 调整大小
```

---

## 三、算法（需要 #include\<algorithm>）

### 1. 翻转 reverse（左闭右开！）
```cpp
reverse(a.begin(), a.end());              // 翻转整个
reverse(a.begin() + 2, a.begin() + 5);    // 翻转[2,5)区间
// ⚠️ 题目给闭区间[l,r]要用 r+1
```

### 2. 排序 sort（左闭右开！）
```cpp
sort(a.begin(), a.end());                      // 升序
sort(a.begin(), a.end(), greater<int>());      // 降序
sort(a.begin(), a.end(), [](int x,int y){return x>y;}); // 降序lambda
```

### 3. 查找 find
```cpp
auto it = find(a.begin(), a.end(), 5);
if (it != a.end()) { 找到了，下标 = it - a.begin(); }
```

### 4. 去重 unique（先排序！）
```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
```

### 5. 二分查找（前提：有序！）
```cpp
binary_search(a.begin(), a.end(), 5);        // 返回bool，是否存在
lower_bound(a.begin(), a.end(), 5);          // 返回第一个>=5的迭代器
upper_bound(a.begin(), a.end(), 5);          // 返回第一个>5的迭代器
```

---

## 四、set / unordered_set（集合）

### 1. 插入与删除
```cpp
set<int> s;
s.insert(5);              // 插入元素（自动去重）
s.erase(5);               // 删除元素（按值删除）
s.erase(it);              // 删除迭代器位置
s.clear();                // 清空
```

### 2. 查找
```cpp
s.count(5);               // 返回0或1（存在性判断，推荐！）
s.find(5);                // 返回迭代器，找不到返回 s.end()
if (s.find(5) != s.end()) { 存在 }
```

### 3. 大小
```cpp
s.size();                 // 元素个数
s.empty();                // 是否为空
```

### 4. set 特有（有序！）
```cpp
s.begin();                // 最小元素
s.rbegin();               // 最大元素
s.lower_bound(5);         // 第一个>=5的迭代器
s.upper_bound(5);         // 第一个>5的迭代器
```

### 5. set vs unordered_set
| 特性 | set | unordered_set |
|------|-----|---------------|
| 底层 | 红黑树 | 哈希表 |
| 有序 | ✅ 有序 | ❌ 无序 |
| 查找复杂度 | O(log n) | O(1) 平均 |
| 能 lower_bound | ✅ | ❌ |

---

## 五、map / unordered_map（映射）

### 1. 插入与访问
```cpp
map<string, int> m;
m["abc"] = 5;             // 插入或修改
m.insert({"abc", 5});     // 插入（已存在则不覆盖）
m["abc"];                 // 访问（不存在会自动创建，值为0）
```

### 2. 查找
```cpp
m.count("abc");           // 返回0或1（存在性判断，推荐！）
m.find("abc");            // 返回迭代器，找不到返回 m.end()
if (m.count("abc")) { 存在 }
```

### 3. 删除
```cpp
m.erase("abc");           // 按键删除
m.erase(it);              // 按迭代器删除
m.clear();                // 清空
```

### 4. 遍历
```cpp
for (auto& [key, val] : m) {
    cout << key << " " << val << endl;
}
// 或者
for (auto it = m.begin(); it != m.end(); it++) {
    cout << it->first << " " << it->second << endl;
}
```

### 5. map 特有（有序！）
```cpp
m.begin();                // 键最小的元素
m.rbegin();               // 键最大的元素
m.lower_bound("abc");     // 第一个键>= "abc"的迭代器
m.upper_bound("abc");     // 第一个键> "abc"的迭代器
```

### 6. map vs unordered_map
| 特性 | map | unordered_map |
|------|-----|---------------|
| 底层 | 红黑树 | 哈希表 |
| 键有序 | ✅ 有序 | ❌ 无序 |
| 查找复杂度 | O(log n) | O(1) 平均 |
| 能 lower_bound | ✅ | ❌ |

---

## 六、stack（栈）

```cpp
stack<int> st;
st.push(5);               // 入栈
st.pop();                 // 出栈（不返回值！）
st.top();                 // 栈顶元素
st.size();                // 元素个数
st.empty();               // 是否为空
```

⚠️ `pop()` 只删除不返回，要先 `top()` 再 `pop()`

---

## 七、queue（队列）

```cpp
queue<int> q;
q.push(5);                // 入队
q.pop();                  // 出队（不返回值！）
q.front();                // 队首元素
q.back();                 // 队尾元素
q.size();                 // 元素个数
q.empty();                // 是否为空
```

⚠️ `pop()` 只删除不返回，要先 `front()` 再 `pop()`

---

## 八、priority_queue（优先队列/堆）

```cpp
priority_queue<int> pq;   // 默认大根堆（大的在前）
pq.push(5);               // 入队
pq.pop();                 // 弹出堆顶
pq.top();                 // 堆顶元素（最大的）
pq.size();
pq.empty();
pq.emplace();

// 小根堆写法：
priority_queue<int, vector<int>, greater<int>> pq;
priority_queue<int, vector<int>, [](int x, int y) {return x > y; }> pq; 
```

---

## 九、deque（双端队列）

```cpp
deque<int> dq;
dq.push_back(5);          // 尾部插入
dq.push_front(5);         // 头部插入
dq.pop_back();            // 尾部删除
dq.pop_front();           // 头部删除
dq.front();               // 首元素
dq.back();                // 尾元素
dq[i];                    // 下标访问（支持随机访问！）
dq.size();
dq.empty();
dq.clear();
```

---

## 十、常见坑

| 坑 | 错误 | 正确 |
|----|------|------|
| find 返回值 | `if (s.find("x") < 0)` | `if (s.find("x") == string::npos)` |
| reverse 区间 | 题目[l,r]闭区间直接用 | 加1变成 `r+1` |
| 下标从1开始 | 直接用 l, r | `l--; r--;` |
| 遍历时删除 | `for(it) { erase(it); }` | `it = erase(it);` |
| stack/queue 的 pop | `x = st.pop()` | `x = st.top(); st.pop();` |
| map 访问自动创建 | `if (m["x"] == 0)` 不存在也会创建 | `if (m.count("x"))` 先判断 |
| set 不能下标访问 | `s[0]` | `*s.begin()` 用迭代器 |

---

## 十一、迭代器与下标转换

```cpp
下标转迭代器：a.begin() + i
迭代器转下标：it - a.begin()
```

---

## 十二、选择容器速查

| 需求 | 推荐容器 |
|------|---------|
| 动态数组 | `vector` |
| 查找是否存在 | `unordered_set` / `set` |
| 键值对映射 | `unordered_map` / `map` |
| 需要有序遍历 | `set` / `map` |
| 需要范围查询（lower_bound） | `set` / `map` |
| 栈操作（后进先出） | `stack` |
| 队列操作（先进先出） | `queue` |
| 堆/优先队列 | `priority_queue` |
| 双端操作 | `deque` |
| 字符串处理 | `string` |
