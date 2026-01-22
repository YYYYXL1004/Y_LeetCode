/*
 * @lc app=leetcode.cn id=86 lang=cpp
 * @lcpr version=30307
 *
 * [86] 分隔链表
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
    ListNode* partition(ListNode* head, int x) {
        ListNode *dummy1 = new ListNode(-1);
        ListNode *dummy2 = new ListNode(-1);
        ListNode *p1 = dummy1, *p2 = dummy2; // 定义工作指针
        ListNode *p = head;

        while(p!=NULL) {
            if(p->val < x) { // 比x小的放到p1
                p1->next = p;
                p1 = p1->next;
            } else {
                p2->next = p;
                p2 = p2->next;
            }
            // 把p和后续节点切割再向后移动，避免成环
            ListNode *temp = p->next;
            p->next = NULL;
            p = temp;
        }
        p1->next = dummy2->next; // 连接两条链表
        return dummy1->next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,4,3,2,5,2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [2,1]\n2\n
// @lcpr case=end

 */

