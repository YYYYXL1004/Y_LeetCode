/*
 * @lc app=leetcode.cn id=92 lang=cpp
 * @lcpr version=30307
 *
 * [92] 反转链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode* successor = nullptr; // 记录前n+1个节点

    // 反转前n个节点，返回新的头结点
    ListNode* reverseN(ListNode* head, int n) {
        if(n == 1) {
            // 递归终止条件：只反转1个节点
            successor = head->next; // 记录n+1个节点
            return head;
        }
        // 递归反转前n-1个节点
        ListNode* last = reverseN(head->next, n - 1);
        head->next->next = head;
        head->next = successor; // 让反转后的head连接后面的节点
        return last;
    }
public:
    // 方法二：递归
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left == 1) { // 如果left == 1，相当于反转前right个节点
            return reverseN(head, right);
        }
        // 递归：问题转化为在head->next中反转第(left-1)到(right-1)个节点
        head->next = reverseBetween(head->next, left - 1, right - 1);
        return head;
    }

    // 方法一：迭代
    // ListNode* reverseBetween(ListNode* head, int left, int right) {
    //     if(!head || !head->next || left == right) return head;
    //     ListNode *dummy = new ListNode(0);  // 创建虚拟头结点，简化边界处理
    //     dummy->next = head;
    //     ListNode* prev = dummy; // 找到待反转区间前的一个节点
    //     for(int i = 0; i < left - 1; i++) {
    //         prev = prev->next;
    //     }
    //     ListNode* beforeReverse = prev; // 记录用于最后拼接
    //     ListNode *cur = prev->next;
    //     ListNode *pre = nullptr, *nxt = nullptr; // 初始化为空
    //     int count = right - left + 1; // (right - left + 1) 是一个表达式的值，不能对它进行 -- 操作
    //     while(count--) { // 执行right - left + 1次反转操作
    //         nxt = cur->next;   // 保存下一个节点
    //         cur->next = pre;   // 反转当前节点
    //         pre = cur;         // 更新pre
    //         cur = nxt;        // 移动到下一个节点
    //     }
    //     // 反转后pre为反转后的新头结点， cur为反转区间后的第一个节点
    //     beforeReverse->next->next = cur;  // 反转区间的尾部连接后面的节点
    //     beforeReverse->next = pre;        // 前面的节点连接反转区间新头部

    //     return dummy->next;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n4\n
// @lcpr case=end

// @lcpr case=start
// [5]\n1\n1\n
// @lcpr case=end

 */

