/*
 * @lc app=leetcode.cn id=155 lang=cpp
 * @lcpr version=30307
 *
 * [155] 最小栈
 */

// @lc code=start
class MinStack {
private:
    stack<int> stk;
    stack<int> minStk; // 辅助栈，存储当前最小值

public:
    MinStack() {
        
    }
    
    void push(int val) {
        stk.push(val);
        // 如果辅助栈为空或者当前值小于等于栈顶，则入栈
        if(minStk.empty() || val <= minStk.top()) {
            minStk.push(val);
        }
    }
    
    void pop() {
        // 如果弹出的是最小值，辅助栈也要弹出
        if(stk.top() == minStk.top()) {
            minStk.pop();
        }
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minStk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MinStack","push","push","push","getMin","pop","top","getMin"]\n[[],[-2],[0],[-3],[],[],[],[]]\n
// @lcpr case=end

 */

