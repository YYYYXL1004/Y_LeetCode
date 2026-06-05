# CSP T3 大模拟题单

来源：[曙梦 OJ - CSP 认证训练计划](https://oj.shumeng.tech/training/68330d72efce6d5ac2765a62)

整理时间：2026-05-29

说明：本文件收录训练页中带有 `模拟` 标签的 CSP 第三题。为方便复习，这里保留原题入口，并写成赛前复习卡式的题意详记和练习重点；完整题面以原题链接为准。

## 总览

| 题号 | 题目 | 练习重点 | 原题 |
| --- | --- | --- | --- |
| CSP201403C | 命令行选项 | 参数解析、状态记录、边界判断 | [链接](https://oj.shumeng.tech/p/5) |
| CSP201409C | 字符串匹配 | 大小写处理、逐行匹配 | [链接](https://oj.shumeng.tech/p/70) |
| CSP201503C | 节日 | 日期推算、星期计算 | [链接](https://oj.shumeng.tech/p/78) |
| CSP201509C | 模板生成系统 | 占位符替换、字符串扫描 | [链接](https://oj.shumeng.tech/p/83) |
| CSP201512C | 画图 | 网格模拟、线段覆盖、连通填充 | [链接](https://oj.shumeng.tech/p/64) |
| CSP201604C | 路径解析 | 路径规范化、栈式处理 | [链接](https://oj.shumeng.tech/p/88) |
| CSP201703C | Markdown | 行级解析、简单状态机 | [链接](https://oj.shumeng.tech/p/560) |
| CSP201809C | 元素选择器 | 树结构、选择器匹配、字符串处理 | [链接](https://oj.shumeng.tech/p/582) |
| CSP201912C | 化学方程式 | 括号解析、计数合并、等式检查 | [链接](https://oj.shumeng.tech/p/550) |
| CSP202006C | Markdown 渲染器 | 块级解析、行内解析、HTML 输出 | [链接](https://oj.shumeng.tech/p/573) |
| CSP202104C | DHCP 服务器 | 协议流程、状态转移、时间模拟 | [链接](https://oj.shumeng.tech/p/545) |
| CSP202206C | 角色授权 | 集合匹配、多条件权限判断 | [链接](https://oj.shumeng.tech/p/32) |
| CSP202406C | 文本分词 | 文本扫描、链表/区间维护 | [链接](https://oj.shumeng.tech/p/308) |
| CSP202409C | 补丁应用 | 文本补丁解析、状态机、输出构造 | [链接](https://oj.shumeng.tech/p/302) |
| CSP202412C | 缓存模拟 | 缓存状态维护、替换策略模拟 | [链接](https://oj.shumeng.tech/p/42) |
| CSP202503C | 模板展开 | 递归展开、变量替换、记忆化 | [链接](https://oj.shumeng.tech/p/138) |
| CSP202506C | 消息解码 | 编码规则解析、字节/字符串处理 | [链接](https://oj.shumeng.tech/p/262) |
| CSP202509C | HTTP 头信息 | 协议表模拟、Huffman 解码、动态表 | [链接](https://oj.shumeng.tech/p/257) |
| CSP202512C | 图片解码 | 二进制/像素解码、格式模拟 | [链接](https://oj.shumeng.tech/p/288) |
| CSP202603C | 进程通信 | 进程状态、队列/集合维护、事件模拟 | [链接](https://oj.shumeng.tech/p/695) |

## 题目详记


### CSP201403C 命令行选项
- 原题：https://oj.shumeng.tech/p/5
- 题意细化：给定一套选项定义和若干行命令行，逐段扫描每个字符串，判断哪些选项被触发、是否带参数，以及当前行是否因为非法输入提前失效。
- 输入输出抓手：先读选项规则，再读若干行命令行；输出通常按选项字母顺序汇总，格式稳定，不能把解析过程中的中间状态直接打印出去。
- 实现要点：先预存“是否需要参数”，再按空格分词后扫描每个片段；如果某个选项需要参数，就把紧跟其后的字符串当作参数值。
- 易错点：`-abc` 不能当成一个整体；缺参时不能跨单词补救；出错后当前行后续内容全部作废。

#### 关键代码（C++）

```cpp
struct OptInfo {
    bool needArg = false;
};

map<char, OptInfo> opt;

vector<string> splitWords(const string& line) {
    vector<string> res;
    string cur;
    stringstream ss(line);
    while (ss >> cur) res.push_back(cur);
    return res;
}

void loadRules(const string& ruleLine) {
    for (int i = 0; i < (int)ruleLine.size(); ++i) {
        if (isalpha((unsigned char)ruleLine[i])) {
            bool need = (i + 1 < (int)ruleLine.size() && ruleLine[i + 1] == ':');
            opt[ruleLine[i]].needArg = need;
        }
    }
}

void handleLine(const string& line) {
    vector<string> tok = splitWords(line);
    map<char, string> seen;
    bool ok = true;
    for (int i = 0; i < (int)tok.size() && ok; ++i) {
        if (tok[i].size() < 2 || tok[i][0] != '-') {
            ok = false;
            break;
        }
        for (int j = 1; j < (int)tok[i].size() && ok; ++j) {
            char c = tok[i][j];
            if (!opt.count(c)) {
                ok = false;
                break;
            }
            if (opt[c].needArg) {
                string arg;
                if (j + 1 < (int)tok[i].size()) arg = tok[i].substr(j + 1);
                else if (i + 1 < (int)tok.size()) arg = tok[++i];
                else {
                    ok = false;
                    break;
                }
                seen[c] = arg;
                break;
            } else {
                seen[c] = "";
            }
        }
    }
    // 按题目要求输出 seen，常见做法是按字母序扫描规则表。
}
```

#### 大模拟技巧/常用语句
- 常用句式：先把规则表读成 `needArg` 标记，再用 `ok` 统一拦截非法行。
- 先把规则表预处理成 `needArg[256]`，解析阶段只查表，不要边扫边推理规则。
- 遇到非法 token、未知选项、缺少参数，立刻停止当前命令行，后面的字符串都不要再看。
- 选项输出建议用 `map<char,string>` 或按 `'a'..'z'` 扫，天然保证字典序。
- 常用语句：`stringstream ss(line); while (ss >> word) ...` 适合空格分隔命令行。
- 常用语句：`if (word.size() < 2 || word[0] != '-') break;` 用来统一拦截非法选项。
- 调试时打印 `word / i / j / seen`，最容易定位“参数吃掉下一项”这类问题。

### CSP201409C 字符串匹配
- 原题：https://oj.shumeng.tech/p/70
- 题意细化：给出一个模式串和多行文本，找出所有包含该模式串的行；题目同时支持大小写敏感和不敏感两种匹配方式。
- 输入输出抓手：文本里可能有空格，必须整行读取；输出时保留原始行内容，不要把匹配用的小写版本直接打印出去。
- 实现要点：不敏感时把模式串和文本统一转小写后做子串查找；敏感时直接比较原串。
- 易错点：转大小写只用于比较，不用于输出；行首行尾空白不能被误删。

#### 关键代码（C++）

```cpp
string lowerCopy(string s) {
    for (char& c : s) c = tolower((unsigned char)c);
    return s;
}

vector<int> solveMatch(const string& pat, const vector<string>& text, bool ignoreCase) {
    string p = ignoreCase ? lowerCopy(pat) : pat;
    vector<int> ans;
    for (int i = 0; i < (int)text.size(); ++i) {
        string cur = ignoreCase ? lowerCopy(text[i]) : text[i];
        if (cur.find(p) != string::npos) ans.push_back(i);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pat;
    getline(cin, pat);
    int n;
    cin >> n;
    string dummy;
    getline(cin, dummy);
    vector<string> text(n);
    for (int i = 0; i < n; ++i) getline(cin, text[i]);

    bool ignoreCase = true; // 按输入规则切换
    auto ans = solveMatch(pat, text, ignoreCase);
    for (int idx : ans) cout << text[idx] << '\n';
    return 0;
}
```

#### 大模拟技巧/常用语句
- 常用句式：比较串和原串分开存，匹配只看归一化版本，输出永远走原始文本。
- 比较串和输出串分开保存：比较用归一化版本，输出永远输出原始行。
- 忽略大小写时统一 `tolower`，不要对中文或非字母字符做额外假设。
- 常用语句：`if (s.find(pattern) != string::npos)` 判断子串存在。
- 常用语句：`for (char& c : s) c = tolower((unsigned char)c);` 避免 `char` 负值 UB。
- 读完数字后要 `getline(cin, dummy)` 吃掉行尾换行。
- 这种题用暴力 `find` 就够，别为了 KMP 把输入输出细节搞乱。

### CSP201503C 节日
- 原题：https://oj.shumeng.tech/p/78
- 题意细化：节日不是固定日号，而是定义成“某月的第几个星期几”；给定年份、月份和星期编号，要找出对应日期。
- 输入输出抓手：若这个日期不存在，输出 `none`；若存在，则输出具体日号即可。
- 实现要点：直接枚举当月每一天，统计目标星期出现次数；配好闰年和月份天数表，反而最稳。
- 易错点：第 5 个星期几经常不存在；星期编号映射写反会整题崩掉；二月天数要单独判断闰年。

#### 关键代码（C++）

```cpp
bool leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int mdays(int y, int m) {
    static int d[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) return d[m] + leap(y);
    return d[m];
}

int weekday(int y, int m, int d) {
    if (m < 3) {
        m += 12;
        --y;
    }
    int c = y / 100, yy = y % 100;
    int w = (d + 26 * (m + 1) / 10 + yy + yy / 4 + c / 4 - 2 * c) % 7;
    return (w + 7) % 7; // 0: Sunday
}

int main() {
    int y, m, x, c;
    cin >> y >> m >> x >> c;
    int cnt = 0;
    for (int d = 1; d <= mdays(y, m); ++d) {
        if (weekday(y, m, d) == c) {
            ++cnt;
            if (cnt == x) {
                cout << d << '\n';
                return 0;
            }
        }
    }
    cout << "none\n";
    return 0;
}
```

#### 大模拟技巧/常用语句
- 常用句式：日期题优先枚举，`days(y,m)` 和 `weekday(y,m,d)` 拆开写最稳。
- 日期题优先考虑“枚举日期”，一个月最多 31 天，逻辑比公式推导更不容易错。
- 把 `leap(y)`、`days(y,m)`、`weekday(y,m,d)` 拆成函数，主流程只写计数。
- 常用语句：`for (int d=1; d<=days(y,m); ++d)`，命中目标星期就 `++cnt`。
- 不存在第 k 个星期几时直接输出 `none`，不要输出 0 或空行。
- 星期映射必须在样例上核对一遍，Zeller 公式输出值和题目编号常不一致。
- 考场上如果公式没把握，可以从已知日期顺推，减少神秘常数出错概率。

### CSP201509C 模板生成系统
- 原题：https://oj.shumeng.tech/p/83
- 题意细化：页面骨架固定，变化的只是数据库里的字段值；模板文本里用占位符表示变量，渲染时要把它们替换成对应内容。
- 输入输出抓手：模板和数据记录可能都跨多行，输入里既有普通文本，也有变量引用；输出是一整段替换后的页面内容。
- 实现要点：顺着模板字符串扫描，遇到占位符就解析变量名，再到映射表里取值替换，其余字符原样输出。
- 易错点：占位符内的空白要忽略或按题意处理；同一变量出现多次要全部替换；缺失字段一般替成空串。

#### 关键代码（C++）

```cpp
string trim(string s) {
    int l = 0, r = (int)s.size() - 1;
    while (l <= r && isspace((unsigned char)s[l])) ++l;
    while (r >= l && isspace((unsigned char)s[r])) --r;
    return s.substr(l, r - l + 1);
}

string renderTemplate(const string& s, const unordered_map<string, string>& mp) {
    string res;
    for (int i = 0; i < (int)s.size(); ) {
        if (i + 1 < (int)s.size() && s[i] == '{' && s[i + 1] == '{') {
            int j = i + 2;
            while (j + 1 < (int)s.size() && !(s[j] == '}' && s[j + 1] == '}')) ++j;
            string key = trim(s.substr(i + 2, j - (i + 2)));
            auto it = mp.find(key);
            if (it != mp.end()) res += it->second;
            i = j + 2;
        } else {
            res += s[i++];
        }
    }
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：扫描到 `{{` 进入变量模式，直到 `}}` 再回到文本模式，变量名先 `trim`。
- 模板题核心是“扫描 + 原样输出”，非占位符字符不要做任何改动。
- 变量名通常要 `trim`，尤其是 `{{ name }}` 这类带空格的写法。
- 常用语句：`while (j+1<n && !(s[j]=='}' && s[j+1]=='}')) ++j;` 找占位符右边界。
- 常用语句：`auto it = mp.find(key); if (it != mp.end()) ans += it->second;` 缺失变量输出空串。
- 多行模板逐行渲染最稳，每行渲染后按题意补回换行。
- 调试时先只输出识别出的 key，确认占位符边界没吃多字符。

### CSP201512C 画图
- 原题：https://oj.shumeng.tech/p/64
- 题意细化：这是一个 ASCII 画板模拟题，需要在字符网格上按指令画出线条，再从指定位置开始填充某种字符。
- 输入输出抓手：输入给的是离散坐标和操作指令，最后输出完整字符画，网格中的每个位置都要落实到具体字符。
- 实现要点：先把线条和边界落到二维数组里，再做 BFS/DFS 进行区域填充；不同元素的覆盖顺序要严格按题意。
- 易错点：坐标原点和数组下标常常不是同一个方向；交叉点字符不能乱写；填充不能越界。

#### 关键代码（C++）

```cpp
void drawLine(vector<string>& g, int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1), dy = -abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    while (true) {
        if (0 <= x1 && x1 < (int)g.size() && 0 <= y1 && y1 < (int)g[0].size())
            g[x1][y1] = ch;
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

void floodFill(vector<string>& g, int sx, int sy, char fill) {
    int n = g.size(), m = g[0].size();
    if (sx < 0 || sx >= n || sy < 0 || sy >= m) return;
    if (g[sx][sy] != '.') return;
    queue<pair<int,int>> q;
    q.push({sx, sy});
    g[sx][sy] = fill;
    int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && g[nx][ny] == '.') {
                g[nx][ny] = fill;
                q.push({nx, ny});
            }
        }
    }
}
```

#### 大模拟技巧/常用语句
- 常用句式：先统一坐标系，再做画线/填充，`put` 和 `floodFill` 分开写。
- 先画边界/线段，再做填充；填充不能穿过线段字符。
- 坐标转换统一写函数，例如 `row = H - 1 - y, col = x`，全题只在这里处理方向。
- 常用语句：`int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};` 四联通填充。
- 常用语句：`if (nx<0||nx>=H||ny<0||ny>=W) continue;` 边界判断固定模板化。
- 横线、竖线、交叉点最好单独写 `putLineChar`，避免覆盖规则散落全题。
- BFS 填色比递归 DFS 更稳，不怕递归深度。

### CSP201604C 路径解析
- 原题：https://oj.shumeng.tech/p/88
- 题意细化：把输入的文件路径规范化成标准形式，类似操作系统里对目录路径做归一化处理。
- 输入输出抓手：每条路径独立处理，输出规范后的目录串；绝对路径和相对路径的输出形式可能不同。
- 实现要点：用栈维护目录层级，遇到普通目录就入栈，遇到 `.` 直接跳过，遇到 `..` 就弹出上一层。
- 易错点：连续斜杠和空段要忽略；根目录不能继续回退；相对路径不要误当成绝对路径。

#### 关键代码（C++）

```cpp
string normalizePath(const string& path, bool absolute) {
    vector<string> st;
    string cur;
    for (int i = 0; i <= (int)path.size(); ++i) {
        if (i == (int)path.size() || path[i] == '/') {
            if (cur == "" || cur == ".") {
            } else if (cur == "..") {
                if (!st.empty()) st.pop_back();
                else if (!absolute) st.push_back("..");
            } else {
                st.push_back(cur);
            }
            cur.clear();
        } else {
            cur += path[i];
        }
    }
    if (st.empty()) return absolute ? "/" : ".";
    string res = absolute ? "/" : "";
    for (int i = 0; i < (int)st.size(); ++i) {
        if (i) res += '/';
        res += st[i];
    }
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：按 `/` 切段后用栈维护路径，遇到 `.` 直接跳过，遇到 `..` 就弹栈。
- 路径规范化就是栈：普通目录入栈，`.` 忽略，`..` 弹栈。
- 连续 `/` 会产生空段，空段必须跳过。
- 常用语句：`if (part.empty() || part==".") continue;`。
- 常用语句：`if (part=="..") { if(!st.empty()) st.pop_back(); }`。
- 输出时再统一拼接 `/`，不要在栈里存带斜杠的字符串。
- 根目录特殊处理：栈空时绝对路径输出 `/`，不能输出空串。

### CSP201703C Markdown
- 原题：https://oj.shumeng.tech/p/560
- 题意细化：把简化版 Markdown 文本翻译成 HTML，题目只覆盖少量常见语法，但要求块级和行内规则都能处理。
- 输入输出抓手：输入是多行 Markdown，输出是对应 HTML 片段；一旦块结构确定，行内语法再在块内部解析。
- 实现要点：先按空行、前缀符号识别标题、列表、段落等块，再对块内文本处理加粗、链接一类标记。
- 易错点：块级语法优先级高于行内；列表要连续合并；空行和换行会改变整篇文档结构。

#### 关键代码（C++）

```cpp
string escapeHtml(string s) {
    string r;
    for (char c : s) {
        if (c == '&') r += "&amp;";
        else if (c == '<') r += "&lt;";
        else if (c == '>') r += "&gt;";
        else r += c;
    }
    return r;
}

string renderInline(const string& s) {
    string t = escapeHtml(s), res;
    for (int i = 0; i < (int)t.size(); ) {
        if (i + 1 < (int)t.size() && t[i] == '*' && t[i + 1] == '*') {
            int j = t.find("**", i + 2);
            if (j != string::npos) {
                res += "<strong>" + t.substr(i + 2, j - (i + 2)) + "</strong>";
                i = j + 2;
                continue;
            }
        }
        if (t[i] == '[') {
            int r = t.find(']', i + 1);
            if (r != string::npos && r + 1 < (int)t.size() && t[r + 1] == '(') {
                int k = t.find(')', r + 2);
                if (k != string::npos) {
                    res += "<a href=\"" + t.substr(r + 2, k - (r + 2)) + "\">" + t.substr(i + 1, r - i - 1) + "</a>";
                    i = k + 1;
                    continue;
                }
            }
        }
        res += t[i++];
    }
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：按行扫描并维护块状态，标题、列表、代码块三类状态最好拆成枚举。
- Markdown 类题固定两层：先分块，再做行内替换。
- 块级状态要显式维护，例如 `inList`、`inPara`，遇到空行统一关闭当前块。
- 常用语句：`closePara(); closeList();` 写成函数，减少漏闭合标签。
- 行内解析用指针 `i` 前进，匹配成功就跳到右边界，失败就原样输出当前字符。
- 列表连续行要包在一个 `<ul>` 里，不是一行开关一次列表。
- 调试顺序：先让块级标签正确，再修行内链接/加粗。

### CSP201809C 元素选择器
- 原题：https://oj.shumeng.tech/p/582
- 题意细化：先按缩进把 HTML/XML 风格的元素组织成树，再回答各种 CSS 风格选择器的查询。
- 输入输出抓手：输入描述树结构和查询语句，输出满足条件的节点集合或编号；查询可能涉及标签、id 和后代关系。
- 实现要点：缩进决定父子关系，节点建树后再做匹配；后代选择器需要沿祖先链判断，而不是只看直接父节点。
- 易错点：id 与标签的大小写规则不同；同层节点顺序要保留；多个匹配结果的去重和排序不要漏。

#### 关键代码（C++）

```cpp
struct Node {
    string tag, id;
    int parent = -1;
    vector<int> child;
};

vector<Node> tr;

bool matchSimple(const Node& x, const string& sel) {
    if (!sel.empty() && sel[0] == '#') return x.id == sel.substr(1);
    return x.tag == sel;
}

bool matchChain(int u, const vector<string>& sels) {
    int cur = u;
    for (int i = (int)sels.size() - 1; i >= 0; --i) {
        while (cur != -1 && !matchSimple(tr[cur], sels[i])) cur = tr[cur].parent;
        if (cur == -1) return false;
        cur = tr[cur].parent;
    }
    return true;
}
```

#### 大模拟技巧/常用语句
- 常用句式：先把选择器拆成条件链，再从树上按祖先/后代关系逐层过滤。
- 缩进建树建议维护 `lastAtDepth[depth]`，当前节点父亲就是上一层最近节点。
- 标签和 id 的大小写规则分开处理，标签可统一小写，id 保持原样。
- 后代选择器不是父子选择器，要沿祖先链向上跳着匹配。
- 常用语句：`while (u!=-1 && !match(u, sel[i])) u = parent[u];`。
- 查询结果按节点输入顺序输出，建树时保留编号即可。
- 如果选择器有多个词，建议从右往左匹配，最后一个选择器先定位当前节点。

### CSP201912C 化学方程式
- 原题：https://oj.shumeng.tech/p/550
- 题意细化：判断化学方程式左右两边是否守恒，也就是方程是否配平。
- 输入输出抓手：每个方程式独立判断，最后输出是否配平的结果即可。
- 实现要点：递归解析元素符号、括号和前导系数，把每种元素的总数累加到 map 里，再比较方程左右两侧。
- 易错点：多位数系数、括号嵌套和括号后的系数都不能漏；元素符号的大小写规则要严格遵守。

#### 关键代码（C++）

```cpp
using Counter = map<string, long long>;

long long parseNum(const string& s, int& i) {
    long long x = 0;
    int j = i;
    while (j < (int)s.size() && isdigit((unsigned char)s[j])) {
        x = x * 10 + s[j] - '0';
        ++j;
    }
    i = j;
    return x == 0 ? 1 : x;
}

string parseAtomName(const string& s, int& i) {
    string name;
    name += s[i++];
    while (i < (int)s.size() && islower((unsigned char)s[i])) name += s[i++];
    return name;
}

Counter merge(const Counter& a, const Counter& b, long long k = 1) {
    Counter c = a;
    for (auto& [x, y] : b) c[x] += y * k;
    return c;
}

Counter parseFormula(const string& s, int& i);

Counter parseFactor(const string& s, int& i) {
    if (s[i] == '(') {
        ++i;
        Counter inside = parseFormula(s, i);
        ++i; // ')'
        long long k = parseNum(s, i);
        for (auto& [x, y] : inside) inside[x] = y * k;
        return inside;
    }
    string atom = parseAtomName(s, i);
    long long k = parseNum(s, i);
    return Counter{{atom, k}};
}

Counter parseFormula(const string& s, int& i) {
    Counter res;
    while (i < (int)s.size() && s[i] != ')' && s[i] != '=') {
        Counter cur = parseFactor(s, i);
        res = merge(res, cur);
        if (i < (int)s.size() && s[i] == '+') ++i;
    }
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：括号用栈记上下文，系数统一在出栈时乘回去，原子计数最后再合并。
- 解析表达式时用 `int& i` 作为游标，函数返回一个元素计数表。
- 原子名、数字、括号三种 token 分开写函数，别在一个 while 里硬怼。
- 常用语句：`map<string,long long> cnt; cnt[atom] += k;`。
- 常用语句：`for (auto& [e,v] : inner) res[e] += v * mul;` 处理括号乘数。
- 左右两侧分别统计，最后比较 map；不用真的配平系数。
- 易错输入优先测：`H2O`、`Mg(OH)2`、`(NH4)2SO4`、多位数系数。

### CSP202006C Markdown 渲染器
- 原题：https://oj.shumeng.tech/p/573
- 题意细化：这题是更完整的 Markdown 渲染器，目标不是“看懂文本”，而是按题目规定精确输出 HTML。
- 输入输出抓手：输入是整篇 Markdown 文本，输出是渲染后的 HTML；行与行之间的空行会直接影响块结构。
- 实现要点：先识别块级结构，再在块内做行内替换；列表、段落、标题等块都要正确打开和闭合。
- 易错点：标签嵌套顺序不能乱；空行会打断块；行内标记通常不能跨行处理。

#### 关键代码（C++）

```cpp
struct MdRenderer {
    vector<string> out;
    bool inPara = false;
    bool inList = false;

    static string escapeHtml(const string& s) {
        string r;
        for (char c : s) {
            if (c == '&') r += "&amp;";
            else if (c == '<') r += "&lt;";
            else if (c == '>') r += "&gt;";
            else r += c;
        }
        return r;
    }

    string renderInline(const string& s) {
        string t = escapeHtml(s), res;
        for (int i = 0; i < (int)t.size(); ) {
            if (i + 1 < (int)t.size() && t[i] == '*' && t[i + 1] == '*') {
                int j = t.find("**", i + 2);
                if (j != string::npos) {
                    res += "<strong>" + t.substr(i + 2, j - (i + 2)) + "</strong>";
                    i = j + 2;
                    continue;
                }
            }
            if (t[i] == '[') {
                int r = t.find(']', i + 1);
                if (r != string::npos && r + 1 < (int)t.size() && t[r + 1] == '(') {
                    int k = t.find(')', r + 2);
                    if (k != string::npos) {
                        res += "<a href=\"" + t.substr(r + 2, k - (r + 2)) + "\">" + t.substr(i + 1, r - i - 1) + "</a>";
                        i = k + 1;
                        continue;
                    }
                }
            }
            res += t[i++];
        }
        return res;
    }

    void closePara() {
        if (inPara) {
            out.push_back("</p>");
            inPara = false;
        }
    }

    void closeList() {
        if (inList) {
            out.push_back("</ul>");
            inList = false;
        }
    }

    void addLine(const string& line) {
        if (line.empty()) {
            closePara();
            closeList();
            return;
        }
        if (!line.empty() && line[0] == '#') {
            closePara();
            closeList();
            int cnt = 0;
            while (cnt < (int)line.size() && line[cnt] == '#') ++cnt;
            string tag = "h" + to_string(cnt);
            string body = line.substr(cnt);
            if (!body.empty() && body[0] == ' ') body.erase(body.begin());
            out.push_back("<" + tag + ">" + renderInline(body) + "</" + tag + ">");
            return;
        }
        if (line.size() >= 2 && line[0] == '-' && line[1] == ' ') {
            closePara();
            if (!inList) {
                out.push_back("<ul>");
                inList = true;
            }
            out.push_back("<li>" + renderInline(line.substr(2)) + "</li>");
            return;
        }
        closeList();
        if (!inPara) {
            out.push_back("<p>");
            inPara = true;
            out.back() += renderInline(line);
        } else {
            out.back() += " " + renderInline(line);
        }
    }

    string finish() {
        closePara();
        closeList();
        string res;
        for (int i = 0; i < (int)out.size(); ++i) {
            if (i) res += '\n';
            res += out[i];
        }
        return res;
    }
};
```

#### 大模拟技巧/常用语句
- 常用句式：块级先切块，块内再做行内解析，解析和输出分层，别混在一层里写。
- 更复杂的渲染题依然坚持“块级优先、行内次之”。
- 每类块都写开关函数：`openList()`、`closeList()`、`closePara()`，避免标签错位。
- 常用语句：`if (line.empty()) { closeAll(); continue; }` 统一处理空行。
- 输出 HTML 时不要多空格、多空行，最终拼接阶段集中控制换行。
- 行内替换不要递归套娃，题目若不要求嵌套，就按最左匹配扫描。
- 调试时用肉眼比对 HTML 标签栈，块级错误通常比行内错误更致命。

### CSP202104C DHCP 服务器
- 原题：https://oj.shumeng.tech/p/545
- 题意细化：模拟 DHCP 服务器分配、续租和回收 IP 地址，按照协议规则处理客户端请求。
- 输入输出抓手：事件按时间顺序到来，处理前要先看有没有租约过期；输出通常是每次请求对应的响应。
- 实现要点：维护地址池、当前占用者和到期时间；每次事件到来前先清理过期项，再执行新的分配或续租。
- 易错点：时间推进和事件处理顺序不能颠倒；重复请求、地址释放和重新分配的优先级要分清。

#### 关键代码（C++）

```cpp
struct Lease {
    int ip = -1;
    string client;
    long long expire = 0;
};

struct DHCPSim {
    int n = 0;
    set<int> freeIps;
    unordered_map<string, Lease> clientLease;
    unordered_map<int, string> ipOwner;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> expireQ;

    void init(int cnt) {
        n = cnt;
        for (int i = 1; i <= n; ++i) freeIps.insert(i);
    }

    void gc(long long now) {
        while (!expireQ.empty() && expireQ.top().first <= now) {
            auto [t, ip] = expireQ.top();
            expireQ.pop();
            if (!ipOwner.count(ip)) continue;
            string client = ipOwner[ip];
            auto it = clientLease.find(client);
            if (it != clientLease.end() && it->second.ip == ip && it->second.expire == t) {
                freeIps.insert(ip);
                ipOwner.erase(ip);
                clientLease.erase(it);
            }
        }
    }

    int alloc(const string& client, long long now, long long ttl) {
        gc(now);
        if (freeIps.empty()) return -1;
        int ip = *freeIps.begin();
        freeIps.erase(freeIps.begin());
        clientLease[client] = {ip, client, now + ttl};
        ipOwner[ip] = client;
        expireQ.push({now + ttl, ip});
        return ip;
    }

    void renew(const string& client, long long now, long long ttl) {
        gc(now);
        if (!clientLease.count(client)) return;
        auto& ls = clientLease[client];
        ls.expire = now + ttl;
        expireQ.push({ls.expire, ls.ip});
    }

    void release(const string& client, long long now) {
        gc(now);
        auto it = clientLease.find(client);
        if (it == clientLease.end()) return;
        freeIps.insert(it->second.ip);
        ipOwner.erase(it->second.ip);
        clientLease.erase(it);
    }
};
```

#### 大模拟技巧/常用语句
- 常用句式：每个请求先做超时清理，再判断可用地址和绑定关系，事件驱动最稳。
- 协议模拟先写状态枚举，再写状态转移，不要直接用字符串散判断。
- 每处理一条消息前先清理过期租约，时间顺序不能反。
- 常用语句：`priority_queue<pair<ll,int>, vector<...>, greater<...>> pq;` 维护过期时间。
- 常用语句：`if (lease.expire == t)` 再回收，避免旧过期事件误删新租约。
- 地址池用 `set<int>`，取最小可用地址就是 `*free.begin()`。
- 对每个报文先判断“是否发给本服务器/广播”，再进入业务逻辑。

### CSP202206C 角色授权
- 原题：https://oj.shumeng.tech/p/32
- 题意细化：判断某个用户在某个资源上执行某个操作时是否有权限，权限来源于角色、授权规则以及用户/用户组绑定。
- 输入输出抓手：先读一批授权配置，再回答若干访问请求；每个请求只需要给出允许或拒绝的结论。
- 实现要点：先把用户能拿到的角色集合整理出来，再拿这些角色去匹配操作、资源类型和资源名。
- 易错点：多级绑定关系容易漏；同一个请求可能被多个角色满足，任一满足即可通过；精确匹配和通配要分层处理。

#### 关键代码（C++）

```cpp
bool wildcardMatch(const string& pat, const string& s) {
    int i = 0, j = 0, star = -1, match = 0;
    while (j < (int)s.size()) {
        if (i < (int)pat.size() && (pat[i] == s[j] || pat[i] == '*')) {
            if (pat[i] == '*') { star = i++; match = j; }
            else ++i, ++j;
        } else if (star != -1) {
            i = star + 1;
            j = ++match;
        } else return false;
    }
    while (i < (int)pat.size() && pat[i] == '*') ++i;
    return i == (int)pat.size();
}

struct Policy {
    string op, type, name;
};

unordered_map<string, vector<Policy>> rolePolicy;
unordered_map<string, vector<string>> userRole;
unordered_map<string, vector<string>> groupRole;
unordered_map<string, vector<string>> userGroup;

bool allow(const string& user, const string& op, const string& type, const string& name) {
    vector<string> roles = userRole[user];
    for (auto& g : userGroup[user]) {
        for (auto& r : groupRole[g]) roles.push_back(r);
    }
    sort(roles.begin(), roles.end());
    roles.erase(unique(roles.begin(), roles.end()), roles.end());

    for (const string& r : roles) {
        for (const Policy& p : rolePolicy[r]) {
            if (wildcardMatch(p.op, op) &&
                wildcardMatch(p.type, type) &&
                wildcardMatch(p.name, name)) {
                return true;
            }
        }
    }
    return false;
}
```

#### 大模拟技巧/常用语句
- 常用句式：权限集合先归一化，再按“任一命中/全部满足”两种逻辑分别判定。
- 权限题按三步走：收集用户角色、遍历角色规则、三字段匹配。
- 用户组、角色、规则都可能多对多，数据结构优先用 `unordered_map<string, vector<string>>`。
- 通配符单独封装 `match(pattern, value)`，主流程不要写三份重复判断。
- 常用语句：`roles.erase(unique(roles.begin(), roles.end()), roles.end());` 角色去重。
- 任一角色满足就允许，别把多个角色条件写成同时满足。
- 资源名为空、通配、精确匹配这几类边界要单独测。

### CSP202406C 文本分词
- 原题：https://oj.shumeng.tech/p/308
- 题意细化：给定长文本和分词规则，把连续字符切成词元，并在修改文本后继续维护分词结果。
- 输入输出抓手：输入一般包含初始文本和若干修改/查询操作；输出对应位置的分词信息或最终结果。
- 实现要点：把词边界当成局部结构处理，修改时只重算受影响的邻域；必要时用链表、平衡树或区间维护。
- 易错点：局部修改可能引发连锁变化；词长度上限和总长度限制要一起考虑；边界处的词元最容易漏。

#### 关键代码（C++）

```cpp
// 局部重算模板：把受影响区间重新切词，再把前后能合并的部分拼回去。
struct Word {
    int l, r;
};

list<Word> words;

bool canMerge(const string& s, int l1, int r1, int l2, int r2) {
    // 按原题的分词规则替换这里。
    return false;
}

void rebuildWindow(const string& s, int L, int R) {
    auto it = words.begin();
    while (it != words.end() && it->r < L) ++it;
    auto start = it;
    while (it != words.end() && it->l <= R) ++it;
    words.erase(start, it);

    // 把 [L, R] 这段重新切分后插回 words。
    // 具体切分逻辑按题意写成 canSplit / canMerge 即可。
}
```

#### 大模拟技巧/常用语句
- 常用句式：先建词库和区间结构，再按最长匹配/指针推进扫描文本。
- 文本维护题不要每次全量重算，先找修改点附近受影响的窗口。
- 把“字符是否同类”“两个片段能否合并”“如何重新切词”拆成函数。
- 常用语句：`auto it = lower_bound/prev/next` 找相邻词元。
- 链表适合频繁插删，数组适合少量修改；看数据范围决定结构。
- 修改后要检查左右边界是否能继续合并，局部变化可能向外扩一小段。
- 调试建议打印词元区间 `[l,r]`，比分词后的字符串更容易看出边界错误。

### CSP202409C 补丁应用
- 原题：https://oj.shumeng.tech/p/302
- 题意细化：读取一份补丁内容，并尝试把它应用到原文本上，过程类似简化版 `diff/patch`。
- 输入输出抓手：补丁一般按块给出，每块含上下文、删除行和新增行；如果某一块不匹配，整份补丁就不能应用。
- 实现要点：逐块校验原文本当前位置和补丁块内容是否一致，再决定是否删除、插入或跳过。
- 易错点：上下文错位会导致整块失败；删除行和新增行的顺序不能写反；空行本身也是内容。

#### 关键代码（C++）

```cpp
struct HunkLine {
    char type;   // ' ', '-', '+'
    string text;
};

bool applyHunk(const vector<string>& src, int& pos, const vector<HunkLine>& hunk, vector<string>& dst) {
    int cur = pos;
    for (auto& line : hunk) {
        if (line.type == ' ') {
            if (cur >= (int)src.size() || src[cur] != line.text) return false;
            dst.push_back(src[cur++]);
        } else if (line.type == '-') {
            if (cur >= (int)src.size() || src[cur] != line.text) return false;
            ++cur;
        } else {
            dst.push_back(line.text);
        }
    }
    pos = cur;
    return true;
}
```

#### 大模拟技巧/常用语句
- 常用句式：补丁先排序再逐段合并，永远按“未覆盖段/覆盖段”拆开输出。
- patch 类题要把每行的前缀字符和正文分开存，正文可能为空。
- 处理一个 hunk 前先校验上下文和删除行，校验失败就整块失败。
- 常用语句：`if (cur>=src.size() || src[cur]!=line.text) return false;`。
- `+` 行只写入输出，不消耗原文；`-` 行只消耗原文，不写入输出；空格行两者都做。
- 多个 hunk 之间原文未涉及部分要原样拷贝。
- 最容易错的是行号偏移，建议统一用 `pos` 表示当前原文游标。

### CSP202412C 缓存模拟
- 原题：https://oj.shumeng.tech/p/42
- 题意细化：模拟组相连缓存的访问过程，判断一次访问是命中、缺失还是触发替换。
- 输入输出抓手：给定访问序列和缓存参数，输出访问结果及统计信息。
- 实现要点：按组维护缓存行，访问时先查组内是否命中，再依据替换策略决定是否装入新块。
- 易错点：组号和块号映射容易错；替换顺序要稳定；若题目带脏位/有效位之类状态，不能只记地址不记状态。

#### 关键代码（C++）

```cpp
struct Line {
    long long tag = -1;
    bool valid = false;
    bool dirty = false;
    int lastUse = 0;
};

struct Cache {
    int sets = 0, ways = 0, blockSize = 0;
    vector<vector<Line>> c;
    int tick = 0;

    void init(int s, int w, int b) {
        sets = s; ways = w; blockSize = b;
        c.assign(sets, vector<Line>(ways));
    }

    bool access(long long addr, bool write) {
        ++tick;
        long long block = addr / blockSize;
        int sid = block % sets;
        long long tag = block / sets;
        auto& v = c[sid];
        for (auto& ln : v) {
            if (ln.valid && ln.tag == tag) {
                ln.lastUse = tick;
                if (write) ln.dirty = true;
                return true;
            }
        }
        int victim = 0;
        for (int i = 1; i < ways; ++i) {
            if (!v[i].valid || v[i].lastUse < v[victim].lastUse) victim = i;
        }
        v[victim] = {tag, true, write, tick};
        return false;
    }
};
```

#### 大模拟技巧/常用语句
- 常用句式：命中、替换、淘汰分开处理，策略状态和内容状态要各自维护。
- 先把地址拆成 `block / set / tag`，后面所有操作都基于这三个量。
- 每个缓存行至少记录 `valid/tag/lastUse`，有写操作再加 `dirty`。
- 常用语句：`block = addr / B; set = block % S; tag = block / S;`。
- 替换策略写成函数 `chooseVictim(set)`，不要塞在主流程里。
- 命中后也要更新时间戳，否则 LRU 会错。
- 空行优先于替换已有行，脏块写回这类统计要在替换前处理。

### CSP202503C 模板展开
- 原题：https://oj.shumeng.tech/p/138
- 题意细化：模板文本里可能引用其他模板或变量，需要把这些引用一路递归展开成最终字符串。
- 输入输出抓手：先读变量定义和模板主体，再输出展开后的完整文本；展开过程中可能会再次遇到引用。
- 实现要点：对引用关系做递归解析，并把中间结果缓存下来，避免重复展开同一模板段。
- 易错点：循环引用和重复展开要提前处理；未定义变量怎么替换要按题意执行；字符串拼接别写成平方复杂度。

#### 关键代码（C++）

```cpp
const long long MOD = 1e9 + 7;

struct Node {
    int type = 0;               // 1: fixed length, 2: token list
    long long len = 0;
    vector<string> tokens;
};

unordered_map<string, Node> defs;

long long dfsLen(const string& name, unordered_map<string, long long>& memo) {
    if (memo.count(name)) return memo[name];
    if (!defs.count(name)) return memo[name] = 0;
    if (defs[name].type == 1) return memo[name] = defs[name].len;
    long long res = 0;
    for (const string& t : defs[name].tokens) {
        if (!t.empty() && t[0] == '$') res = (res + dfsLen(t.substr(1), memo)) % MOD;
        else res = (res + (long long)t.size()) % MOD;
    }
    return memo[name] = res;
}

vector<string> readTokens(const string& line) {
    vector<string> res;
    stringstream ss(line);
    string w;
    while (ss >> w) res.push_back(w);
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：递归展开前先判循环，再用记忆化缓存展开结果，避免重复爆炸。
- 只问长度时绝对不要真的展开字符串，统一维护长度并取模。
- 直接赋值和间接赋值要分开：直接赋值当场固化长度，间接赋值保存 token 列表。
- 常用语句：`if (token[0]=='$') dfs(token.substr(1)); else token.size();`。
- 每次查询新建 `memo`，保证同一次 DFS 内复用结果。
- 未定义变量长度按 0 处理，别访问 map 后自动创建错误节点。
- 若题目保证无环就不用环检测；不保证时加 `visiting` 标记处理递归环。

### CSP202506C 消息解码
- 原题：https://oj.shumeng.tech/p/262
- 题意细化：把按特定编码规则打包的短消息解码成可读内容，题目重点在格式恢复而不是文本本身。
- 输入输出抓手：输入通常是十六进制或压缩编码串，输出是解码后的字段、正文或重建出的消息。
- 实现要点：按位或按字节推进游标，先读长度、类型等头信息，再根据字段定义继续读正文。
- 易错点：进制转换和补零最容易写错；字节边界一乱，后面所有字段都会跟着错位。

#### 关键代码（C++）

```cpp
struct BitReader {
    string bits;
    int p = 0;

    bool empty() const { return p >= (int)bits.size(); }

    int readInt(int k) {
        int x = 0;
        while (k-- && p < (int)bits.size()) x = (x << 1) | (bits[p++] - '0');
        return x;
    }
};

unordered_map<char, string> hex2bits = {
    {'0',"0000"},{'1',"0001"},{'2',"0010"},{'3',"0011"},
    {'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
    {'8',"1000"},{'9',"1001"},{'a',"1010"},{'b',"1011"},
    {'c',"1100"},{'d',"1101"},{'e',"1110"},{'f',"1111"}
};

string hexToBits(const string& s) {
    string bits;
    for (char c : s) bits += hex2bits[tolower((unsigned char)c)];
    return bits;
}
```

#### 大模拟技巧/常用语句
- 常用句式：位流解析一定封装成 `readBit()/readByte()`，指针只做单调前进。
- 编码解码题先写 `BitReader`，所有字段都通过游标读取，别手算下标。
- 十六进制转 bit 串时每个字符固定补成 4 位。
- 常用语句：`x = (x << 1) | (bits[p++] - '0');` 读二进制整数。
- 字段格式建议写成 `readHeader()`、`readPayload()`、`readString()` 小函数。
- 每读完一段都确认游标位置，样例错位通常是少读/多读了一位。
- 输出前再做字符集转换，解析阶段只管原始数值，职责分开更稳。

### CSP202509C HTTP 头信息
- 原题：https://oj.shumeng.tech/p/257
- 题意细化：模拟 HTTP 头部的压缩/解码过程，核心机制包括静态表、动态表和 Huffman 编码。
- 输入输出抓手：指令里可能既有表项引用，也有新字段插入；对于压缩字符串，需要先恢复二进制，再解码成原始头信息。
- 实现要点：静态表按编号直接取值，动态表按插入顺序维护；Huffman 串先按补零规则还原，再按树解码。
- 易错点：动态表的前插和淘汰顺序别搞反；编号从哪一端开始数很关键；普通字符串和编码字符串的前缀规则要分清。

#### 关键代码（C++）

```cpp
struct Node {
    char data = 0;
    shared_ptr<Node> left, right;
    Node() = default;
    Node(char c) : data(c) {}
};

map<string, char> codeToChar;

void buildHuffman(const string& s, int& idx, string path) {
    if (idx >= (int)s.size()) return;
    char cur = s[idx++];
    if (cur == '0') {
        buildHuffman(s, idx, path + "0");
        buildHuffman(s, idx, path + "1");
    } else {
        codeToChar[path] = s[idx++];
    }
}

unordered_map<char, string> hexMap = {
    {'0',"0000"},{'1',"0001"},{'2',"0010"},{'3',"0011"},
    {'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
    {'8',"1000"},{'9',"1001"},{'a',"1010"},{'b',"1011"},
    {'c',"1100"},{'d',"1101"},{'e',"1110"},{'f',"1111"}
};

string decodeHuffmanValue(const string& s) {
    if (s.empty() || s[0] != 'H') return s;
    if (s.size() >= 2 && s[1] == 'H') return s.substr(1);
    int p = s.back() - '0';
    string bits;
    for (int i = 1; i + 2 < (int)s.size(); ++i) bits += hexMap[tolower((unsigned char)s[i])];
    if (p) bits = bits.substr(0, bits.size() - p);
    string res, path;
    for (char b : bits) {
        path += b;
        if (codeToChar.count(path)) {
            res += codeToChar[path];
            path.clear();
        }
    }
    return res;
}
```

#### 大模拟技巧/常用语句
- 常用句式：协议字段表驱动，动态表、字典树、解码器分开写，别把规则散在主流程里。
- 表驱动协议题先统一写 `getEntry(index)`，隐藏静态表/动态表编号差异。
- 动态表用 `deque<pair<string,string>>`，新条目 `push_front`，超容量 `pop_back`。
- 常用语句：`int pos = idx - (S + 1);` 动态表编号转下标。
- Huffman 先建 `code -> char` 映射，再把 hex 展开为 bit 流逐段匹配。
- `HH` 是普通字符串转义，单个 `H` 才表示 Huffman 编码。
- 每条指令先还原 key/value，再决定是否插入动态表，顺序别反。

### CSP202512C 图片解码
- 原题：https://oj.shumeng.tech/p/288
- 题意细化：把编码后的图片数据按规则还原成可读的图像信息，重点在解码流程而不是视觉效果。
- 输入输出抓手：输入是系统生成的编码文件或压缩表示，输出是还原后的图片结果或像素描述。
- 实现要点：先把编码格式分层拆开，再按位推进；块、行、列的关系要先理顺，再去填像素。
- 易错点：图像坐标和数据顺序不是一回事；行尾填充、块边界和颜色通道最容易混。

#### 关键代码（C++）

```cpp
struct BitReader {
    string bits;
    int p = 0;

    int read(int k) {
        int x = 0;
        while (k-- && p < (int)bits.size()) x = (x << 1) | (bits[p++] - '0');
        return x;
    }
};

vector<string> decodeImage(const string& raw, int h, int w) {
    BitReader br{raw};
    vector<string> img(h, string(w, '.'));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int pix = br.read(1); // 按题目实际位宽替换
            img[i][j] = pix ? '#' : '.';
        }
    }
    return img;
}
```

#### 大模拟技巧/常用语句
- 常用句式：先解文件头，再解块/行/像素层，最后统一映射到二维数组。
- 图片/二进制格式题先画出文件层次：头部、块、行、像素，再写读入函数。
- bit 游标必须单调前进，任何对齐/补零都写成独立函数。
- 常用语句：`for (int i=0;i<h;i++) for (int j=0;j<w;j++)` 按输出坐标填图。
- 若数据按块存储，先解块再映射到全图坐标，别边读边乱算。
- RGB/灰度/索引色通道要用结构体保存，避免把通道顺序写反。
- 每行输出前检查宽度，图片题很容易多输出一个空格或少一个像素。

### CSP202603C 进程通信
- 原题：https://oj.shumeng.tech/p/695
- 题意细化：模拟操作系统中的进程通信过程，进程会因为消息、等待或资源关系发生阻塞、唤醒和状态切换。
- 输入输出抓手：输入是一系列事件或指令，输出每一步处理后的结果，或者最终所有进程的状态变化。
- 实现要点：用队列或集合维护等待关系，每个事件到来时先判断当前进程能否运行，再决定通信、阻塞或唤醒。
- 易错点：状态机不能写成单线流程；等待队列顺序要保持；重复唤醒和解除阻塞的时机要和题意完全一致。

#### 关键代码（C++）

```cpp
using ll = long long;
const ll INF = (ll)2e18;

struct Q {
    ll st, len, cnt;  // 队列起始地址、长度、发送次数
};

vector<Q> proc[105];
set<pair<ll, ll>> byLen; // {len, st}
set<pair<ll, ll>> byPos; // {st, len}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    byLen.insert({INF, 0});
    byPos.insert({0, INF});

    while (q--) {
        string op;
        cin >> op;
        if (op == "new") {
            int id;
            ll len;
            cin >> id >> len;
            auto it = byLen.lower_bound({len, -1});
            ll st = it->second, curLen = it->first;
            byLen.erase(it);
            byPos.erase({st, curLen});
            if (curLen > len) {
                byLen.insert({curLen - len, st + len});
                byPos.insert({st + len, curLen - len});
            }
            proc[id].push_back({st, len, 0});
            cout << st << '\n';
        } else if (op == "send") {
            int id;
            cin >> id;
            ll sum = 0;
            for (auto& cur : proc[id]) {
                sum += cur.st + (cur.cnt % cur.len);
                ++cur.cnt;
            }
            cout << sum << '\n';
        } else if (op == "delete") {
            int id, idx;
            cin >> id >> idx;
            --idx;
            ll st = proc[id][idx].st, len = proc[id][idx].len;
            proc[id].erase(proc[id].begin() + idx);

            ll newSt = st, newLen = len;
            auto it = byPos.lower_bound({st, -1});
            if (it != byPos.end() && it->first == st + len) {
                newLen += it->second;
                byLen.erase({it->second, it->first});
                it = byPos.erase(it);
            }
            it = byPos.lower_bound({st, -1});
            if (it != byPos.begin()) {
                --it;
                if (it->first + it->second == st) {
                    newSt = it->first;
                    newLen += it->second;
                    byLen.erase({it->second, it->first});
                    byPos.erase(it);
                }
            }
            byLen.insert({newLen, newSt});
            byPos.insert({newSt, newLen});
        }
    }
    return 0;
}
```

#### 大模拟技巧/常用语句
- 常用句式：消息、等待、唤醒都按事件流处理，队列/集合维护状态，别假设自然顺序。
- 大内存模拟不要开数组，维护“空闲区间集合”和“已分配区间列表”即可。
- best-fit 用两个 set：一个按长度找最短可用段，一个按起点合并相邻段。
- 常用语句：`auto it = byLen.lower_bound({need, -1});` 找最优空闲块。
- 常用语句：`pos = st + (cnt % len); ++cnt;` 模拟环形发送位置。
- delete 时先释放区间，再检查右邻、左邻是否能合并，两套 set 要同步删插。
- 地址和长度用 `long long`，题面内存上界极大，不能用 int 赌运气。

## 未纳入的大三题
训练页中还有两道 CSP 第三题没有 `模拟` 标签，暂未放入本大模拟题单：

- [CSP201312C 最大的矩形](https://oj.shumeng.tech/p/3)：典型单调栈题，重点是把矩形边界压出来。
- [CSP201412C 集合竞价](https://oj.shumeng.tech/p/74)：更偏枚举、排序和数据维护，不属于本页主线模拟题。




