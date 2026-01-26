/*
 * @lc app=leetcode.cn id=622 lang=cpp
 * @lcpr version=30307
 *
 * [622] 设计循环队列
 */

// @lc code=start
class MyCircularQueue {
private:
    vector<int> data;
    int front, rear, capacity;
public:
    MyCircularQueue(int k) {
        capacity = k + 1;
        data.resize(capacity);
        front = 0;
        rear = 0;
    }
    
    // 队尾插入
    bool enQueue(int value) {
        if(isFull()) return false;
        data[rear] = value;
        rear = (rear + 1) % capacity;
        return true;
    }
    
    // 队首删除
    bool deQueue() {
        if(isEmpty()) return false;
        front = (front + 1) % capacity;
        return true;
    }
    
    int Front() {
        if(isEmpty()) return -1;
        return data[front];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
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
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MyCircularQueue","enQueue","enQueue","enQueue","enQueue","Rear","isFull","deQueue","enQueue","Rear"]\n[[3],[1],[2],[3],[4],[],[],[],[4],[]]\n
// @lcpr case=end

 */

