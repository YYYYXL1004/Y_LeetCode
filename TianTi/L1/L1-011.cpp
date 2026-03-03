/*
本题要求你计算A−B。不过麻烦的是，A和B都是字符串 —— 
即从字符串A中把字符串B所包含的字符全删掉，剩下的字符组成的就是字符串A−B。

输入格式：
输入在2行中先后给出字符串A和B。两字符串的长度都不超过10^4，
并且保证每个字符串都是由可见的ASCII码和空白字符组成，最后以换行符结束。

输出格式：
在一行中打印出A−B的结果字符串。

输入样例：
I love GPLT!  It's a fun game!
aeiou

输出样例：
I lv GPLT!  It's  fn gm!
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;
    // 使用getline读取整行，因为字符串可能包含空格
    getline(cin, s1);
    getline(cin, s2);
    
    // 用unordered_set存储s2中的字符，实现O(1)查找
    unordered_set<char> s;
    for (char c : s2) {
        s.insert(c);
    }
    
    // 遍历s1，只输出不在集合s中的字符
    for (char c : s1) {
        if (s.find(c) == s.end()) {
            cout << c;
        }
    }
    
    return 0;
}

/*
【题解总结】

核心思路：哈希集合快速查找

1. 为什么用getline？
   - 字符串可能包含空格，cin >> 遇到空格会停止
   - getline可以读取整行，包括空格

2. 为什么用unordered_set而不是遍历s2？
   - unordered_set查找时间复杂度：O(1)
   - 遍历s2查找时间复杂度：O(|s2|)
   - 如果s1很长、s2也很长，双重循环会是O(|s1|×|s2|)，会超时
   - 用集合优化后：O(|s1| + |s2|)

3. 替代方案（如果不用set）：
   - 可以用bool数组：bool flag[256] = {false};
   - 遍历s2时标记 flag[c] = true;
   - 遍历s1时检查 if (!flag[c]) 输出
   - 这是用空间换时间，对于ASCII字符很高效

时间复杂度：O(|A| + |B|)
空间复杂度：O(|B|) 或 O(256) 如果用数组
*/
