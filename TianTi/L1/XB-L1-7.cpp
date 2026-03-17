/*
 * XB-L1-7 PION5202 的选手代码
 * 
 * 题目描述：
 * PION5202 的选手代码公布了。判断每位选手是哪类人：
 * 
 * 三类选手：
 * 1. 普通人：所有题目的 freopen 语句都正确
 *    freopen("<title>.in","r",stdin);
 *    freopen("<title>.out","w",stdout);
 * 
 * 2. 见祖宗人：至少有一行语句以 //freopen 开头，以 ); 结尾
 * 
 * 3. 乐子人：不满足上面两种情况
 * 
 * 判断顺序：
 * - 先检查是否是见祖宗人（只要有注释的 freopen 就算）
 * - 再检查是否是普通人（所有题目都正确）
 * - 否则是乐子人
 * 
 * 输入格式：
 * 第一行 n, m（选手数和题目数）
 * 接下来 m 行，每行一个题目名称
 * 接下来 n×(2m+1) 行，每位选手的 freopen 语句
 * 
 * 输出格式：
 * 普通人：PION5202 RP++.
 * 见祖宗人：Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.
 * 乐子人：Good luck and have fun.
 * 
 * 坑点：
 * 1. getline 末尾可能有 '\r'，需要忽略
 * 2. 见祖宗人的条件：以 "//freopen" 开头，以 ");" 结尾
 * 3. 判断顺序：先见祖宗人，再普通人，最后乐子人
 * 4. 普通人要求所有题目都完全正确
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<string> ti(m + 1);
    for(int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        ti[i] = s;
    }
    getchar();  // 吸收换行
    
    for(int i = 1; i <= n; i++) {
        bool isAncestor = false;  // 见祖宗人
        int cnt = 0;  // 正确题目数
        
        getchar();  // 吸收空行
        
        for(int j = 1; j <= m; j++) {
            string s1, s2;
            getline(cin, s1);
            getline(cin, s2);
            
            // 注意：如果本地 Windows 测试有问题，可能需要处理 '\r'
            // if(!s1.empty() && s1.back() == '\r') s1.pop_back();
            // if(!s2.empty() && s2.back() == '\r') s2.pop_back();
            
            // 检查是否是见祖宗人：以 "//freopen" 开头，以 ");" 结尾
            if(s1.length() >= 11 && s1.substr(0, 9) == "//freopen" && s1.substr(s1.length() - 2) == ");") {
                isAncestor = true;
                continue;
            }
            if(s2.length() >= 11 && s2.substr(0, 9) == "//freopen" && s2.substr(s2.length() - 2) == ");") {
                isAncestor = true;
                continue;
            }
            
            // 构造正确的 freopen 语句 注意转义字符的使用
            string t1 = "freopen(\"" + ti[j] + ".in\",\"r\",stdin);";
            string t2 = "freopen(\"" + ti[j] + ".out\",\"w\",stdout);";
            
            // 检查是否完全匹配
            if(t1 == s1 && t2 == s2) {
                cnt++;
            }
        }
        
        // 输出结果（判断顺序很重要！）
        if(isAncestor) {
            cout << "Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI." << endl;
        } else if(cnt == m) {
            cout << "PION5202 RP++." << endl;
        } else {
            cout << "Good luck and have fun." << endl;
        }
    }
    
    return 0;
}

/*
 * ==================== 知识点总结 ====================
 * 
 * 1. getline 读入问题：
 *    - Windows 下换行是 \r\n，getline 可能读到 \r
 *    - 处理方法：if(s.back() == '\r') s.pop_back();
 * 
 * 2. 字符串匹配：
 *    - substr(pos, len) 从 pos 开始截取 len 个字符
 *    - substr(pos) 从 pos 截取到末尾
 *    - 注意：s.substr(s.length() - 2) 截取最后 2 个字符
 * 
 * 3. 判断顺序：
 *    - 先判断见祖宗人（最特殊的条件）
 *    - 再判断普通人（要求全部正确）
 *    - 最后是乐子人（兜底）
 * 
 * 4. 字符串拼接：
 *    - "freopen(\"" + ti[j] + ".in\",\"r\",stdin);"
 *    - 注意转义引号 \"
 */
