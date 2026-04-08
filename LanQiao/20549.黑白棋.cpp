// #include <bits/stdc++.h>
// using namespace std;

// int a[6][6] = {
//     { 1,  0,  1,  0, -1, -1},
//     {-1, -1, -1,  0, -1, -1},
//     {-1, -1, -1,  1,  0,  0},
//     {-1, -1, -1, -1, -1, -1},
//     {-1, -1,  1, -1, -1,  1},
//     {-1,  0, -1, -1,  1, -1}
// };

// vector<pair<int, int>> pos;
// string ans;

// bool check() {
//     // 检查每一行：黑白数量都不能超过 3，且不能出现三个连续相同颜色
//     for (int i = 0; i < 6; i++) {
//         int c0 = 0, c1 = 0, e = 0;
//         for (int j = 0; j < 6; j++) {
//             if (a[i][j] == 0) c0++;
//             else if (a[i][j] == 1) c1++;
//             else e++;
//         }
//         if (c0 > 3 || c1 > 3 || c0 + e < 3 || c1 + e < 3) return false;
//         for (int j = 0; j < 4; j++) {
//             if (a[i][j] != -1 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2]) {
//                 return false;
//             }
//         }
//     }

//     // 检查每一列
//     for (int j = 0; j < 6; j++) {
//         int c0 = 0, c1 = 0, e = 0;
//         for (int i = 0; i < 6; i++) {
//             if (a[i][j] == 0) c0++;
//             else if (a[i][j] == 1) c1++;
//             else e++;
//         }
//         if (c0 > 3 || c1 > 3 || c0 + e < 3 || c1 + e < 3) return false;
//         for (int i = 0; i < 4; i++) {
//             if (a[i][j] != -1 && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j]) {
//                 return false;
//             }
//         }
//     }

//     // 已经填满的两行不能完全相同
//     for (int i = 0; i < 6; i++) {
//         for (int j = i + 1; j < 6; j++) {
//             bool full1 = true, full2 = true, same = true;
//             for (int k = 0; k < 6; k++) {
//                 if (a[i][k] == -1) full1 = false;
//                 if (a[j][k] == -1) full2 = false;
//                 if (a[i][k] != a[j][k]) same = false;
//             }
//             if (full1 && full2 && same) return false;
//         }
//     }

//     // 已经填满的两列不能完全相同
//     for (int i = 0; i < 6; i++) {
//         for (int j = i + 1; j < 6; j++) {
//             bool full1 = true, full2 = true, same = true;
//             for (int k = 0; k < 6; k++) {
//                 if (a[k][i] == -1) full1 = false;
//                 if (a[k][j] == -1) full2 = false;
//                 if (a[k][i] != a[k][j]) same = false;
//             }
//             if (full1 && full2 && same) return false;
//         }
//     }

//     return true;
// }

// bool dfs(int u) {
//     if (!check()) return false;

//     // 空位全部填完，直接拼接答案
//     if (u == pos.size()) {
//         ans.clear();
//         for (int i = 0; i < 6; i++) {
//             for (int j = 0; j < 6; j++) {
//                 ans += char(a[i][j] + '0');
//             }
//         }
//         return true;
//     }

//     int x = pos[u].first, y = pos[u].second;
//     // 枚举当前位置填 0 或 1
//     for (int v = 0; v <= 1; v++) {
//         a[x][y] = v;
//         if (dfs(u + 1)) return true;
//     }
//     a[x][y] = -1;
//     return false;
// }

// int main() {
//     // 记录所有空位，按顺序回溯填数
//     for (int i = 0; i < 6; i++) {
//         for (int j = 0; j < 6; j++) {
//             if (a[i][j] == -1) pos.push_back({i, j});
//         }
//     }
//     dfs(0);
//     cout << ans << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mp = {
    { 1,  0,  1,  0, -1, -1},
    {-1, -1, -1,  0, -1, -1},
    {-1, -1, -1,  1,  0,  0},
    {-1, -1, -1, -1, -1, -1},
    {-1, -1,  1, -1, -1,  1},
    {-1,  0, -1, -1,  1, -1}
};

// 检查当前填入后，第 r 行和第 c 列是否仍然合法
bool isValid(int r, int c) {
    int countRow[2] = {0, 0};
    int countCol[2] = {0, 0};

    for (int i = 0; i < 6; i++) {
        if (mp[r][i] != -1) countRow[mp[r][i]]++;
        if (mp[i][c] != -1) countCol[mp[i][c]]++;

        if (i >= 2 && mp[r][i] != -1 && mp[r][i - 1] == mp[r][i] && mp[r][i - 2] == mp[r][i]) {
            return false;
        }
        if (i >= 2 && mp[i][c] != -1 && mp[i - 1][c] == mp[i][c] && mp[i - 2][c] == mp[i][c]) {
            return false;
        }
    }

    if (countRow[0] > 3 || countRow[1] > 3) return false;
    if (countCol[0] > 3 || countCol[1] > 3) return false;

    return true;
}

// 最终检查所有行、列是否互不相同
bool checkUnique() {
    set<string> rows, cols;
    for (int i = 0; i < 6; i++) {
        string r_str, c_str;
        for (int j = 0; j < 6; j++) {
            r_str += char(mp[i][j] + '0');
            c_str += char(mp[j][i] + '0');
        }
        if (rows.count(r_str) || cols.count(c_str)) return false;
        rows.insert(r_str);
        cols.insert(c_str);
    }
    return true;
}

bool dfs(int r, int c) {
    if (r == 6) return checkUnique();

    int next_r = (c == 5 ? r + 1 : r);
    int next_c = (c == 5 ? 0 : c + 1);

    if (mp[r][c] != -1) return dfs(next_r, next_c);

    for (int val = 0; val <= 1; val++) {
        mp[r][c] = val;
        if (isValid(r, c) && dfs(next_r, next_c)) return true;
        mp[r][c] = -1;
    }
    return false;
}

int main() {
    if (dfs(0, 0)) {
        string res;
        for (const auto& row : mp) {
            for (int val : row) {
                res += char(val + '0');
            }
        }
        cout << res << endl;
    }
    return 0;
}
