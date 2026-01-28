/*
 * @lc app=leetcode.cn id=83 lang=cpp
 * @lcpr version=30307
 *
 * [83] 删除排序链表中的重复元素
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
    ListNode* deleteDuplicates(ListNode* head) {
        // 方法一：单指针遍历法
        // 思路：遍历链表，当前节点与下一节点值相同时，跳过下一节点
        // ListNode* dummy = new ListNode(-101);
        // dummy->next = head;
        // ListNode* p = dummy;
        // while(p->next != nullptr && p->next->next != nullptr) {
        //     if(p->next->val == p->next->next->val) {
        //         p->next = p->next->next;  // 跳过重复节点
        //     } else {
        //         p = p->next;  // 不重复则移动指针
        //     }
        // }
        // return dummy->next;

        // 方法二：快慢指针法（类似数组去重）
        // 思路：slow指向不重复序列的末尾，fast遍历整个链表
        // 当fast遇到与slow不同的值时，将其接到slow后面
        if(head == nullptr) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != nullptr) {
            if(fast->val != slow->val) {  // 注意：应该是不等于时才移动slow
                // 将不重复的节点接到slow后面
                slow->next = fast;
                slow = slow->next;
            }
            fast = fast->next;
        }
        // 断开与后面重复元素的链接
        slow->next = nullptr;
        return head;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2,3,3]\n
// @lcpr case=end

 */

