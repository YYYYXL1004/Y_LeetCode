/*
 * @lc app=leetcode.cn id=25 lang=cpp
 * @lcpr version=30307
 *
 * [25] K 个一组翻转链表
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
    // 递归版
    // ListNode* successor = nullptr; // 记录后面n+1个节点
    // // 反转前n个节点，并返回新的头结点
    // ListNode* reverseN(ListNode* head, int n) {
    //     if(n == 1) {
    //         successor = head->next;
    //         return head;
    //     }
    //     ListNode* last = reverseN(head->next, n - 1);
    //     head->next->next = head;
    //     head->next = successor;
    //     return last;
    // }
    
    // 迭代版
    // 反转前n个节点，并返回新的头结点
    ListNode* reverseN(ListNode* head, int n) {
        if(!head || !head->next) return head;
        ListNode *pre, *cur, *nxt;
        pre = nullptr, cur = head, nxt = head->next;
        while(n--) {
            cur->next = pre;
            pre = cur;
            cur = nxt;
            if(nxt != nullptr) {  // 这里是if不是while
                nxt = nxt->next;
            }
        }
        head->next = cur;  // 想不清楚就画图，1,2,3,4翻转前3个试试
        return pre;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k == 1 || !head || !head->next) return head;
        ListNode *a = head, *b = head; // 区间[a, b)包含k个待反转节点
        for(int i = 0; i < k; i++) {
            if(b == nullptr) return head; // 不足k个直接返回原head
            b = b->next; 
        } // 最后b为 k+1 个节点
        ListNode* newHead = reverseN(a, k);
        // 此时 b 指向下一组待反转节点的头结点
        // a是第一组翻转前的头结点，连接反转后的下一组链表
        a->next = reverseKGroup(b, k); 
        return newHead;
        // 叹为观止，太nb了
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n3\n
// @lcpr case=end

 */

