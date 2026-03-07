/*
 * @lc app=leetcode.cn id=707 lang=cpp
 * @lcpr version=30307
 *
 * [707] 设计链表
 */

// @lc code=start
// class MyLinkedList {  // 单链表实现
// private:
//     struct ListNode { // 节点和链表解耦定义，方便操作，比如虚拟头结点定义
//         int val;
//         ListNode *next;
//         ListNode(int x) : val(x), next(NULL) {}
//     };
//     ListNode* dummy; // 虚拟头节点
//     int size; // 链表长度
// public:
//     MyLinkedList() {
//         dummy = new ListNode(-1);
//         size = 0;
//     }

//     int get(int index) {
//         if(index < 0 || index >= size) {
//             return -1;
//         }
//         ListNode* cur = dummy->next;
//         for(int i=0;i<index;i++) { // 从0索引向后移动index次
//             cur = cur->next; // 最后cur指向索引为index的节点
//         }
//         return cur->val;
//     }
    
//     void addAtHead(int val) {
//         ListNode* newNode = new ListNode(val);
//         newNode->next = dummy->next; // 头插法
//         dummy->next = newNode;
//         size++;  // 记得记录size的变化
//     }
    
//     void addAtTail(int val) {
//         ListNode* newNode = new ListNode(val);
//         ListNode* cur = dummy; // debug注意：考虑链表为空的情况
//         while(cur->next != NULL) { // 移动指针到末尾
//             cur = cur->next;
//         }
//         cur->next = newNode;
//         size++;
//     }
    
//     void addAtIndex(int index, int val) {
//         if(index < 0 || index > size) {
//             return ;
//         } else if(index == size) {
//             addAtTail(val);
//         } else if(index == 0) {
//             addAtHead(val);
//         } else {
//             ListNode* newNode = new ListNode(val);
//             ListNode* cur = dummy;
//             for(int i=0; i<index; i++) {
//                 cur = cur->next; // 把cur-next指向索引为index的位置，而不是cur指向index的位置
//             }
//             newNode->next = cur->next;
//             cur->next = newNode;
//             size++;
//         }
//     }
    
//     void deleteAtIndex(int index) {
//         if(index < 0 || index >= size) {
//             return ;
//         }
//         ListNode* cur = dummy;
//         for(int i=0; i <index; i++) {
//             cur = cur->next; // 依旧让cur->next指向索引为index的位置
//         }
//         ListNode* toDelete = cur->next;
//         cur->next = cur->next->next;
//         delete toDelete;
//         size--;
//     }
// };
class MyLinkedList {  //双链表实现
private:
    struct Node {
        int val;
        Node* next;
        Node* prev;
        Node(int x): val(x), next(NULL), prev(NULL) {}
    };
    Node* dummyhead;
    Node* dummytail;
    int size;
public:
    MyLinkedList() {
        dummyhead = new Node(-1);
        dummytail = new Node(-1);
        dummyhead->next = dummytail;
        dummytail->prev = dummyhead;
        size = 0;
    }

    int get(int index) {
        if(index < 0 || index >= size) {
            return -1;
        }
        Node* cur = dummyhead;
        for(int i = 0; i < index; i++) {
            cur = cur->next; //cur->next指向index索引位置
        }
        return cur->next->val; 
    }
    
    // 插入的时候一定要考虑链表为空的情况，淡然，好像使用虚拟头尾节点就不用考虑了（？
    void addAtHead(int val) {
        Node* newNode = new Node(val);
        Node* temp = dummyhead->next; // 引入一个中间变量，避免dummphead->next的改变影响4式
        temp->prev = newNode; //必须第一个做，趁dummyhead->next还没改变
        newNode->next = temp; 
        newNode->prev = dummyhead;
        dummyhead->next = newNode; // 最后再修改
        size++; // 不要忘
    }
    
    void addAtTail(int val) {
        Node* newNode = new Node(val);
        Node* temp = dummytail->prev;
        temp->next = newNode;
        newNode->next = dummytail;
        newNode->prev = temp;
        dummytail->prev = newNode;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index >size) {
            return ;
        }
        Node* newNode = new Node(val);
        Node* cur = dummyhead;
        for(int i = 0; i < index; i++) {
            cur = cur->next;
        }
        Node* temp = cur->next; // 想不清楚就多画图
        temp->prev = newNode;
        newNode->next = temp;
        newNode->prev = cur;
        cur->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index >= size) {
            return ;
        }
        Node* cur = dummyhead;
        for(int i = 0; i < index; i++) {
            cur = cur->next;
        } // cur是待删除节点前一个节点
        Node* toDelete = cur->next;
        Node* temp = toDelete->next;
        cur->next = toDelete->next;
        temp->prev = cur;
        delete toDelete;
        size--; 
    }
};
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
// @lc code=end



/*
// @lcpr case=start
// ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]\n[[],[1],[3],[1,2],[1],[1],[1]]\n
// @lcpr case=end

 */

