/*
 * XB-L1-8 网校课程学习
 * 
 * 题目描述：
 * 网校共开设 n 类课程，编号依次为 1,2,⋯,n。
 * 学员按照课程 1,2,⋯,n 的顺序学完课程。
 * 学习讲究循序渐进，在前一个课程学完前，不能开始下一个课程的学习。
 * 
 * 规则：
 * - 必须按顺序学习：课程1 → 课程2 → ... → 课程n
 * - 在任意一天，只能属于一个班级
 * - 前一个课程结束后，才能开始下一个课程（不能在同一天）
 * 
 * 输入格式：
 * 第一行 n, m（课程数和天数）
 * 接下来 n 行，每行描述一个课程：
 * - 第一个整数 ci 表示班级数目
 * - 接下来 2*ci 个整数，每两个描述一个班级的 开始时间 和 结束时间
 * 
 * 输出格式：
 * 最早结束全部课程的天数，无法完成输出 -1
 * 
 * 样例1：
 * 输入：4 20
 *       4 1 3 5 7 9 11 16 18
 *       4 2 4 6 7 7 9 11 16
 *       4 4 5 7 8 10 11 17 18
 *       4 2 4 6 8 13 15 18 19
 * 输出：15
 * 
 * 样例2：
 * 输入：4 15
 *       2 1 2 10 12
 *       1 11 14
 *       1 15 15
 *       1 15 15
 * 输出：-1
 * 
 * 解题思路：
 * 贪心策略：对于每个课程，选择"开始时间 > 前一个课程结束时间"的班级中，
 * 结束时间最早的那个。
 * 
 * 状态转移：
 * - ed[i] = 第 i 个课程的最早结束时间
 * - 对于课程 i，遍历所有班级：
 *   - 如果 s > ed[i-1]，说明可以选这个班级
 *   - 在所有可选班级中，选结束时间最早的
 * 
 * 注意事项：
 * - 本题数据量大（n≤10^6, Σci≤3×10^6），需要快读
 * - 不保证班级按时间顺序给出，需要遍历所有班级找最优解
 */

#include<iostream>
#include<unordered_map>
#include<climits>
using namespace std;

/*
 * ==================== 方法一：unordered_map 版本 ====================
 * 
 * 用 unordered_map 存储每个课程的最早结束时间
 * 查找复杂度 O(1)，比 map 的 O(log n) 更快
 * 
 * 空间复杂度：O(n)
 */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    unordered_map<int, int> ed;  // 课程i -> 最早结束时间
    
    // 课程1：选择结束时间最早的班级
    int c;
    cin >> c;
    
    int min_end = INT_MAX;
    for(int j = 1; j <= c; j++) {
        int s, e;
        cin >> s >> e;
        min_end = min(min_end, e);
    }
    ed[1] = min_end;
    
    if(n == 1) {
        cout << ed[1];
        return 0;
    }
    
    // 课程 2 到 n
    for(int i = 2; i <= n; i++) {
        int c;
        cin >> c;
        
        min_end = INT_MAX;
        for(int j = 1; j <= c; j++) {
            int s, e;
            cin >> s >> e;
            // 必须在前一个课程结束后才能开始（严格大于）
            if(s > ed[i - 1]) {
                min_end = min(min_end, e);
            }
        }
        
        // 没有可选的班级
        if(min_end == INT_MAX) {
            cout << -1;
            return 0;
        }
        
        ed[i] = min_end;
    }
    
    cout << ed[n];
    
    return 0;
}

/*
 * ==================== 方法二：滚动变量版本（更优） ====================
 * 
 * 用一个变量 prev_end 滚动更新，不需要存储所有课程的结果
 * 
 * 空间复杂度：O(1)
 * 
 * int main() {
 *     ios::sync_with_stdio(0);
 *     cin.tie(0);
 *     cout.tie(0);
 *     
 *     int n, m;
 *     cin >> n >> m;
 *     
 *     // 课程1：选择结束时间最早的班级
 *     int c;
 *     cin >> c;
 *     
 *     int min_end = INT_MAX;
 *     for(int j = 1; j <= c; j++) {
 *         int s, e;
 *         cin >> s >> e;
 *         min_end = min(min_end, e);
 *     }
 *     int prev_end = min_end;  // 前一个课程的最早结束时间
 *     
 *     if(n == 1) {
 *         cout << prev_end;
 *         return 0;
 *     }
 *     
 *     // 课程 2 到 n
 *     for(int i = 2; i <= n; i++) {
 *         int c;
 *         cin >> c;
 *         
 *         min_end = INT_MAX;
 *         for(int j = 1; j <= c; j++) {
 *             int s, e;
 *             cin >> s >> e;
 *             // 必须在前一个课程结束后才能开始（严格大于）
 *             if(s > prev_end) {
 *                 min_end = min(min_end, e);
 *             }
 *         }
 *         
 *         // 没有可选的班级
 *         if(min_end == INT_MAX) {
 *             cout << -1;
 *             return 0;
 *         }
 *         
 *         prev_end = min_end;
 *     }
 *     
 *     cout << prev_end;
 *     
 *     return 0;
 * }
 */

/*
 * ==================== 知识点总结 ====================
 * 
 * 1. 贪心策略：
 *    - 每一步选择"当前最优"：结束时间最早的班级
 *    - 这样能给后续课程留出最多的时间
 * 
 * 2. 快读技巧：
 *    - ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 *    - 数据量大时必须使用，否则会 TLE
 * 
 * 3. 题目坑点：
 *    - "前一个课程结束后才能开始"是严格大于（>），不是 >=
 *    - 班级时间不保证有序，需要遍历所有班级
 * 
 * 4. map vs unordered_map vs 滚动变量：
 *    | 方式 | 查找复杂度 | 空间复杂度 | 适用场景 |
 *    |------|-----------|-----------|----------|
 *    | map | O(log n) | O(n) | 需要有序遍历 |
 *    | unordered_map | O(1) | O(n) | 需要快速查找 |
 *    | 滚动变量 | O(1) | O(1) | 只需要前一个状态 |
 * 
 * 5. 为什么滚动变量更优？
 *    - ed[i] 只在计算 ed[i+1] 时用一次，不需要存储所有历史
 *    - 用一个变量 prev_end 滚动更新即可，空间 O(1)
 */
