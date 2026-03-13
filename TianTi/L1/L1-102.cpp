/*
 * L1-102 数独检验
 * 
 * 题目描述：
 * 游戏规则是：将一个 9×9 的正方形区域划分为 9 个 3×3 的正方形宫位，
 * 要求 1 到 9 这九个数字中的每个数字在每一行、每一列、每个宫位中都只能出现一次。
 * 本题并不要求你写程序解决这个问题，只是对每个填好数字的九宫格，
 * 判断其是否满足游戏规则的要求。
 * 
 * 输入格式：
 * 输入首先在第一行给出一个正整数 n（≤10），随后给出 n 个填好数字的九宫格。
 * 每个九宫格分 9 行给出，每行给出 9 个数字，其间以空格分隔。
 * 
 * 输出格式：
 * 对每个给定的九宫格，判断其中的数字是否满足游戏规则的要求。
 * 满足则在一行中输出 1，否则输出 0。
 * 
 * 输入样例：
 * 3
 * 5 1 9 2 8 3 4 6 7
 * 7 2 8 9 6 4 3 5 1
 * 3 4 6 5 7 1 9 2 8
 * 8 9 2 1 4 5 7 3 6
 * 4 7 3 6 2 8 1 9 5
 * 6 5 1 7 3 9 2 8 4
 * 9 3 4 8 1 6 5 7 2
 * 1 6 7 3 5 2 8 4 9
 * 2 8 5 4 9 7 6 1 3
 * 8 2 5 4 9 7 1 3 6
 * 7 9 6 5 1 3 8 2 4
 * 3 4 1 6 8 2 7 9 5
 * 6 8 4 2 7 1 3 5 9
 * 9 1 2 8 3 5 6 4 7
 * 5 3 7 9 6 4 2 1 8
 * 2 7 9 1 5 8 4 6 3
 * 4 5 8 3 2 6 9 7 1
 * 1 6 3 7 4 9 5 8 3
 * 81 2 5 4 9 7 1 3 6
 * 7 9 6 5 1 3 8 2 4
 * 3 4 1 6 8 2 7 9 5
 * 6 8 4 2 7 1 3 5 9
 * 9 1 2 8 3 5 6 4 7
 * 5 3 7 9 6 4 2 1 8
 * 2 7 9 1 5 8 4 6 3
 * 4 5 8 3 2 6 9 7 1
 * 1 6 3 7 4 9 5 8 2
 * 
 * 输出样例：
 * 1
 * 0
 * 0
 * 
 * 解题思路：
 * 1. 检查数字范围是否在 1-9 内（坑点：样例中有81这种超范围数字）
 * 2. 检查每一行是否有重复数字
 * 3. 检查每一列是否有重复数字
 * 4. 检查每个 3×3 宫位是否有重复数字
 * 使用 set 来判断是否有重复
 */

#include <iostream>
#include <set>
using namespace std;

int mp[9][9];

// 检查以 (ii, jj) 为左上角的 3×3 宫格是否合法
bool isxiaomp(int ii, int jj) {
    set<int> s;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s.count(mp[ii + i][jj + j])) return false;
            s.insert(mp[ii + i][jj + j]);
        }
    }
    return true;
}

// 检查整个九宫格是否合法
bool ismp() {
    // 判断每一行是否符合
    for (int i = 0; i < 9; i++) {
        set<int> s;
        for (int j = 0; j < 9; j++) {
            if (s.count(mp[i][j])) return false;
            s.insert(mp[i][j]);
        }
    }
    
    // 判断每一列是否符合
    for (int i = 0; i < 9; i++) {
        set<int> s;
        for (int j = 0; j < 9; j++) {
            if (s.count(mp[j][i])) return false;
            s.insert(mp[j][i]);
        }
    }
    
    // 判断每个 3×3 宫格
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!isxiaomp(i, j)) return false;
        }
    }
    
    return true;
}

int main() {
    int n;
    cin >> n;
    
    while (n--) {
        bool is = true;
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> mp[i][j];
                // 注意：数独数字范围是 1-9，不是 0-9！
                if (mp[i][j] < 1 || mp[i][j] > 9) {
                    is = false;
                }
            }
        }
        
        if (!is) cout << 0 << endl;
        else if (ismp()) cout << 1 << endl;
        else cout << 0 << endl;
    }
    
    return 0;
}
