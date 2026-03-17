/*
 * L1-064 估值一亿的 AI 核心代码（AI 英文问答程序）
 * 
 * 题目描述：
 * 实现一个 AI 英文问答程序，规则：
 * 1. 无论用户说什么，首先把对方说的话在一行中原样打印出来
 * 2. 消除原文中多余空格：相邻单词间多个空格换成1个，删掉行首尾空格，删掉标点符号前的空格
 * 3. 把原文中所有大写英文字母变成小写，除了 I
 * 4. 把原文中所有独立的 can you、could you 对应地换成 I can、I could
 * 5. 把原文中所有独立的 I 和 me 换成 you
 * 6. 把原文中所有的问号 ? 换成惊叹号 !
 * 
 * 关键点：
 * - "独立"是指被空格或标点符号分隔开的单词
 * - 使用占位符防止嵌套替换污染
 * 
 * 输入样例：
 * 6
 * Hello ?
 *  Good to chat   with you
 * can   you speak Chinese?
 * Really?
 * Could you show me 5
 * What Is this prime? I,don 't know
 * 
 * 输出样例：
 * Hello ?
 * AI: hello!
 *  Good to chat   with you
 * AI: good to chat with you
 * can   you speak Chinese?
 * AI: I can speak chinese!
 * Really?
 * AI: really!
 * Could you show me 5
 * AI: I could show you 5
 * What Is this prime? I,don 't know
 * AI: what Is this prime! you,don't know
 */

#include<bits/stdc++.h>
using namespace std;

/*
 * ==================== 方法一：占位符法（原地修改派） ====================
 * 
 * 核心思路：
 * 1. 用 find + replace 原地替换
 * 2. 关键技巧：先用不可见占位符（\1, \2, \3）替换，最后统一还原
 *    这样避免了"替换后的内容又被匹配"的问题
 * 
 * 占位符映射：
 * - \1 → "I can"（对应 can you）
 * - \2 → "I could"（对应 could you）  
 * - \3 → "you"（对应 I 和 me）
 * 
 * 优点：代码直观，符合"原地修改"直觉
 * 缺点：多次 replace 有内存移动开销
 */
int main() {
    int N;
    cin >> N;
    getchar(); 
    
    while(N--) {
        string s;
        getline(cin, s);
        cout << s << endl;

        // 1. 大写转小写，?转!
        for(int i = 0; i < s.length(); i++) {
            if(s[i] != 'I') s[i] = tolower(s[i]);
            if(s[i] == '?') s[i] = '!';
        }

        // 2. 用 stringstream 去除多余空格
        stringstream ss(s);
        string vs, s1;
        vector<string> v;
        while(ss >> vs) {
            v.push_back(vs);
        }

        // 复原去除多余空格的 s
        for(int i = 0; i < v.size(); i++) {
            // 不是首位，并且第一位是字母或数字，要加空格
            if(i != 0 && isalnum(v[i][0])) s1 += ' ';
            s1 += v[i];
        }

        // 3. 替换 can you → \1（占位符）
        size_t pos = 0;
        while(s1.find("can you", pos) != s1.npos) {
            pos = s1.find("can you", pos);
            // 独立性检查：左边到头或非字母，且右边到头或非字母
            if((pos == 0 || !isalnum(s1[pos - 1])) 
               && (pos + 7 == s1.length() || !isalnum(s1[pos + 7]))) {
                    s1.replace(pos, 7, "\1");  // 用占位符替代，防止嵌套替换
                    pos += 1;
            } else {
                pos += 7;
            }
        }

        // 4. 替换 could you → \2（占位符）
        pos = 0;
        while(s1.find("could you", pos) != s1.npos) {
            pos = s1.find("could you", pos);
            if((pos == 0 || !isalnum(s1[pos - 1])) 
               && (pos + 9 == s1.length() || !isalnum(s1[pos + 9]))) {
                    s1.replace(pos, 9, "\2");
                    pos += 1;
            } else {
                pos += 9;
            }
        }

        // 5. 替换 I → \3（占位符）
        pos = 0;
        while(s1.find("I", pos) != s1.npos) {
            pos = s1.find("I", pos);
            if((pos == 0 || !isalnum(s1[pos - 1])) 
               && (pos + 1 == s1.length() || !isalnum(s1[pos + 1]))) {
                    s1.replace(pos, 1, "\3");
                    pos += 1;
            } else {
                pos += 1;
            }
        }

        // 6. 替换 me → \3（占位符）
        pos = 0;
        while(s1.find("me", pos) != s1.npos) {
            pos = s1.find("me", pos);
            if((pos == 0 || !isalnum(s1[pos - 1])) 
               && (pos + 2 == s1.length() || !isalnum(s1[pos + 2]))) {
                    s1.replace(pos, 2, "\3");
                    pos += 1;
           } else {
                pos += 2;
           }
        }

        // 7. 统一还原占位符
        string res;
        for(int i = 0; i < s1.length(); i++) {
            if(s1[i] == '\1') res += "I can";
            else if(s1[i] == '\2') res += "I could";
            else if(s1[i] == '\3') res += "you";
            else res += s1[i];
        }

        cout << "AI: " << res << endl;
    }
    
    return 0;
}

/*
 * ==================== 方法二：线性扫描法（异地重组派） ====================
 * 
 * 核心思路：
 * 1. 线性扫描原串，逐字符构建新串
 * 2. 遇到匹配的模式就追加替换内容，跳过原串中被替换的部分
 * 3. 不存在"替换顺序"问题，因为是构建新串而非原地修改
 * 
 * 优点：时间复杂度严格 O(N)，免疫连环替换污染
 * 缺点：需要额外空间存储结果串
 * 
 * int main() {
 *     int N; cin >> N;
 *     getchar(); 
 *     
 *     while (N--) {
 *         string s;
 *         getline(cin, s);
 *         cout << s << endl;
 * 
 *         // 1. 字符映射：处理大小写和问号
 *         for (size_t i = 0; i < s.length(); i++) {
 *             if (s[i] >= 'A' && s[i] <= 'Z' && s[i] != 'I') {
 *                 s[i] = tolower(s[i]);
 *             } else if (s[i] == '?') {
 *                 s[i] = '!';
 *             }
 *         }
 * 
 *         // 2. 空格清洗：内联双指针
 *         string s1 = "";
 *         for (size_t i = 0; i < s.length(); ) {
 *             if (s[i] == ' ') {
 *                 size_t j = i;
 *                 while (j < s.length() && s[j] == ' ') j++;
 *                 
 *                 if (j == s.length()) break;
 *                 
 *                 if (isalnum(s[j]) && !s1.empty()) {
 *                     s1 += ' ';
 *                 }
 *                 i = j;
 *             } else {
 *                 s1 += s[i];
 *                 i++;
 *             }
 *         }
 * 
 *         // 3. 模式匹配与替换：线性扫描
 *         string s2 = "";
 *         for (size_t i = 0; i < s1.length(); ) {
 *             bool is_can_you = (i + 7 <= s1.length() && s1.substr(i, 7) == "can you");
 *             bool is_could_you = (i + 9 <= s1.length() && s1.substr(i, 9) == "could you");
 *             bool is_I = (s1[i] == 'I');
 *             bool is_me = (i + 2 <= s1.length() && s1.substr(i, 2) == "me");
 * 
 *             if (is_can_you && (i == 0 || !isalnum(s1[i - 1])) && (i + 7 == s1.length() || !isalnum(s1[i + 7]))) {
 *                 s2 += "I can"; 
 *                 i += 7;
 *             } else if (is_could_you && (i == 0 || !isalnum(s1[i - 1])) && (i + 9 == s1.length() || !isalnum(s1[i + 9]))) {
 *                 s2 += "I could"; 
 *                 i += 9;
 *             } else if (is_I && (i == 0 || !isalnum(s1[i - 1])) && (i + 1 == s1.length() || !isalnum(s1[i + 1]))) {
 *                 s2 += "you"; 
 *                 i += 1;
 *             } else if (is_me && (i == 0 || !isalnum(s1[i - 1])) && (i + 2 == s1.length() || !isalnum(s1[i + 2]))) {
 *                 s2 += "you"; 
 *                 i += 2;
 *             } else {
 *                 s2 += s1[i];
 *                 i++;
 *             }
 *         }
 * 
 *         cout << "AI: " << s2 << endl;
 *     }
 *     
 *     return 0;
 * }
 */
