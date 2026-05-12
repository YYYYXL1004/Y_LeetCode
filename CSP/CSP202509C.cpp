/*
题目背景
西西艾弗岛大数据公司的服务器需要将 HTTP/1.1 头信息升级为 HTTP/2 的 HPACK
格式。头信息是有序 key-value 对，字段名可重复。HPACK 使用静态表和动态表：
静态表预定义，动态表从空开始，插入新条目到最前面，超过容量时丢弃最旧条目。

题目描述
给定静态表、动态表容量、Huffman 树描述以及一系列指令，按顺序解码得到原始
头信息。指令类型：
1) 表格引用：1 i，输出静态/动态表中编号 i 的键值对。
2) 字面量并索引：2 0 k v 或 2 i v，k/v 为字符串或 Huffman 编码字符串。
	 若 i>0，字段名来自编号 i 的条目。输出后将该键值对插入动态表。
3) 字面量不索引：3 0 k v 或 3 i v，类似但不插入动态表。

表的编号：静态表编号 1..S，动态表编号 S+1..S+D。插入新条目后成为 S+1。

Huffman 树表示
从根节点开始：叶子节点输出 1 并跟随字符；非叶子输出 0，再递归输出左、右子树。
例如 001b01c1d1a 对应示例树，编码为 a:1, b:00, c:010, d:011。

字符串格式
普通字符串：s，若 s 以 H 开头：
	- 若以 HH 开头，输出去掉第一个 H 的部分；
	- 若以单个 H 开头，则为 Huffman 编码字符串。
Huffman 编码字符串：Hb，b 为偶数位 0-9a-f 十六进制串。按位连续存储：
	- 原始字符串靠前的字符编码位先写入，高位在每字节高位；
	- 最后一字节低位补 0，并追加一字节表示补 0 数 p (0<=p<=7)。
	例：abcd 编码得到 100010011，补 0 后为 10001001 10000000，表示为 H898007。

输入格式
第一行 S D。接着 S 行为静态表键和值。随后一行 Huffman 树表示。
再一行 N 表示指令数，后续 N 行为指令。

输出格式
输出 N 行，格式为 key: value，字符串需解码为原始字符串。

输入样例 1
3 3
Foo Bar
Foo Barz
bar barzz1
001b01c1d1a
11
1 1
3 3 ABCD
3 0 H898007 HHIJK
2 0 H898007 EFGH
1 4
2 0 DDDD EEEE
2 5 GGGG
1 4
1 6
2 0 HHHH IIII
1 4

输出样例 1
Foo: Bar
bar: ABCD
abcd: HIJK
abcd: EFGH
abcd: EFGH
DDDD: EEEE
abcd: GGGG
abcd: GGGG
abcd: EFGH
HHH: IIII
HHH: IIII

样例说明
第 1 条指令引用静态表 1；第 3/4 条指令字段名使用 Huffman 解码得到 abcd。
动态表插入后编号整体前移，超过容量时丢弃末尾条目。

数据范围
1 <= S <= 64，1 <= D <= 120，Huffman 编码长度不超过 8 位。
1 <= N <= 1000，字段名/字段值解码前后长度不超过 150。
子任务包含：仅引用、无 Huffman、字面量并索引不超过 D 等情况。
*/
#include<bits/stdc++.h>
using namespace std;
using pss = pair<string, string>;

string huffman_str;
int idx = 0;  // 全局指针，用于遍历字符串
map<string, char> code_to_char;

void buildHuffman(const string& str, string path) {
	if(idx >= str.length()) return ;
	char cur_char = str[idx];  idx++;
	if(cur_char == '0') {
		// 遇到0是内部节点，要分叉了，分别左右递归
		buildHuffman(str, path + "0");
		buildHuffman(str, path + "1");
	} else if(cur_char == '1') {
		char c = str[idx];  idx++; // 叶子节点真正对应的字母页跳过
		code_to_char[path] = c;
	}
}

unordered_map<char, string> hex_map = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
    {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
};
// 转换str
string trans(const string& str) {
	if(str[0] != 'H') {
		return str;
	} else if(str[0] == 'H' && str[1] == 'H') {
		return str.substr(1); // 返回下标1及之后的
	} else {
		int len = str.length();
		int p = str[len-1] - '0';
		string b = "";
		for(int i = 1; i < len - 2; i++) {
			b += hex_map[str[i]];
		}
		b = b.substr(0, b.length()-p); // 去掉后补0
		string res = "";
		string path = "";
		for(char bit : b) {
			path += bit;
			if(code_to_char.count(path)) {
				res += code_to_char[path];
				path = ""; // 清零，重新匹配
			}
		}
		return res;
	}
}

int main() {
	int S, D;  cin>>S>>D;
	vector<pss> vec(S+1);
	for(int i = 1; i <= S; i++) {
		cin>>vec[i].first>>vec[i].second;
	}
	deque<pss> dq;
	cin>>huffman_str;
	buildHuffman(huffman_str, "");
	int N;  cin>>N;
	while(N--) {
		int op;  cin>>op;
		if(op == 1) {
			int i;  cin>>i;
			if(i > S) {
				int pos = i - (S+1);
				cout<<dq[pos].first<<": "<<dq[pos].second<<"\n";
			} else {
				cout<<vec[i].first<<": "<<vec[i].second<<"\n";
			}
		} else if(op == 2) {
			int i;  cin>>i;
			if(i == 0) {
				string k, v;  cin>>k>>v;
				string kk = trans(k), vv = trans(v);
				dq.emplace_front(kk, vv);
				cout<<kk<<": "<<vv<<"\n";
			} else {
				string v;  cin>>v;
				string vv = trans(v);
				if(i > S) {
					int pos = i - (S+1);
					string key = dq[pos].first;
					cout<<key<<": "<<vv<<"\n";
					dq.emplace_front(key, vv);
				} else {
					cout<<vec[i].first<<": "<<vv<<"\n";
					dq.emplace_front(vec[i].first, vv);
				}
			}
		} else if(op == 3) {
			int i;  cin>>i;
			if(i == 0) {
				string k, v;  cin>>k>>v;
				string kk = trans(k), vv = trans(v);
				cout<<kk<<": "<<vv<<"\n";
			} else {
				string v;  cin>>v;
				string vv = trans(v);
				if(i > S) {
					int pos = i - (S+1);
					string key = dq[pos].first;
					cout<<key<<": "<<vv<<"\n";
				} else {
					cout<<vec[i].first<<": "<<vv<<"\n";
				}
			}
		}
	}
	return 0;
}

/*
【总结】
1. 通用模板（表驱动解码 + Huffman 还原）：先用先序编码重建 Huffman 树，再将
	十六进制串转比特流并沿树解码得到原串；逐条指令解码并维护静态/动态表。
2. 适用特征：存在“表引用 + 动态表插入/淘汰 + Huffman 压缩字符串”的协议解码题。
3. 正确性直觉：树的先序表示可唯一还原结构；比特流按路径匹配叶子即为原字符；
	动态表用队列前插，编号与位置同步移动，引用编号即可取到对应键值。
4. 复杂度：建树 O(|T|)，字符串解码 O(比特数)，每条指令 O(1) 表操作，总体近似
	O(输入总长度)。
5. 通用易错点："HH" 表示转义字符串；Huffman 末字节补 0 与补位计数字节 p 的处理；
	编号 1-based，动态表索引为 i-(S+1)；容量超限需丢弃最旧条目。
6. 本题差异：动态表插入位置固定为最前（编号 S+1），引用静态/动态表混用且可重复。
7. 本题差异：Huffman 编码长度不超过 8 位，解码可用“路径到字符”映射快速匹配。
*/