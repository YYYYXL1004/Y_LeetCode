/*
 * L1-059 敲笨钟
 * 
 * 题目描述：
 * 微博上有个自称"大笨钟V"的家伙，每天敲钟催促码农们爱惜身体早点睡觉。
 * 为了增加敲钟的趣味性，还会糟改几句古诗词。其糟改的方法为：
 * 去网上搜寻压"ong"韵的古诗词，把句尾的三个字换成"敲笨钟"。
 * 
 * 例如唐代诗人李贺有名句曰："寻章摘句老雕虫，晓月当帘挂玉弓"，
 * 其中"虫"（chong）和"弓"（gong）都压了"ong"韵。
 * 于是这句诗就被糟改为"寻章摘句老雕虫，晓月当帘敲笨钟"。
 * 
 * 输入格式：
 * 输入首先在第一行给出一个不超过 20 的正整数 N。
 * 随后 N 行，每行用汉语拼音给出一句古诗词，分上下两半句，用逗号 , 分隔，句号 . 结尾。
 * 相邻两字的拼音之间用一个空格分隔。
 * 题目保证每个字的拼音不超过 6 个字符，每行字符的总长度不超过 100，并且下半句诗至少有 3 个字。
 * 
 * 输出格式：
 * 对每一行诗句，判断其是否压"ong"韵。即上下两句末尾的字都是"ong"结尾。
 * 如果是压此韵的，就按题面方法糟改之后输出，输出格式同输入；
 * 否则输出 Skipped，即跳过此句。
 * 
 * 输入样例：
 * 5
 * xun zhang zhai ju lao diao chong, xiao yue dang lian gua yu gong.
 * tian sheng wo cai bi you yong, qian jin san jin huan fu lai.
 * xue zhui rou zhi leng wei rong, an xiao chen jing shu wei long.
 * zuo ye xing chen zuo ye feng, hua lou xi pan gui tang dong.
 * ren xian gui hua luo, ye jing chun shan kong.
 * 
 * 输出样例：
 * xun zhang zhai ju lao diao chong, xiao yue dang lian qiao ben zhong.
 * Skipped
 * xue zhui rou zhi leng wei rong, an xiao chen jing qiao ben zhong.
 * Skipped
 * Skipped
 * 
 * 解题思路：
 * 1. 判断上半句是否以"ong"结尾：检查逗号前三个字符是否为"ong"
 * 2. 判断下半句是否以"ong"结尾：检查句号前三个字符是否为"ong"
 * 3. 如果两句都押韵，保留上半句，下半句去掉最后三个字，换成"qiao ben zhong."
 * 4. 使用 stringstream 分割下半句的拼音，方便处理
 * 
 * 坑点：
 * - 下标从0开始，逗号位置为pos，所以逗号前三个字符是 s[pos-3], s[pos-2], s[pos-1]
 * - 句号在最后位置，所以句号前三个字符是 s[len-3], s[len-2], s[len-1]（len已减1）
 * - 输出格式：上半句末尾有逗号，下半句末尾有句号
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    string s;
    getchar();  // 吸收换行符
    
    while(N--) {
        getline(cin, s);
        
        // 找逗号位置
        size_t pos = s.find(',');
        
        // 判断逗号前是否是"ong"
        if(pos < 3) {
            cout << "Skipped" << endl;
            continue;
        }
        if(s[pos - 3] != 'o' || s[pos - 2] != 'n' || s[pos - 1] != 'g') {
            cout << "Skipped" << endl;
            continue;
        }
        
        // 判断句号前是否是"ong"
        int len = s.length() - 1;  // 去掉句号的位置
        if(s[len - 3] != 'o' || s[len - 2] != 'n' || s[len - 1] != 'g') {
            cout << "Skipped" << endl;
            continue;
        }
        
        // 押韵，进行替换
        string s1 = s.substr(0, pos + 1);  // 逗号前（含逗号）
        cout << s1 << " ";
        
        string s2 = s.substr(pos + 2, len - pos - 2);  // 逗号后到句号前
        stringstream ss(s2);
        vector<string> v;
        string vs;
        while(ss >> vs) {
            v.push_back(vs);
        }
        
        // 输出除最后三个字外的所有字
        for(int i = 0; i < v.size() - 3; i++) {
            cout << v[i] << " ";
        }
        cout << "qiao ben zhong." << endl;
    }
    
    return 0;
}
