/*
L1-009 N个数求和

分数 20

本题的要求很简单，就是求N个数字的和。麻烦的是，这些数字是以有理数分子/分母的形式给出的，
你输出的和也必须是有理数的形式。

输入格式：
输入第一行给出一个正整数N（≤100）。随后一行按格式a1/b1 a2/b2 ...给出N个有理数。
题目保证所有分子和分母都在长整型范围内。另外，负数的符号一定出现在分子前面。

输出格式：
输出上述数字和的最简形式 —— 即将结果写成整数部分 分数部分，其中分数部分写成分子/分母，
要求分子小于分母，且它们没有公因子。如果结果的整数部分为0，则只输出分数部分。

输入样例1：
5
2/5 4/15 1/30 -2/60 8/3

输出样例1：
3 1/3

输入样例2：
2
4/3 2/3

输出样例2：
2

输入样例3：
3
1/3 -1/6 1/8

输出样例3：
7/24
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;  cin>>n;
    long long x_sum = 0;
    long long y_sum = 1;
    while(n--) {
        string s; cin>>s;
        long long x, y;
        // 解析
        int index = s.find('/');
        if(s[0] == '-') x = -stoll(s.substr(1, index - 1));
        else x = stoll(s.substr(0, index));
        y = stoi(s.substr(index + 1, s.length() - index - 1));
        // 约分
        long long g = __gcd(x, y);
        x /= g; y /= g;
        // 求和并约分
        long long gongbei = (y_sum * y) / __gcd(y, y_sum); //最小公倍数
        x_sum = x_sum * (gongbei / y_sum) + x * (gongbei / y); //计算分子和
        y_sum = gongbei;
        long long gg = __gcd(x_sum, y_sum);
        x_sum /= gg, y_sum /= gg;
    }
    bool is_fu = false;
    if(x_sum < 0) {
        is_fu = true;
        x_sum = -x_sum;
    }
    long long zheng = x_sum / y_sum;
    long long yu = x_sum - zheng * y_sum;
    
    if(is_fu) cout<<"-";
    if(yu ==0) cout<<zheng;
    else if(zheng == 0) cout<<yu<<"/"<<y_sum;
    else cout<<zheng<<" "<<yu<<"/"<<y_sum;
    return 0;
}

/*
【核心思路与讲解】

一、问题的本质
多个有理数（分数）求和，需要：
1. 解析每个分数的分子和分母
2. 通分后相加
3. 输出最简形式（带分数或真分数）

二、关键步骤

1. 分数解析
   - 使用 find('/') 找到分号位置
   - 注意负数：负号一定在分子前面，所以要先判断第一个字符是否为 '-'
   - 使用 stoi 将字符串转为整数

2. 通分求和
   - 先对当前分数化简（用 __gcd 求最大公约数）
   - 求两个分母的最小公倍数：LCM(a,b) = a*b / GCD(a,b)
   - 通分后分子相加

3. 每次累加后化简
   - 防止分子分母溢出
   - 用 __gcd 求最大公约数后约分

4. 输出格式处理
   - 分离整数部分和分数部分
   - 处理负数情况
   - 根据不同情况输出：
     * 余数为0：只输出整数部分
     * 整数部分为0：只输出分数部分
     * 否则：输出 "整数 分子/分母"

三、注意事项

1. 数据范围：使用 long long 防止溢出
2. 负数处理：负号在分子上，输出时要单独处理
3. 每次运算后及时约分，防止中间结果溢出

四、时间复杂度
O(N * log(max值))，主要是求 GCD 的时间

五、易错点

1. stoi 的范围有限，对于"长整型范围内"的数可能需要用 stoll
2. 通分时分子也要乘以相应的系数
3. 输出时要判断各种特殊情况
*/
