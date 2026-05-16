/*
题目背景
两个集合的 Jaccard 相似度定义为：
Sim(A,B) = |A ∩ B| / |A ∪ B|
即交集的大小除以并集的大小。当集合 A 和 B 完全相同时，Sim(A,B)=1 取得最大值；当二者交集为空时，Sim(A,B)=0 取得最小值。

题目描述
除了进行简单的词频统计，小 P 还希望使用 Jaccard 相似度来评估两篇文章的相似性。 具体来说，每篇文章均由若干个英文单词组成，且英文单词仅包含“大小写英文字母”。 对于给定的两篇文章，小 P 首先需要提取出两者的单词集合 A 和 B，即去掉各自重复的单词。 然后计算出：
|A ∩ B|，即有多少个不同的单词同时出现在两篇文章中；
|A ∪ B|，即两篇文章一共包含了多少个不同的单词。
最后再将两者相除即可算出相似度。 需要注意，在整个计算过程中应当忽略英文字母大小写的区别，比如 the、The 和 THE 三者都应被视作同一个单词。
试编写程序帮助小 P 完成前两步，计算出 |A ∩ B| 和 |A ∪ B|；小 P 将亲自完成最后一步的除法运算。

输入格式
从标准输入读入数据。
输入共三行。
输入的第一行包含两个正整数 n 和 m，分别表示两篇文章的单词个数。
第二行包含空格分隔的 n 个单词，表示第一篇文章；
第三行包含空格分隔的 m 个单词，表示第二篇文章。

输出格式
输出到标准输出。
输出共两行。
第一行输出一个整数 |A ∩ B|，即有多少个不同的单词同时出现在两篇文章中；
第二行输出一个整数 |A ∪ B|，即两篇文章一共包含了多少个不同的单词。
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, m;  cin>>n>>m;
	set<string> A, B;
	for(int i = 0; i < n; i++) {
		string s;  cin>>s;
		string ss = "";
		for(char c : s) {
			ss += tolower(c);
		}
		A.insert(ss);
	}
	for(int i = 0; i < m; i++) {
		string s;  cin>>s;
		string ss = "";
		for(char c : s) {
			ss += tolower(c);
		}
		B.insert(ss);
	}
	int lena = A.size(), lenb = B.size();
	int cnt0 = 0; // 交集
	auto pa = A.begin(), pb = B.begin();
	while(pa != A.end() && pb != B.end()) {
		if(*pa == *pb) {
			cnt0++;
			pa++; pb++;
		} else if(*pa < *pb) {
			pa++;
		} else {
			pb++;
		}
	}
	cout<<cnt0<<"\n"<<lena+lenb-cnt0;
	return 0;
}

/*
【总结】
1. 模型：集合的交集与并集（字符串存储、去重与小写化）。
2. 正确性直观：运用 std::set 的特性进行自动去重以及按字典序排序；结合双指针的思想遍历两数组，进而获得交集个数。利用容斥原理，并集大小即为 |A| + |B| - |A ∩ B|。
3. 复杂度：
   - 插入集合操作（自动排序）：O(N * L * logN + M * L * logM)。
   - 双指针寻找交集大小：O((N+M) * L)。
   - 总体时间复杂度：大致为 O((N+M)log(N+M) * L)。在本题 , m \le 10^4$ 的范围可以迅速通过。
4. 避坑：直接用内置函数tolower 提取字符串有效避免手动 ASCII 判断繁琐细节；遍历有序集合算交集比较快捷，此外，求并集不用合并 std::set。
*/
