/*
 * L1-101 别再来这么多猫娘了！
 * 
 * 题目描述：
 * 你会得到一段由大小写字母、数字、空格及 ASCII 码范围内的标点符号的文字，
 * 以及若干个违禁词以及警告阈值，你需要首先检查内容里有多少违禁词，
 * 如果少于阈值个，则简单地将违禁词替换为<censored>；
 * 如果大于等于阈值个，则直接输出一段警告并输出有几个违禁词。
 * 
 * 输入格式:
 * 输入第一行是一个正整数 N (1≤N≤100)，表示违禁词的数量。
 * 接下来的 N 行，每行一个长度不超过 10 的、只包含大小写字母、数字及 ASCII 码范围内的标点符号的单词，表示应当屏蔽的违禁词。
 * 然后的一行是一个非负整数 k (0≤k≤100)，表示违禁词的阈值。
 * 最后一行是不超过 5000 个字符的字符串，表示需要检查的文字。
 * 
 * 处理规则：
 * 从左到右处理文本，违禁词按照输入顺序依次处理；
 * 对于有重叠的情况，无论计数还是替换，查找完成后从违禁词末尾继续处理。
 * 
 * 输出格式:
 * 如果违禁词数量小于阈值，则输出替换后的文本；
 * 否则先输出一行一个数字，表示违禁词的数量，然后输出 He Xie Ni Quan Jia!
 * 
 * 输入样例1:
 * 5
 * MaoNiang
 * SeQing
 * BaoLi
 * WeiGui
 * BuHeShi
 * 4
 * BianCheng MaoNiang ba! WeiGui De Hua Ye Keyi Shuo! BuYao BaoLi NeiRong.
 * 
 * 输出样例1:
 * BianCheng <censored> ba! <censored> De Hua Ye Keyi Shuo! BuYao <censored> NeiRong.
 * 
 * 输入样例2:
 * 5
 * MaoNiang
 * SeQing
 * BaoLi
 * WeiGui
 * BuHeShi
 * 3
 * BianCheng MaoNiang ba! WeiGui De Hua Ye Keyi Shuo! BuYao BaoLi NeiRong.
 * 
 * 输出样例2:
 * 3
 * He Xie Ni Quan Jia!
 * 
 * 输入样例3:
 * 2
 * AA
 * BB
 * 3
 * AAABBB
 * 
 * 输出样例3:
 * <censored>A<censored>B
 * 
 * 输入样例4:
 * 2
 * AB
 * BB
 * 3
 * AAABBB
 * 
 * 输出样例4:
 * AA<censored><censored>
 * 
 * 输入样例5:
 * 2
 * BB
 * AB
 * 3
 * AAABBB
 * 
 * 输出样例5:
 * AAA<censored>B
 * 
 * 解题思路：
 * 按违禁词输入顺序依次处理，每个违禁词在文本中找所有出现并替换。
 * 先用临时占位符 "-_-" 替换，避免后续违禁词匹配到已替换的部分。
 * 最后根据阈值决定输出警告还是替换为 "<censored>"。
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    
    int k;
    cin >> k;
    getchar();
    
    string s;
    getline(cin, s);
    
    int cnt = 0;
    
    // 按违禁词顺序依次处理
    for (int i = 0; i < n; i++) {
        // 找到所有该违禁词并替换为临时占位符
        while (s.find(words[i]) != string::npos) {
            int pos = s.find(words[i]);
            cnt++;
            s.erase(pos, words[i].length());
            s.insert(pos, "-_-");
        }
    }
    
    // 根据阈值决定输出
    if (cnt >= k) {
        cout << cnt << endl << "He Xie Ni Quan Jia!";
    } else {
        // 将临时占位符替换为最终结果
        while (s.find("-_-") != string::npos) {
            int t = s.find("-_-");
            s.erase(t, 3);
            s.insert(t, "<censored>");
        }
        cout << s;
    }
    
    return 0;
}
