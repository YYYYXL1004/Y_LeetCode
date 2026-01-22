/*
 * @lc app=leetcode.cn id=82 lang=cpp
 * @lcpr version=30307
 *
 * [82] 删除排序链表中的重复元素 II
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
    // 方法1：分隔链表
    // ListNode* deleteDuplicates(ListNode* head) {
    //     ListNode* dummy1 = new ListNode(-101); // 放不重复的数字
    //     ListNode* dummy2 = new ListNode(-101); // 放重复数字
    //     ListNode* p1 = dummy1, *p2 = dummy2;
    //     ListNode* p = head;
    //     while(p != nullptr) {
    //         if(p->next != nullptr && p->val == p->next->val || p->val == p2->val) {
    //             p2->next = p;
    //             p2 = p2->next;
    //         } else {
    //             p1->next = p;
    //             p1 = p1->next;
    //         }
    //         p = p->next;
    //         // 切断p1,p2和原链表的联系
    //         p1->next = nullptr;
    //         p2->next = nullptr;
    //     }
    //     return dummy1->next;
    // }
    // 方法2 直接遍历跳过
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(-101);
        dummy->next = head;
        ListNode* p = dummy;

        while(p->next != nullptr && p->next->next != nullptr) {
            if(p->next->val == p->next->next->val) {
                int dup = p->next->val;
                while(p->next != nullptr && p->next->val == dup) {
                    p->next = p->next->next; // 跳过所有重复值dup
                } 
            } else {
                p = p->next;
            }
        }
        return dummy->next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,3,4,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,1,2,3]\n
// @lcpr case=end

 */

