/*
 * @lc app=leetcode.cn id=142 lang=cpp
 * @lcpr version=30307
 *
 * [142] 环形链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head, *slow = head;
        while(fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) {
                break; // 相遇就退出
            }
        }  // 假设慢指针走了k步， 相遇点距离成环处m步。
        // 所以成环点距离起点为k-m步
        if(fast == nullptr || fast->next == nullptr) {
            return nullptr; // 没相遇就退出说明没有环
        }  // 推荐使用nullptr是空指针类型 而NULL通常是int
        slow = head;
        while(slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,0,-4]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [1]\n-1\n
// @lcpr case=end

 */

