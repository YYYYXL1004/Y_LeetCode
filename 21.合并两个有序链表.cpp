/*
 * @lc app=leetcode.cn id=21 lang=cpp
 * @lcpr version=30307
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(-1); // 按栈分配，无需手动释放，推荐
        // 使用工作指针p,p1,p2进行指针的移动,保证头指针引用的不变
        ListNode *p = &dummy; // 因为dummy是对象，所以需要&取地址，赋值给指针p
        ListNode *p1 = list1, *p2 = list2; 
        while(p1 != NULL && p2 != NULL) {
            if(p1->val <= p2->val) {
                p->next = p1;
                p1 = p1->next; 
            } else {
                p->next = p2;
                p2 = p2->next; 
            }
            p = p->next;
        }
        if(p1 != NULL) { // 有一方剩余就直接加到末尾
            p->next = p1;
        }
        if(p2 != NULL) {
            p->next = p2;
        }
        return dummy.next; 
        // 因为初始化使用栈分配， dummy是对象，所以要用dummy.next
        // 如果初始化使用堆分配ListNode* dummy = new ListNode(-1)
        // 那dummy就是指针，要用dumy->next
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,4]\n[1,3,4]\n
// @lcpr case=end

// @lcpr case=start
// []\n[]\n
// @lcpr case=end

// @lcpr case=start
// []\n[0]\n
// @lcpr case=end

 */

