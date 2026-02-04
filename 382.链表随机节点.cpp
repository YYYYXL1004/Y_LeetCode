/*
 * @lc app=leetcode.cn id=382 lang=cpp
 * @lcpr version=30307
 *
 * [382] 链表随机节点
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

// 方法1：数组存储（推荐）
// 时间：构造 O(n)，getRandom O(1)
// 空间：O(n)
// class Solution {
// private:
//     vector<int> nums;  // 存储链表所有值
    
// public:
//     Solution(ListNode* head) {
//         // 遍历链表，将所有值存入数组
//         while (head) {
//             nums.push_back(head->val);
//             head = head->next;
//         }
//     }
    
//     int getRandom() {
//         // 从数组中随机返回一个元素
//         return nums[rand() % nums.size()];
//     }
// };

// 方法2：蓄水池抽样（Reservoir Sampling）
// 时间：构造 O(1)，getRandom O(n)
// 空间：O(1)
// 原理：第 i 个节点以 1/i 概率被选中，最终每个节点被选中概率都是 1/n
// 证明：
// 第1个节点：被选中概率 = 1 × (1 - 1/2) × (1 - 1/3) × ... × (1 - 1/n) = 1/n
// 第k个节点：以 1/k 概率选中，后续不被替换的概率 = k/(k+1) × (k+1)/(k+2) × ... × (n-1)/n = k/n，总概率 = (1/k) × (k/n) = 1/n

class Solution {
private:
    ListNode* head;  // 保存链表头指针
    
public:
    Solution(ListNode* head) : head(head) {}
    
    int getRandom() {
        int result = 0;
        int count = 0;
        ListNode* curr = head;
        
        // 蓄水池抽样
        while (curr) {
            count++;
            // 以 1/count 的概率选择当前节点
            if (rand() % count == 0) {
                result = curr->val;
            }
            curr = curr->next;
        }
        
        return result;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
// @lc code=end



/*
// @lcpr case=start
// ["Solution","getRandom","getRandom","getRandom","getRandom","getRandom"]\n[[[1,2,3]],[],[],[],[],[]]\n
// @lcpr case=end

 */

