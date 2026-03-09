#include<bits/stdc++.h>
using namespace std;

// 数字转字符：1 -> 'a', 2 -> 'b', ..., 26 -> 'z'
char itc(int n) {
    return (char)('a' + n - 1);
}

// 字符转数字：'a' -> 1, 'b' -> 2, ..., 'z' -> 26
int cti(char c) {
    return (int)(c - 'a' + 1);
}

int main() {
    int N, M;
    cin >> N >> M;
    
    string s;
    s.resize(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        s[i] = itc(x);
    }
    
    while (M--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            // 查找并替换
            int L1;
            cin >> L1;
            string target;
            target.resize(L1);
            for (int i = 0; i < L1; i++) {
                int y;
                cin >> y;
                target[i] = itc(y);
            }
            
            int L2;
            cin >> L2;
            string replacement;
            replacement.resize(L2);
            for (int i = 0; i < L2; i++) {
                int y;
                cin >> y;
                replacement[i] = itc(y);
            }
            
            // 查找第一次出现的位置
            size_t pos = s.find(target);
            if (pos != string::npos) {
                s = s.substr(0, pos) + replacement + s.substr(pos + L1);
            }
            
        } else if (op == 2) {
            // 在相邻和为偶数的元素间插入平均数
            for(int i = 0; i < (int)s.length() - 1; i++) {
                int sum = cti(s[i]) + cti(s[i + 1]);
                if(sum % 2 == 0) {
                    s = s.insert(i + 1, 1, itc(sum / 2));
                    i++; //跳过新插入的
                }
            }            
            // // 或者从后往前处理，避免下标混乱
            // for (int i = (int)s.length() - 2; i >= 0; i--) {
            //     int sum = cti(s[i]) + cti(s[i + 1]);
            //     if (sum % 2 == 0) {
            //         char avg = itc(sum / 2);
            //         s.insert(i + 1, 1, avg);
            //     }
            // }
            
        } else {  // op == 3
            // 翻转 [l, r] 区间（题目是 1-based）
            int l, r;
            cin >> l >> r;
            // 【关键】转换为 0-based
            l--;
            r--;
            reverse(s.begin() + l, s.begin() + r + 1);
        }
    }
    
    // 输出结果
    for (int i = 0; i < (int)s.length(); i++) {
        if (i != 0) cout << " ";
        cout << cti(s[i]);
    }
    
    return 0;
}

/*
 * ==================== string 常用函数速查 ====================
 * 
 * 【1. 查找 find】
 *     size_t pos = s.find("abc");        // 查找子串，返回起始下标
 *     size_t pos = s.find("abc", 2);      // 从下标2开始查找
 *     size_t pos = s.find('a');           // 查找字符
 *     返回值：找到返回下标，找不到返回 string::npos
 *     
 *     【string::npos】本质是 size_t 的最大值 (约 18446744073709551615)
 *     判断是否找到：if (pos != string::npos) { 找到了 }
 *     
 * 【2. 截取 substr】
 *     s.substr(2);            // 从下标2截取到末尾
 *     s.substr(2, 3);         // 从下标2截取3个字符
 *     注意：substr 不改变原串，返回新串
 *     
 * 【3. 插入 insert】（会改变原串！）
 *     s.insert(2, "abc");             // 在下标2处插入字符串"abc"
 *     s.insert(2, 3, 'x');            // 在下标2处插入3个字符'x'
 *     s.insert(2, "abc", 1, 2);       // 在下标2处插入"abc"的[1,2)子串，即"bc"
 *     
 * 【4. 删除 erase】（会改变原串！）
 *     s.erase(2);                // 删除下标2及之后的所有字符
 *     s.erase(2, 3);             // 从下标2开始删除3个字符
 *     s.erase(s.begin() + 2);    // 删除迭代器位置的字符
 *     s.erase(s.begin(), s.begin() + 3);  // 删除[0,3)区间的字符
 *     
 * 【5. 替换 replace】（会改变原串！）
 *     s.replace(2, 3, "abc");    // 从下标2开始删除3个字符，插入"abc"
 *     
 * 【6. 翻转 reverse】（需要 #include<algorithm>）
 *     reverse(s.begin(), s.end());              // 翻转整个串
 *     reverse(s.begin() + 2, s.begin() + 5);    // 翻转[2,5)区间
 *     注意：reverse 是左闭右开区间 [begin, end)
 *     
 * 【7. 其他常用】
 *     s.length() / s.size()      // 返回字符串长度
 *     s.empty()                  // 判断是否为空
 *     s.clear()                  // 清空字符串
 *     s.push_back('x')           // 末尾添加字符
 *     s.pop_back()               // 删除末尾字符
 *     s.append("abc")            // 末尾添加字符串
 *     s += "abc"                 // 末尾添加字符串（更常用）
 *     
 * 【8. 迭代器与下标转换】
 *     下标转迭代器：s.begin() + i
 *     迭代器转下标：it - s.begin()
 *     
 * 【9. 常见坑】
 *     (1) 所有下标从0开始！题目说从1开始要 -1
 *     (2) find 返回 size_t 类型，与 int 比较时注意类型
 *         错误：if (s.find("x") < 0)   // 永远false，因为 size_t >= 0
 *         正确：if (s.find("x") == string::npos)
 *     (3) insert/erase 会改变原串，返回的是改变后的串的引用
 *     (4) reverse 是左闭右开 [begin, end)，题目给 [l,r] 闭区间要用 r+1
 */
