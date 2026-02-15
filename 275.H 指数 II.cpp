/*
 * @lc app=leetcode.cn id=275 lang=cpp
 * @lcpr version=30400
 *
 * [275] H 指数 II
 */

// @lc code=start
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        // 从大到小枚举 h，找第一个满足条件的
        // for(int h = n; h >= 0; h--) {
        //     auto it = lower_bound(citations.begin(), citations.end(), h);
        //     int count = n - (it - citations.begin()); // 有count片引用大于等于h的
        //     if(count >= h)  return h;
        // }
        // return 0;
        
        int left = 0, right = n;
        while(left < right) {
            int mid = left + (right - left) / 2;
            // citations[mid] 是第 mid 篇的引用数
            // n - mid 是从 mid 到末尾的论文数
            if(citations[mid] >= n - mid) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return n - left;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,3,3,6]\n
// @lcpr case=end

// @lcpr case=start
// [100]\n
// @lcpr case=end

 */

