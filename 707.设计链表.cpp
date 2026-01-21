/*
 * @lc app=leetcode.cn id=707 lang=cpp
 * @lcpr version=30307
 *
 * [707] 设计链表
 */

// @lc code=start
class MyLinkedList {
private:
    struct ListNode { // 节点和链表解耦定义，方便操作，比如虚拟头结点定义
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    ListNode* dummy; // 虚拟头节点
    int size; // 链表长度
public:
    MyLinkedList() {
        dummy = new ListNode(-1);
        size = 0;
    }

    int get(int index) {
        if(index < 0 || index >= size) {
            return -1;
        }
        ListNode* cur = dummy->next;
        for(int i=0;i<index;i++) { // 从0索引向后移动index次
            cur = cur->next; // 最后cur指向索引为index的节点
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = dummy->next; // 头插法
        dummy->next = newNode;
        size++;  // 记得记录size的变化
    }
    
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        ListNode* cur = dummy; // debug注意：考虑链表为空的情况
        while(cur->next != NULL) { // 移动指针到末尾
            cur = cur->next;
        }
        cur->next = newNode;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index > size) {
            return ;
        } else if(index == size) {
            addAtTail(val);
        } else if(index == 0) {
            addAtHead(val);
        } else {
            ListNode* newNode = new ListNode(val);
            ListNode* cur = dummy;
            for(int i=0; i<index; i++) {
                cur = cur->next; // 把cur-next指向索引为index的位置，而不是cur指向index的位置
            }
            newNode->next = cur->next;
            cur->next = newNode;
            size++;
        }
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index >= size) {
            return ;
        }
        ListNode* cur = dummy;
        for(int i=0; i <index; i++) {
            cur = cur->next; // 依旧让cur->next指向索引为index的位置
        }
        ListNode* toDelete = cur->next;
        cur->next = cur->next->next;
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

