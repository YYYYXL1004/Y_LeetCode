/*
题目背景
一幅长宽分别为 n 个像素和 m 个像素的灰度图像可以表示为一个 n×m 大小的矩阵 A。
其中每个元素 A[i,j] (1<=i<=n, 1<=j<=m) 是一个 [0, L-1] 范围内的整数，表示对应位置像素的灰度值。
具体来说，一个 8 比特的灰度图像中每个像素的灰度范围是 [0, 255]。

题目描述
选定阈值 k 后将图像二值化：
1) 灰度值 >= k 的像素变为白色；
2) 灰度值 <  k 的像素变为黑色。
然后检查图像中是否存在一个 5×9 的子矩阵，其黑白分布与“CSP”字母形状完全一致（图略）。
不考虑旋转、翻转等复杂情况。

对于给定的 n×n 灰度图像 A，计算所有能检测出水印 CSP 的阈值 k。

输入格式
第一行包含两个正整数 n 和 L，表示图像大小和像素灰度范围。
接下来 n 行，每行 n 个整数，为矩阵 A。

输出格式
输出若干行，每行一个整数，表示可检测出水印 CSP 的阈值 k。
[0, L-1] 范围内所有可行阈值 k 按从小到大顺序输出。

输入数据 1
9 256
9 9 8 8 9 9 9 8 255
9 0 0 8 0 0 7 0 8
9 0 0 8 7 9 7 7 5
9 0 0 0 0 8 7 0 0
7 7 8 7 7 8 8 6 5
6 2 2 5 1 1 5 1 6
6 2 2 6 6 6 7 5 3
6 2 2 2 1 5 8 1 1
7 7 8 7 7 8 8 2 3

输出数据 1
4
5
7

样例说明
k=4 或 k=5 时水印出现在后五行；k=7 时水印出现在前五行。

数据范围
9<=n<=200, L in {256, 65536}，像素值均在 [0, L-1]，且保证至少存在一个阈值可检测水印。
*/
// 方法一：对与每一个k,遍历全图  O(L*N*2)只能过（80/100） 
//#include<bits/stdc++.h>
//using namespace std;
//#define debug(x) cout<<#x<<" "<<x<<"\n"
//
//vector<vector<int>> mp;
//int n, L;
//
//int mmp[4][8] = {{0, 0, 1, 0, 0, 1, 0, 1}, 
//			   {0, 0, 1, 1, 1, 1, 1, 0},
//			   {0, 0, 0, 0, 1, 1, 0, 0},
//			   {1, 1, 1, 1, 1, 1, 0, 0}};   
//
//bool check(int k, int x, int y) {
//	for(int i = y; i < y + 9; i++) { // 第一行必须全是 >= k
//		if(mp[x][i] < k)  return false;
//	}
//	for(int i = x; i < x + 5; i++) { // 第一列也必须全是 >= k
//		if(mp[i][y] < k)  return false;
//	}
//	for(int i = x+1; i < x+5; i++) {
//		for(int j = y +1; j < y + 9; j++) {
//			// 剩下的 4 * 8的矩阵每一个都要匹配
//			int tmp = mp[i][j] >= k ? 1 : 0;
//			if(mmp[i-(x+1)][j-(y+1)] != tmp) {
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin>>n>>L;
//	mp.assign(n, vector<int>(n));
//	for(int i = 0; i < n; i++) {
//		for(int j = 0;j < n; j++) {
//			cin>>mp[i][j];
//		}
//	}
//	for(int k = 1; k < L; k++) {
//		bool found = false;
//		for(int i = 0; i <= n-5; i++) {
//			for(int j = 0; j <= n-9; j++) {
//				if(check(k, i, j)) {
//					cout<<k<<"\n";
//					found = true;
//					break;
//				}
//			}
//			if(found) break;
//		}
//	}
//	return 0;
//}

// 方法二：遍历每一个窗口，找符合条件的k  O(45* N^2)
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<#x<<" "<<x<<"\n"

vector<vector<int>> mp;
int n, L;

int mmp[4][8] = {{0, 0, 1, 0, 0, 1, 0, 1}, 
			   {0, 0, 1, 1, 1, 1, 1, 0},
			   {0, 0, 0, 0, 1, 1, 0, 0},
			   {1, 1, 1, 1, 1, 1, 0, 0}};   

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>L;
	mp.assign(n, vector<int>(n));
	for(int i = 0; i < n; i++) {
		for(int j = 0;j < n; j++) {
			cin>>mp[i][j];
		}
	}
	vector<bool>ans(L, false);
	for(int x = 0; x <= n - 5; x++) {
		for(int y = 0; y <= n-9; y++) {
			int mink = 1e6;  // 必须变白像素的最小值
			int maxk = -1;   // 必须变黑像素的最大值
			for(int i = y; i < y+9; i++) { // 第一行全白
				mink = min(mink, mp[x][i]);
			}
			for(int i = x; i < x + 5; i++) { // 第一列全白
				mink = min(mink, mp[i][y]);
			}
			// 检查剩余的 4 * 8 的矩阵
			for(int i = x + 1; i < x + 5; i++) {
				for(int j = y + 1; j < y + 9; j++) {
					int tmp = mmp[i - (x+1)][j - (y+1)];
					if(tmp == 1) {
						mink = min(mink, mp[i][j]);
					} else {
						maxk = max(maxk, mp[i][j]);
					}
				}
			}
			// 判断：如果最大黑点灰度 < 最小白点灰度，说明存在合法的 k
			if(maxk < mink) {
				for(int k = maxk + 1; k <= mink; k++) {
					if(k >= 0 && k < L) {
						ans[k] = true;
					}
				}
			}
		}
	}
	for(int k = 0; k < L; k++) {
		if(ans[k]) cout<<k<<"\n";
	}
	return 0;
}

/*
【总结】
通用模板：二值化阈值匹配固定模式时，把每个像素的约束转成 k 的区间；白点要求 k <= 最小白值，黑点要求 k > 最大黑值，合法 k 在 (maxBlack, minWhite]。
标准框架：枚举窗口 -> 统计白点最小值与黑点最大值 -> 若 maxBlack < minWhite 则标记区间 -> 输出所有 k。
复杂度结论：窗口数 O(n^2)，每窗常数点检查，整体 O(n^2)；空间 O(L) 或 O(1) 额外。
通用易错点：注意阈值定义是 >=k 为白、<k 为黑，区间端点是 maxBlack+1 到 minWhite；还要截断到 [0, L-1]。
本题差异：模式固定为 5×9，且首行、首列全白，其余 4×8 由模板矩阵约束。
本题特化：直接用 4×8 模式表 mmp 统计 white/min 和 black/max，窗口内常数 45 点即可。
*/