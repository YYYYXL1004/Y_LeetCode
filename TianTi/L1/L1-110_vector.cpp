#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    
    while (M--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            // 查找并替换
            int L1;
            cin >> L1;
            vector<int> target(L1);
            for (int i = 0; i < L1; i++) {
                cin >> target[i];
            }
            
            int L2;
            cin >> L2;
            vector<int> replacement(L2);
            for (int i = 0; i < L2; i++) {
                cin >> replacement[i];
            }
            
            // 在 a 中查找 target 第一次出现的位置
            int pos = -1;
            for (int i = 0; i + L1 <= (int)a.size(); i++) {
                bool match = true;
                for (int j = 0; j < L1; j++) {
                    if (a[i + j] != target[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    pos = i;
                    break;
                }
            }
            
            if (pos != -1) {
                // 替换：删除 [pos, pos+L1-1]，插入 replacement
                a.erase(a.begin() + pos, a.begin() + pos + L1);
                a.insert(a.begin() + pos, replacement.begin(), replacement.end());
            }
            
        } else if (op == 2) {
            // 在相邻和为偶数的元素间插入平均数
            // 从后往前处理，避免下标混乱
            for (int i = (int)a.size() - 2; i >= 0; i--) {
                if ((a[i] + a[i + 1]) % 2 == 0) {
                    int avg = (a[i] + a[i + 1]) / 2;
                    a.insert(a.begin() + i + 1, avg);
                }
            }
            
        } else {  // op == 3
            // 翻转 [l, r] 区间（1-based）
            int l, r;
            cin >> l >> r;
            // 转换为 0-based
            l--;
            r--;
            reverse(a.begin() + l, a.begin() + r + 1);
        }
    }
    
    // 输出结果
    for (int i = 0; i < (int)a.size(); i++) {
        if (i != 0) cout << " ";
        cout << a[i];
    }
    
    return 0;
}

/*
 * ==================== vector 常用函数速查 ====================
 * 
 * 【1. 访问元素】
 *     a[i]                  // 下标访问（不检查越界）
 *     a.at(i)               // 下标访问（检查越界，越界抛异常）
 *     a.front()             // 返回第一个元素
 *     a.back()              // 返回最后一个元素
 *     
 * 【2. 插入 insert】（会改变原容器！）
 *     a.insert(a.begin() + 2, 5);              // 在下标2处插入元素5
 *     a.insert(a.begin() + 2, 3, 5);           // 在下标2处插入3个元素5
 *     a.insert(a.begin() + 2, b.begin(), b.end());  // 在下标2处插入另一个vector的所有元素
 *     
 * 【3. 删除 erase】（会改变原容器！）
 *     a.erase(a.begin() + 2);                  // 删除下标2的元素
 *     a.erase(a.begin() + 2, a.begin() + 5);   // 删除[2,5)区间的元素
 *     
 * 【4. 添加/删除末尾元素】
 *     a.push_back(5);          // 末尾添加元素
 *     a.pop_back();            // 删除末尾元素
 *     
 * 【5. 大小相关】
 *     a.size()                 // 返回元素个数
 *     a.empty()                // 判断是否为空
 *     a.clear()                // 清空所有元素
 *     a.resize(10);            // 调整大小为10（多补默认值，少删末尾）
 *     a.resize(10, 5);         // 调整大小为10，多补元素5
 *     
 * 【6. 查找元素】（需要 #include<algorithm>）
 *     find(a.begin(), a.end(), 5);    // 返回迭代器，找不到返回 a.end()
 *     auto it = find(a.begin(), a.end(), 5);
 *     if (it != a.end()) { 找到了，下标 = it - a.begin(); }
 *     
 * 【7. 翻转 reverse】（需要 #include<algorithm>）
 *     reverse(a.begin(), a.end());              // 翻转整个vector
 *     reverse(a.begin() + 2, a.begin() + 5);    // 翻转[2,5)区间
 *     
 * 【8. 排序 sort】（需要 #include<algorithm>）
 *     sort(a.begin(), a.end());                 // 升序排序
 *     sort(a.begin(), a.end(), greater<int>()); // 降序排序
 *     sort(a.begin(), a.end(), [](int x, int y){ return x > y; }); // 降序（lambda）
 *     
 * 【9. 去重 unique】（需要先排序！）
 *     sort(a.begin(), a.end());
 *     a.erase(unique(a.begin(), a.end()), a.end());  // 先排序再去重
 *     
 * 【10. 迭代器与下标转换】
 *     下标转迭代器：a.begin() + i
 *     迭代器转下标：it - a.begin()
 *     
 * 【11. 常见坑】
 *     (1) 所有下标从0开始！
 *     (2) erase/insert 后迭代器可能失效，遍历时删除要小心
 *         错误示例：for(auto it = a.begin(); it != a.end(); it++) { a.erase(it); }
 *         正确做法：for(auto it = a.begin(); it != a.end(); ) {
 *                      if(条件) it = a.erase(it);  // erase返回下一个有效迭代器
 *                      else it++;
 *                  }
 *     (3) reverse/sort 等算法是左闭右开区间 [begin, end)
 */
