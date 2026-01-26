/*
 * @lc app=leetcode.cn id=641 lang=cpp
 * @lcpr version=30307
 *
 * [641] 设计循环双端队列
 */

// @lc code=start
class MyCircularDeque {
private:    
    vector<int> data;
    int front, rear, capacity;  // front: 指向队首元素  rear:指向队尾元素的下一个空位
public:
    MyCircularDeque(int k) {
        capacity = k + 1;
        data.resize(capacity);
        front = 0;
        rear = 0;
    }
    // 环形数组技巧
    // 下一个位置 = (当前位置 + 1) % capacity    // 向后走
    // 上一个位置 = (当前位置 - 1 + capacity) % capacity  // 向前走
    bool insertFront(int value) {
        if(isFull()) return false;
        front = (front - 1 + capacity) % capacity; // 向前移动
        data[front] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull()) return false;
        data[rear] = value;
        rear = (rear + 1) % capacity; // 向后移动
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()) return false;
        front = (front + 1) % capacity;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        return true;
    }
    
    int getFront() {
        if(isEmpty()) return -1;
        return data[front];
    }
    
    int getRear() {
        if(isEmpty()) return -1;
        return data[(rear - 1 + capacity) % capacity];
    }
    
    bool isEmpty() {
        return front == rear;
    }
    
    bool isFull() {
        return (rear + 1) % capacity == front;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MyCircularDeque","insertLast","insertLast","insertFront","insertFront","getRear","isFull","deleteLast","insertFront","getFront"]\n[[3],[1],[2],[3],[4],[],[],[],[4],[]]\n
// @lcpr case=end

 */

