/*
输入一个整数，输出每个数字对应的拼音。当整数为负数时，先输出"fu"字。

十个数字对应的拼音如下：
0: ling
1: yi
2: er
3: san
4: si
5: wu
6: liu
7: qi
8: ba
9: jiu

输入格式：
输入在一行中给出一个整数，如：1234。
提示：整数包括负数、零和正数。

输出格式：
在一行中输出这个整数对应的拼音，每个数字的拼音之间用空格分开，行末没有最后的空格。
如：yi er san si。

输入样例：
-600

输出样例：
fu liu ling ling
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 用vector存储0-9对应的拼音，下标即数字，访问更方便
    vector<string> v = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    
    int n;
    cin >> n;
    
    // 处理负数：先输出"fu"，然后转为正数
    if (n < 0) {
        cout << "fu";
        n = -n;
    }
    
    // 将数字转为字符串，逐位处理
    string s = to_string(n);
    
    // 第一个数字前面不加空格，后面的数字前面都加空格
    // 这样避免行末有多余空格
    cout << v[s[0] - '0'];
    for (int i = 1; i < s.size(); i++) {
        cout << " " << v[s[i] - '0'];
    }
    
    return 0;
}

/*
关于为什么不用map/unordered_map：

1. 语法问题：
   unordered_map的列表初始化需要双层大括号：
   unordered_map<int, string> mp = {{0, "ling"}, {1, "yi"}, ...};
   你原来的写法 {0, "ling"} 语法不正确。

2. 效率问题：
   - map: 基于红黑树，查找O(log n)
   - unordered_map: 基于哈希表，查找O(1)但有哈希计算开销
   - vector: 连续内存，直接下标访问，O(1)且常数极小

3. 适用场景：
   当key是连续的整数（0-9），用vector/array是最简单高效的选择。
   map适合key不连续、范围大或需要有序遍历的场景。
*/
