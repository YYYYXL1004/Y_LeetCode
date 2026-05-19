/*
题目背景
近日来，西西艾弗岛化学研究中心的研究员们向岛上的初中学生开展了化学科普活动。在活动中发现，初学化学的同学们十分苦恼于正确配平化学方程式。 而还有一些同学，则提出了一些稀奇古怪的方程式，让研究员们帮忙配平。在配平之前，研究员们需要先判断这个方程式是否能够配平。

一个化学方程式，也叫化学反应方程式，是用化学式表示化学反应的式子。其等号左右两侧分别列举了化学反应的全部反应物和生成物。 每种物质都用其化学式表示。一个物质的化学式，列举了构成该物质的各元素的原子数目。例如，水的化学式是 H2O，表示水分子中含有两个氢原子和一个氧原子。 化学方程式中每种物质的化学式前面都有一个系数，表示参与反应或生成的物质的相对数目比例。例如，方程式 2H2 + O2 = 2H2O 表示二分子氢气和一分子氧气反应生成二分子水。 我们称一个化学方程式是配平的，是指该方程式中的反应物和生成物中，各元素原子总数目相等。例如上述方程式中，左侧氢原子、氧原子的总数目分别为 4 和 2，右侧氢原子、氧原子的总数目分别为 4 和 2，因此该方程式是配平的。

题目描述
为了配平一个化学方程式，我们可以令方程式中各物质的系数为未知数，然后针对涉及的每一种元素，列出关于系数的方程，形成一个齐次线性方程组。然后求解这个方程组，得到各物质的系数。这样，我们就把化学方程式配平的问题，转化为了求解齐次线性方程组的问题。 如果方程组没有非零解，那么这个方程式是不可以配平的。反之，如果方程组有非零解，我们就可能得到一个配平的方程式。当然，最终得到的方程式仍然需要结合化学知识进行检验，对此我们不再进一步考虑，仅考虑非零解的存在。
本题中，我们将给出一些化学方程式，请你按照上述方法判断它们是否可以配平。为了便于程序处理，我们用到的化学式，会被化简为只包含小写字母和数字的字符串，不包含括号。 其中连续的字母表示一种元素，随后的数字表示原子个数。原子个数为 1 时不省略数字；一个化学式中包含的元素不重复。例如，上述方程式中的化学式可以化简为 al2s3o12、n1h5o1、al1o3h3、n2h8s1o4。

输入格式
从标准输入读入数据。
输入的第一行包含一个正整数 n，表示需要判断的化学方程式的个数。
接下来的 n 行，每行描述了一个需要被配平的化学方程式。包含空格分隔的一个正整数和全部涉及物质的化学式。其中，正整数 m 表示方程式中的物质；随后的 m 个字符串，依次给出方程式中的反应物的化学式和生成物的化学式。

输出格式
输出到标准输出。
输出包含 n 行，每行包含字母 Y 或 N，表示按题设方法，所给待配平化学方程式能否配平。
*/


#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<#x<<" "<<x<<"\n"
const double EPS = 1e-7;   // 浮点判零精度阈值：abs(x) <= EPS 视为 0
int ans;                    // 秩（非零行计数）

// 高斯消元：将矩阵化为阶梯形，统计秩（非零行数）
// x = 当前处理的行，y = 当前处理的列（主元列）
void solve(vector<vector<double>>& mp, int x, int y) {
	if(x >= mp.size() || y >= mp[0].size()) return ;
	// ① 检查第 y 列从第 x 行往下是否全为零
	bool full_0 = true;
	for(int i = x; i < mp.size(); i++) {
		if(abs(mp[i][y]) > EPS) {  // 浮点判零必须用 abs < EPS，不能用 == 0
			full_0 = false;
			break;
		}
	}
	// 全零 → 这列没有可用主元，跳到下一列，行不动
	if(full_0) {
		solve(mp, x, y+1);
		return ;
	}
	// ② 选主元：如果当前行 x 的第 y 列是 0，从下面找非零行换上来
	//    因为下一步要用 mp[x][y] 做除数，不能除以零
	if(abs(mp[x][y]) <= EPS) {
		for(int i = x+1; i < mp.size(); i++) {
			if(abs(mp[i][y]) > EPS) {
				for(int j = y; j < mp[0].size(); j++) {
					swap(mp[x][j], mp[i][j]);  // 整行交换
				}
				break;
			}
		}
	}
	// ③ 消元：用主元行 x 把下面所有行的第 y 列消成 0
	for(int i = x+1; i < mp.size(); i++) {
		if(abs(mp[i][y]) > EPS) {
			double bei = mp[i][y] / mp[x][y];   // 消元倍数
			for(int j = y; j < mp[0].size(); j++) {
				mp[i][j] -= bei * mp[x][j];     // 行减法：第 i 行 -= 倍数 × 主元行
			}
		}
	}
	// ④ 找到一个主元 → 秩 +1，递归处理右下角子矩阵
	ans++;
	solve(mp, x+1,y+1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;  cin>>n;
	while(n--) {
		int m;  cin>>m;
		set<string> st;                              // 收集所有元素名（自动去重+排序）
		vector<unordered_map<string, int>> v(m);     // v[i] = 第 i 种物质的 {元素→原子数}
		for(int i = 0; i < m; i++) {
			string s;  cin>>s;
			// 解析化学式：连续字母=元素名，连续数字=原子个数
			string s1 = "", s2 = "";
			for(int j = 0; j < s.length(); j++) {
				if(s[j] >= 'a' && s[j] <= 'z') {
					s1 += s[j];                      // 累积元素名
				} else {
					s2 += s[j];                      // 累积数字
					if(j != s.length() && s[j+1] >= '0' && s[j+1] <= '9') {
						s2 += s[j+1];
						j++;
					}
					v[i].insert({s1, stoi(s2)});
					st.insert(s1);
					s1 = "", s2 = ""; // 清空
				}
			}
		}
		int len = st.size();                     // len = 元素种数（矩阵行数）
		if(len < m) {                            // 元素数 < 物质数 → 方程数 < 未知数 → 必有非零解
			cout<<"Y"<<"\n";
			continue;
		}
		// 构建系数矩阵：行=元素，列=物质，mp[i][j]=第j种物质含第i种元素的原子数
		vector<vector<double>> mp (len, vector<double>(m));
		auto it = st.begin();
		for(int i = 0; i < len; i++) {
			string s = *it;
			for(int j = 0; j < m; j++) {
				if(v[j].count(s)) {
					mp[i][j] = v[j][s];
				} else {
					mp[i][j] = 0;
				}
			}
			it++;
		}
		// 高斯消元求秩，判断 rank < m（物质数）
		ans = 0;
		solve(mp, 0, 0);
		if(ans < m) cout<<"Y"<<"\n";   // 秩 < 未知数个数 → 有非零解 → 可配平
		else cout<<"N"<<"\n";           // 秩 = 未知数个数 → 只有零解 → 不可配平
	}
	return 0;
}

/*
【总结（第一种解法）】
1. 模型：将配平问题转化为齐次线性方程组，判断系数矩阵秩是否小于未知数个数。
2. 正确性直观：用元素集合确定矩阵行，物质数为列；高斯消元消去列得到秩；若秩 < m，则存在非零解。
3. 复杂度：元素数 E、物质数 m，消元 O(E * m^2)；构建矩阵 O(E * m)。
4. 避坑：浮点消元要用 EPS 判零；元素解析时按字母+数字成对提取。
*/

/*
第二种解法（注释保留，不参与编译）：模 998244353 高斯消元
核心思想：所有运算在模 998244353 的整数域上进行，用乘逆元代替除法，彻底规避浮点精度问题。

#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<#x<<" "<<x<<"\n"
const int MOD = 998244353;

// 快速幂：计算 a^b % MOD，O(log b)
long long qpow(long long a, long long b) {
	long long res = 1;
	a %= MOD;
	while(b > 0) {
		if(b & 1) res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

// 费马小定理求逆元：a^(p-2) 就是 a 在模 p 下的倒数
long long inv(long long a) {
	return qpow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;  cin>>n;
	while(n--) {
		int m;  cin>>m;
		set<string> st;                              // 收集所有元素名（自动去重+排序）
		vector<unordered_map<string, int>> v(m);     // v[i] = 第 i 种物质的 {元素→原子数}
		for(int i = 0; i < m; i++) {
			string s;  cin>>s;
			// 解析化学式：连续字母=元素名，连续数字=原子个数
			string s1 = "", s2 = "";
			for(int j = 0; j < s.length(); j++) {
				if(s[j] >= 'a' && s[j] <= 'z') {
					s1 += s[j];
				} else {
					s2 += s[j];
					if(j != s.length() && s[j+1] >= '0' && s[j+1] <= '9') {
						s2 += s[j+1];
						j++;
					}
					v[i].insert({s1, stoi(s2)});
					st.insert(s1);
					s1 = "", s2 = "";
				}
			}
		}
		int len = st.size();
		if(len < m) {
			cout<<"Y"<<"\n";
			continue;
		}
		// 构建系数矩阵：行=元素，列=物质
		vector<vector<long long>> mp(len, vector<long long>(m, 0));
		auto it = st.begin();
		for(int i = 0; i < len; i++) {
			string s = *it;
			for(int j = 0; j < m; j++) {
				if(v[j].count(s)) {
					mp[i][j] = v[j][s] % MOD;     // 直接存模意义下的值
				}
			}
			it++;
		}
		// 高斯消元求秩（模意义下，用乘逆元代替除法）
		int ans = 0, row = 0;
		for(int col = 0; col < m && row < len; col++) {
			// ① 选主元：从第 row 行往下找第一个非零行
			int pivot = row;
			for(int i = row; i < len; i++) {
				if(mp[i][col] != 0) {               // 模意义下直接 != 0，不需要 EPS
					pivot = i;
					break;
				}
			}
			if(mp[pivot][col] == 0) continue;        // 整列全零 → 跳过
			// ② 换行
			swap(mp[row], mp[pivot]);
			// ③ 算主元的逆元（代替浮点除法中的 1/mp[x][y]）
			long long inv_p = inv(mp[row][col]);
			// ④ 消元：用主元行把下面所有行的第 col 列消成 0
			for(int i = row+1; i < len; i++) {
				if(mp[i][col] != 0) {
					long long f = mp[i][col] * inv_p % MOD;
					for(int j = col; j < m; j++) {
						mp[i][j] = (mp[i][j] - f * mp[row][j]) % MOD;
						if(mp[i][j] < 0) mp[i][j] += MOD;  // C++ 负数取模修正
					}
				}
			}
			ans++;  row++;
		}
		if(ans < m) cout<<"Y"<<"\n";
		else cout<<"N"<<"\n";
	}
	return 0;
}

/*
【总结】
1. 模型：将化学方程式的配平问题转化为齐次线性方程组  = 0$ 的非零解存在性判断问题。实质上就是判断系数矩阵 $ 的秩是否严格小于未知数的个数 $。
2. 正确性直观：提取连续字母作为元素标识并映射到对应的行下标上。由于是对存在解本身进行定性判断，无需使用容易产生精度问题的 double，而采用模大质数（如 998244353）域下的高斯消元求矩阵的秩，能够规避所有精度带来的异常。
3. 复杂度：
   - 字符串解析阶段复杂度线性相关。
   - 矩阵通过哈希映射为元素去重，构成最坏 (40 \times 40)$ 维的矩阵。
   - 高斯消元的时间复杂度为 (N \cdot M^2)$ 即最高 (N \cdot 40^3)$ 极小，完全满足运算要求。
4. 避坑：利用质数取模对带有除法的消元过程执行乘法逆元（Fermat 小定理）进行转换；字符串解析时须判断 isalpha 和 isdigit。
*/
