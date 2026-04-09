/*
L2-016 愿天下有情人都是失散多年的兄妹
分数 25
作者 陈越
单位 浙江大学

呵呵。大家都知道五服以内不得通婚，即两个人最近的共同祖先如果在五代以内
（即本人、父母、祖父母、曾祖父母、高祖父母）则不可通婚。
本题就请你帮助一对有情人判断一下，他们究竟是否可以成婚？

输入格式：
输入第一行给出一个正整数 N（2 <= N <= 10^4），随后 N 行，每行按以下格式给出一个人的信息：

本人ID 性别 父亲ID 母亲ID

其中 ID 是 5 位数字，每人不同；性别 M 代表男性、F 代表女性。
如果某人的父亲或母亲已经不可考，则相应的 ID 位置上标记为 -1。

接下来给出一个正整数 K，随后 K 行，每行给出一对有情人的 ID，其间以空格分隔。

注意：题目保证两个人是同辈，每人只有一个性别，并且血缘关系网中没有乱伦或隔辈成婚的情况。

输出格式：
对每一对有情人，判断他们的关系是否可以通婚：
如果两人是同性，输出 Never Mind；
如果是异性并且关系出了五服，输出 Yes；
如果异性关系未出五服，输出 No。

输入样例：
24
00001 M 01111 -1
00002 F 02222 03333
00003 M 02222 03333
00004 F 04444 03333
00005 M 04444 05555
00006 F 04444 05555
00007 F 06666 07777
00008 M 06666 07777
00009 M 00001 00002
00010 M 00003 00006
00011 F 00005 00007
00012 F 00008 08888
00013 F 00009 00011
00014 M 00010 09999
00015 M 00010 09999
00016 M 10000 00012
00017 F -1 00012
00018 F 11000 00013
00019 F 11100 00018
00020 F 00015 11110
00021 M 11100 00020
00022 M 00016 -1
00023 M 10012 00017
00024 M 00022 10013
9
00021 00024
00019 00024
00011 00012
00022 00018
00001 00004
00013 00016
00017 00015
00019 00021
00010 00011

输出样例：
Never Mind
Yes
Never Mind
No
Yes
No
Yes
No
No
*/

// 方法一：
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005; // ID最大99999
vector<int> mp[MAXN];
unordered_map<int, char> fmp;

void dfs(int u, int p, int d, vector<int>& fa) { // 记录u的4辈
	if(d >= 4) return ; // d等于0时就计算父母这一辈了， 所以d=4时就可以退出啦
	for(int v : mp[u]) {
		if(v != p) {
			fa.push_back(v);
			dfs(v, u, d+1, fa);
		}
	}
}

int main() {
	int N;  cin>>N;
	int id, fa_id, ma_id;
	char fale;
	for(int i = 1; i <= N; i++) {
		cin>>id>>fale>>fa_id>>ma_id;
		fmp[id] = fale;
		if(fa_id != -1) { mp[id].push_back(fa_id); fmp[fa_id] = 'M'; }
		if(ma_id != -1) { mp[id].push_back(ma_id); fmp[ma_id] = 'F'; } //这么阴，还要手动添加父母性别
	}
	int K;  cin>>K;
	int u,v;
	while(K--) {
		cin>>u>>v;
		if(fmp[u] == fmp[v]) {
			cout<<"Never Mind"<<endl;
			continue;
		}
		vector<int> fa_u, fa_v; // u和v的4辈祖宗
		dfs(u, 0, 0, fa_u);
		dfs(v, 0, 0, fa_v);
		sort(fa_u.begin(), fa_u.end());
		sort(fa_v.begin(), fa_v.end());
		// 查是否有相同的元素
		int ul = 0, vl = 0;  // 双指针
		while(ul != (int)fa_u.size() && vl != (int)fa_v.size()) { // 注意这里的逻辑
			if(fa_u[ul] == fa_v[vl]) {
				cout<<"No"<<endl;
				break;
			} else if(fa_u[ul] > fa_v[vl]) {
				vl++;
			} else {
				ul++;
			}
		}
		if(ul == (int)fa_u.size() || vl == (int)fa_v.size()) cout<<"Yes"<<endl;
	}
	return 0;
}

// 方法二：
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005; // 修复1：ID最大99999，开10万
vector<int> mp[MAXN];    // 只存向上的边 (孩子 -> 父母)
char fmp[MAXN];          // 用数组存性别比 unordered_map 快得多
bool visited[MAXN];      // 记录祖先路径
bool has_common;         // 是否有公共祖先

// u: 当前节点, gen: 当前代数 (本人算第1代)
void dfs_u(int u, int gen) {
    if (gen > 5) return;  // 超过5服就不管了
    visited[u] = true;    // 走过的祖先打上标记 (包括自己)
    for (int p : mp[u]) {
        dfs_u(p, gen + 1);
    }
}

void dfs_v(int v, int gen) {
    if (gen > 5 || has_common) return; // 剪枝：如果已经找到了公共祖先，直接退出
    if (visited[v]) {     // 如果 v 走到过的节点被 u 走过，说明撞上了！
        has_common = true;
        return;
    }
    for (int p : mp[v]) {
        dfs_v(p, gen + 1);
    }
}

int main() {
    // 提速小技巧：关掉同步流
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    if (!(cin >> N)) return 0;
    
    int id, fa_id, ma_id;
    char gender;
    
    for (int i = 1; i <= N; i++) {
        cin >> id >> gender >> fa_id >> ma_id;
        fmp[id] = gender;
        
        if (fa_id != -1) {
            mp[id].push_back(fa_id);
            fmp[fa_id] = 'M'; // 修复5：隐式记录父亲性别
        }
        if (ma_id != -1) {
            mp[id].push_back(ma_id);
            fmp[ma_id] = 'F'; // 修复5：隐式记录母亲性别
        }
    }
    
    int K;
    cin >> K;
    int u, v;
    while (K--) {
        cin >> u >> v;
        
        // 1. 同性判断
        if (fmp[u] == fmp[v]) {
            cout << "Never Mind\n";
            continue;
        }
        
        // 2. 每次查询前，清空 visited 数组和标记
        fill(begin(visited), end(visited), false); // 或者用 memset(visited, 0, sizeof(visited));
        has_common = false;
        
        // 3. 开始搜索
        dfs_u(u, 1); // 本人算第 1 代
        dfs_v(v, 1);
        
        // 4. 修复4：输出逻辑
        if (has_common) {
            cout << "No\n";  // 有公共祖先，不能结婚
        } else {
            cout << "Yes\n"; // 出了五服，百年好合
        }
    }
    
    return 0;
}

// 【总结】
// 1. 题目本质：判断两人是否在五服内有共同祖先；同性直接 Never Mind，异性再判血缘。
// 2. 方法一（手写）：分别 DFS 收集双方祖先，再排序 + 双指针判交集，思路直观、易调试。
// 3. 方法二（优化）：先标记 u 的五服祖先，再 DFS v 时在线检测 visited，省去排序与数组合并，更高效。
// 4. 正确性依据：只要 v 的追溯路径上碰到 u 已标记的节点，即存在五服内共同祖先，答案为 No；否则 Yes。
// 5. 复杂度对比：
//    - 方法一：单次查询约 O(A log A + B log B)（主要在排序）
//    - 方法二：单次查询约 O(A + B)，整体更优，适合查询较多时使用。
// 6. 易错点：
//    - 代数边界统一（本人算第 1 代时，需搜索到第 5 代）
//    - 父母可能未单独出现在输入里，也要补记录性别
//    - 每次查询前必须清空 visited / has_common，避免上一次查询污染结果。
