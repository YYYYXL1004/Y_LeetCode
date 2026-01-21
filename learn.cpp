#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void vector_learn(int n) {
    vector<int> nums(n);
    cout << nums.empty() << endl;  // false
    cout << nums.size() <<endl;    // 10

    nums.push_back(20);
    cout<< nums.size() <<endl;   // 11
    cout<< nums.back() <<endl;   // 20

    // nums.pop_back();  // 删除最后一个元素，无返回值
    cout<< nums.size() <<endl;   // 10

    nums[0] = 11;  // 11 0 0 0 0 0 0 0 0 0 0
    nums.insert(nums.begin()+3, 4); // 在索引3处插入一个元素 11 0 0 4 0 0 0 0 0 0 
    nums[5] = 5, nums[6] = 6;   // 11 0 0 4 0 5 6 0 0 0
    nums.erase(nums.begin()+6);  // 删除索引6处的元素 11 0 0 4 0 5 0 0 0 0

    swap(nums[0], nums[1]); // 交换元素 0 11 0 4 0 5 0 0 0 0
 

    // for(int i=0; i<n; i++) {
    //     cout<<nums[i]<<" ";
    // }

    for(int val: nums) {
        cout<<val<<" ";
    }
    cout<<endl;
}
void list_learn() {
    list<int> lst{1, 2 ,3, 4, 5, 6};
    cout<< lst.empty() <<endl;  // false
    cout<< lst.size() <<endl;   // 6

    lst.push_front(0);
    lst.push_back(7);
    cout<< lst.front() <<" "<< lst.back()<<endl;  // 0 7

    // lst.pop_front();
    // lst.pop_back();
    
    // 在列表中插入元素
    auto it = lst.begin();
    advance(it, 2); // 移动到索引2处
    lst.insert(it, 999);  // 在索引2处插入 1 2 999 3 4 5 6

    // it = lst.begin();
    advance(it, 5);
    lst.erase(it); // 1 2 999 3 4 6

    for(int val: lst) {
        cout<<val<<" ";
    }
    cout<<endl;

}
void queue_learn() {
    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);
    cout<< q.empty() <<endl;  // false
    cout<< q.size() <<endl; // 3
    cout<< q.front() << " " <<q.back()<<endl; // 10 30

    q.pop(); // 删除队首元素   

    cout<< q.front() <<endl;  // 20
    while(!q.empty()) {
        cout<< q.front() <<" "; // 20 30
        q.pop();
    }
    cout<<endl;
}
void stack_learn() {
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);
    cout<< s.empty() <<endl; // false
    cout<< s.size() <<endl; // 3
    cout<< s.top() <<endl; // 30
    s.pop();
    cout<< s.top()<<endl;  //20
}
void unordered_map_learn() {
    unordered_map<int, string> hashmap {{1, "one"}, {2, "two"}, {3, "three"}};
    cout<<hashmap.empty() <<endl;
    cout<<hashmap.size() <<endl;

    // if(hashmap.contains(2)) { // c++20支持
    //     cout<< "Key 2 -> " << hashmap[2] <<endl;
    // } else {
    //     cout<< "Key 2 not found"<<endl;
    // }

    if(hashmap.count(3)) {  // 存在返回1，不存在返回0 （C++11支持）
        cout<<"Key 3 -> " << hashmap[3] <<endl; 
    }

    cout<< hashmap[4]<<endl;  // 输出空字符串
    cout<< hashmap.size()<<endl;  // 访问不存在的键会自动创建这个键

    hashmap[4] = "four";

    hashmap.erase(3); // 删除键值对

    for(const auto &pair: hashmap) {  // 输出不一定按原顺序
        cout<< pair.first << "->" << pair.second<< endl;
    }

}
void unordered_set_learn() {
    unordered_set<int> hashset{1, 2, 3, 5};
    cout<< hashset.empty() << " " <<hashset.size() <<endl;  // false 4

    if(hashset.count(3)) {
        cout<<"3 is found"<<endl;
    } else {
        cout<<"3 is not found"<<endl;
    }

    hashset.insert(7);  // 1 2 3 5 7
    hashset.erase(2);  // 删除2这个元素 1 3 5 7 

    for(const auto &element: hashset) {  // 没有顺序
        cout<< element << endl;
    }
}

int main() {
    int n = 10;
    // vector_learn(n);  // 学习vec
    // list_learn(); // 学习双向链表
    // queue_learn(); // 学习队列
    // stack_learn();  // 学习栈，先进后出
    // unordered_map_learn(); // 学习unordered_map
    // unordered_set_learn();  // 学习unordered_set

    // 特别注意一个可能出现的问题，就是当递归函数的参数中有容器数据结构时，千万别使用传值的方式，
    // 否则每次递归都会创建一个数据副本，消耗大量的内存和时间，非常容易导致超时或者超内存的错误。

    
    return 0;
}