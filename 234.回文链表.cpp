/*
 * @lc app=leetcode.cn id=234 lang=cpp
 * @lcpr version=30307
 *
 * [234] 回文链表
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
    // // 方法一：转化为数组 O(N)，O(N)
    // bool isPalindrome(ListNode* head) {
    //     vector<int> v;
    //     ListNode* cur = head;
    //     while(cur) {
    //         v.push_back(cur->val);
    //         cur = cur->next;
    //     }
    //     //双指针判断回文
    //     int left = 0, right = v.size() - 1;
    //     while(left < right) {
    //         if(v[left] != v[right]) {
    //             return false;
    //         }
    //         left++;
    //         right--;
    //     }
    //     return true;
    // }

    // 方法二：快慢指针+反转后半部分 O(N),O(1)
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        // 快慢指针找中点
        ListNode *fast = head, *slow = head;
        while(fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        } // 奇数情况 slow是中点， 偶数情况：slow是左中点

        // 反转后半部分
        ListNode* head2 = reverseList(slow->next);

        // 比较前后部分
        ListNode *p1 = head, *p2 = head2;
        while(p2 != nullptr)  {// p2可能更短(在slow为奇数中点的时候)
            if(p1->val != p2->val) {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        // 复原链表（可选）
        slow->next = reverseList(head2);
        return true;
    }

    // 反转链表，返回新头结点
    // ListNode* reverseList(ListNode* head) {
    //     ListNode *pre, *cur, *nxt;
    //     pre = nullptr, cur = head, nxt = head->next;
    //     while(cur != nullptr) {
    //         cur->next = pre;
    //         pre = cur;
    //         cur = nxt;
    //         if(nxt != nullptr) nxt = nxt->next;
    //     }
    //     return pre; // 返回pre，不是cur
    // }

    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* last = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

    // 方法三：递归 
    // ListNode* left;
    // bool res = true;
    // bool isPalindrome(ListNode* head) {
    //     left = head;
    //     traverse(head);
    //     return res;
    // }
    // // 先递归到底，回溯时比较
    // void traverse(ListNode* right) {
    //     if(right == nullptr) return; //递归终止
    //     traverse(right->next); // 递归到最右边

    //     // 后序遍历位置（回溯时执行）
    //     // 此时 right 从右向左移动，left 从左向右移动
    //     if(left->val != right->val) {
    //         res =false;
    //     }
    //     left = left->next;
    // }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

 */

