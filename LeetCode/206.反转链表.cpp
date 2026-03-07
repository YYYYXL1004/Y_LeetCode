/*
 * @lc app=leetcode.cn id=206 lang=cpp
 * @lcpr version=30307
 *
 * [206] 反转链表
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
public:
    ListNode* reverseList(ListNode* head) {
        // 方法一：迭代
        // if(head == nullptr || head->next == nullptr) {
        //     return head;
        // }
        // ListNode *pre, *cur, *nxt;
        // pre = nullptr, cur = head, nxt = head->next;
        // while(cur != nullptr) {
        //     // 逐个节点反转
        //     cur->next = pre;
        //     pre = cur;
        //     cur = nxt;

        //     if(nxt != nullptr) {
        //         nxt = nxt->next;
        //     }
        // }
        // // cur为nullptr，pre为头结点
        // return pre;
        
        // 方法二：迭代
        if(head == nullptr || head->next == nullptr) {
            return head;
        }  // 递归函数要有 base case，也就是这句：
        ListNode* last = reverseList(head->next);
        head->next->next = head; // 掉头
        // 当链表递归反转之后，新的头结点是 last，而之前的 head 变成了最后一个节点
        // 别忘了链表的末尾要指向 null：
        head->next = nullptr;
        return last;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

