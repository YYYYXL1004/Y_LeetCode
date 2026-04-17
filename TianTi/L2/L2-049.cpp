#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
vector<int> mp[MAXN]; // 物品：拥有人

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;  cin>>n>>m;
    int maxm = 2;
    for(int i = 1; i <= n; i++) {
        int k;  cin>>k;
        while(k--) {
            int x;  cin>>x;
            mp[x].push_back(i);
            maxm = max(maxm, x);
        }
    }
    // 不用排序，添加时就是有序的
    // for(int i = 2; i <= maxm; i++) sort(mp[i].begin(), mp[i].end());
    int Q; cin>>Q;
    while(Q--) {
        int x, y;  cin>>x>>y;
        int cnt = 0;
        // 避免直接深拷贝
        // vector<int> v1 = mp[x];
        // vector<int> v2 = mp[y];
        // 建议加上引用& 和const 直接读取原数组
        // const vector<int>& v1 = mp[x];
        // const vector<int>& v2 = mp[y];
        int len1 = mp[x].size() , len2 = mp[y].size();
        int l1 = 0, l2 = 0;
        while(l1 < len1 && l2 < len2) {
            if(mp[x][l1] == mp[y][l2]) {
                cnt++;
                l1++, l2++;
            } else if(mp[x][l1] < mp[y][l2]) {
                l1++;
            } else {
                l2++;
            }
        }
        cout<<cnt<<"\n";
    }
    return 0;
}