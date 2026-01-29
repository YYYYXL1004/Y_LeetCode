/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * @lcpr version=30307
 *
 * [146] LRU 缓存
 */

// @lc code=start
class Node {
public:
    int key, val;
    Node *next, *prev;
    Node(int k, int v) : key(k), val(v),next(nullptr), prev(nullptr) {}
};

class DoubleList{
private:
    // 头尾虚节点
    Node* head;
    Node* tail;
    int size;
public:
    DoubleList() {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    void addLast(Node* x) {
        x->prev = tail->prev;
        x->next = tail;
        tail->prev->next = x;
        tail->prev = x;
        size++;
    }

    void remove(Node* x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
        size--;
    }

    // 删除链表中的第一个节点并返回该节点
    Node* removeFirst() {
        if(head->next == tail) {
            return nullptr;
        }
        Node* first = head->next;
        remove(first);
        return first;
    }

    int getSize() {
        return size;
    }
};

class LRUCache {
private:
    // key->Node(key, val)
    unordered_map<int, Node*> mp;
    // Node(k1, v1) -> Node(k2, v2)..
    DoubleList cache;
    int cap; // 最大容量

public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }

    int get(int key) {
        if(!mp.count(key)) {
            return -1;
        }   
        // 将该数据设置成最近使用过的
        makeRecently(key);
        return mp[key]->val;
    }
    
    void put(int key, int value) {
        if(mp.count(key)) {
            // 删除旧元素
            deleteKey(key);
            // 把新插入的数据设置为最近使用过的
            addRecently(key, value);
            return;
        }
        if(cap == cache.getSize()) {
            // 删除最久未使用的元素
            removeLeastRecently();
        }
        // 如果不存在，则向缓存中插入该组
        addRecently(key, value);
    }

    void makeRecently(int key) {
        Node* x = mp[key];
        cache.remove(x); // 先删除再重新插到队尾
        cache.addLast(x);
    }

    void addRecently(int key, int val) {
        Node* x = new Node(key, val);
        cache.addLast(x);
        mp[key] = x; // 别忘了添加映射
    }

    void deleteKey(int key) {
        Node* x = mp[key];
        cache.remove(x);
        mp.erase(key);
    }

    void removeLeastRecently() {
        // 链表头部第一个节点就是最近未使用的
        Node* x = cache.removeFirst();
        int deleteKey = x->key;
        mp.erase(deleteKey);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end



/*
// @lcpr case=start
// ["LRUCache","put","put","get","put","get","put","get","get","get"]\n[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]\n
// @lcpr case=end

 */

