/*
 * @lc app=leetcode.cn id=19 lang=cpp
 * @lcpr version=30307
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* p1 = dummy;
        ListNode* p2 = dummy;
        for(int i=0; i <= n; i++) {
            p1 = p1->next;
        } // p1走n+1步，假设链表长为N+1(加上虚拟头结点)
        //这里p1要走N-n步才能走到结尾，所以要让p2也走了N-n步，走到了倒数第n+1个节点
        while(p1 != NULL) { 
            p1 = p1->next;
            p2 = p2->next;
        } // 因为我们要删除倒数第n个，所以需要p2成为倒数n+1个节点
        p2->next = p2->next->next;
        // 指针只是地址，修改指针指向的内容会影响整个链表，所有指向这条链表的指针都能看到变化。
        return dummy->next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n1\n
// @lcpr case=end

 */

