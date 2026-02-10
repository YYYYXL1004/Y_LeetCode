/*
 * @lc app=leetcode.cn id=23 lang=cpp
 * @lcpr version=30307
 *
 * [23] 合并 K 个升序链表
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        
        // Lambda表达式: [捕获列表](参数列表) -> 返回类型 { 函数体 }
        // 1. 最简形式
        // auto f1 = []() { return 42; };
        // 2. 带参数
        // auto f2 = [](int a, int b) { return a + b; };
        // 3. 省略返回类型（自动推导）
        // auto f3 = [](int x) { return x * 2; };
        // 4. 显式指定返回类型
        // auto f4 = [](int x) -> double { return x / 2.0; };
        // 实际应用场景
        // 排序
        // vector<int> v = {3, 1, 4, 1, 3};
        // sort(v.begin(), v.end(), [](int a, int b) {return a > b; }); // 降序
        // // 查找
        // auto it = find_if(v.begin(), v.end(), [](int x) {return x > 3; });
        // // 优先队列
        // auto cmp = [] (ListNode *a, ListNode* b) {
        //     return a->val > b->val;
        // };
        // priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        // 优先队列，小顶堆 
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };  // 优先队列的比较器，比较谁先沉底
        priority_queue<
            ListNode*,          // 元素类型
            vector<ListNode*>,  // 底层容器
            decltype(cmp)       // 比较器类型
        > pq(cmp);              // 构造时传入比较器实例

        // 把k个链表的 头结点都加入小顶堆
        for(ListNode* head : lists) {
            if(head != NULL) {
                pq.push(head);
            }
        }

        while(!pq.empty()) {
            ListNode* node = pq.top(); // 获取最小节点
            pq.pop();
            p->next = node;
            if(node->next != NULL) {
                pq.push(node->next);
            }
            p = p->next; // p移动向前
        }
        return dummy->next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,4,5],[1,3,4],[2,6]]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [[]]\n
// @lcpr case=end

 */

