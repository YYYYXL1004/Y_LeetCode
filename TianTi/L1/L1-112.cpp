/*
 * L1-112 现代战争
 * 
 * 题目描述：
 * 在最新的《命运召唤：现代战争》中，你要扮演 B 国的一名战斗机飞行员，
 * 前往轰炸 A 国的高价值建筑。A 国的建筑群可视为一个由 n×m 个小方格组成的地图，
 * 每个小方格中有一幢建筑，并且你已经知道了所有建筑的价值。
 * 
 * 作为一名优秀的战斗机飞行员，你打算轰炸 k 幢建筑，轰炸方式是：
 * 你选择当前所有还存在的建筑里最高价值的一幢投下炸弹，
 * 这个炸弹会将这个建筑所在的一整行和一整列都炸平。
 * 随后系统将彻底抹除被炸平的建筑，将剩下的地块合并成 (n−1)×(m−1) 的地图。
 * 
 * 输入格式：
 * 输入第一行给出三个正整数 n、m（2≤n,m≤1000）和 k（<min{n,m}），
 * 依次对应地图中建筑的行数、列数，以及轰炸步数。
 * 随后 n 行，每行 m 个整数，为地图中对应建筑的价值。
 * 题目保证所有元素在 [−2^30, 2^30] 区间内，且互不相等。同行数字间以空格分隔。
 * 
 * 输出格式：
 * 输出轰炸 k 幢建筑后的地图。同行数字间以 1 个空格分隔，行首尾不得有多余空格。
 * 
 * 输入样例：
 * 4 5 2
 * 3 8 6 1 10
 * 28 9 21 37 5
 * 4 11 7 25 18
 * 15 23 2 17 14
 * 
 * 输出样例：
 * 3 6 10
 * 4 7 18
 * 
 * 解题思路：
 * 1. 用优先队列（大根堆）存储所有建筑的价值和坐标
 * 2. 每次取出最大值，标记其所在行和列为已删除
 * 3. 如果该行或列已被删除，则跳过（因为该建筑已在之前的轰炸中被删除）
 * 4. 最后输出未被删除的行列中的元素
 * 
 * 注意：
 * - 数据范围是 [−2^30, 2^30]，需要用 long long
 * - 要处理"延迟删除"的情况：优先队列中可能包含已删除行列中的元素
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, k;
long long mp[1005][1005];
bool row_de[1005];  // 标记行是否被删除
bool col_de[1005];  // 标记列是否被删除

struct st {
    long long num;
    int row, col;
    st(long long num, int row, int col) : num(num), row(row), col(col) {}
};

// 大根堆比较器：大的先出
auto cmp = [](st a, st b) {
    return a.num < b.num;
};

priority_queue<st, vector<st>, decltype(cmp)> pq(cmp);

int main() {
    cin >> n >> m >> k;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mp[i][j];
            pq.emplace(st(mp[i][j], i, j));
        }
    }
    
    // 找出前 k 个最大值的建筑并删除其所在行列
    int count = 0;
    while (count < k && !pq.empty()) {
        st cur = pq.top();
        pq.pop();
        
        int r = cur.row;
        int c = cur.col;
        
        // 如果这个元素所在行或列已经删除，跳过（延迟删除）
        if (row_de[r] || col_de[c]) {
            continue;
        }
        
        row_de[r] = true;
        col_de[c] = true;
        count++;
    }
    
    // 输出未被删除的行列
    bool first_in_row = true;
    for (int i = 0; i < n; i++) {
        if (row_de[i]) continue;
        
        first_in_row = true;
        for (int j = 0; j < m; j++) {
            if (col_de[j]) continue;
            
            if (!first_in_row) cout << " ";
            cout << mp[i][j];
            first_in_row = false;
        }
        cout << endl;
    }
    
    return 0;
}
