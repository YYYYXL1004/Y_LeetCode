/*
 * @lc app=leetcode.cn id=160 lang=cpp
 * @lcpr version=30307
 *
 * [160] 相交链表
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int len1 = 0, len2 = 0;
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while(p1 != nullptr) {
            len1++;
            p1 = p1->next;
        }
        while(p2 != nullptr) {
            len2++;
            p2 = p2->next;
        }
        p1 = headA, p2 = headB;
        if(len1 > len2) { // 让p1 p2到末尾距离相等
             for(int i = 0; i<len1-len2; i++) {
                p1 = p1->next;
             }
        } else {
            for(int i = 0; i<len2-len1; i++) {
                p2 = p2->next;
             }
        }
        // 两种情况，p1 p2不相交，一块走到末尾nullptr
        // 或者相交 p1==p2
        while(p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 8\n[4,1,8,4,5]\n[5,6,1,8,4,5]\n2\n3\n
// @lcpr case=end

// @lcpr case=start
// 2\n[1,9,1,2,4]\n[3,2,4]\n3\n1\n
// @lcpr case=end

// @lcpr case=start
// 0\n[2,6,4]\n[1,5]\n3\n2\n
// @lcpr case=end

 */

