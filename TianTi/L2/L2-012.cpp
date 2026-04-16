#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int> heap;

int main() {
    cin>>n>>m;
    heap.resize(n+1);
    for(int i = 1; i <= n; i++) {
        cin>>heap[i];
        int index = i;
        // 向上调整，父节点大就换下来
        while(index > 1 && heap[index] < heap[index/2]) {
            swap(heap[index], heap[index/2]);
            index /= 2;
        }
    }
    unordered_map<int, int> mp; // 存key->index
    for(int i = 1; i <= n; i++) {
        mp[heap[i]] = i;
    }
    
    while(m--) {
        int x;  string s;
        cin>>x>>s;
        if(s == "and") { // x and y are siblings
            int y; cin>>y>>s>>s;  // 两个字符串没用，读取即可
            if(mp[x] / 2 == mp[y] /2) cout<<"T\n";
            else cout<<"F\n";
        }  else{
            cin>>s;
            if(s == "a") {  // x is a child of y
                int y;  cin>>s>>s>>y;
                if(mp[x]/2 == mp[y]) cout<<"T\n";
                else cout<<"F\n";
            } else {
                cin>>s;
                if(s == "root") {  // x is the root
                    if(mp[x] == 1) cout<<"T\n";
                    else cout<<"F\n";
                } else{ // x is the parent of y
                    int y;  cin>>s>>y;
                    if(mp[y] / 2 == mp[x]) cout<<"T\n";
                    else cout<<"F\n";
                }
            }
        }
        
    }
    
    return 0;
}