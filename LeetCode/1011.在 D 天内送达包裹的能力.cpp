/*
 * @lc app=leetcode.cn id=1011 lang=cpp
 * @lcpr version=30307
 *
 * [1011] 在 D 天内送达包裹的能力
 */

// @lc code=start
class Solution {
public:
    // 当运载能力为 x 时，需要 f(x) 天运完所有货物
    int f(vector<int>& weights, int x) {
        int days = 0;
        for(int i = 0; i < weights.size();) {
            int cap = x;
            while(i < weights.size()) {
                if(cap < weights[i]) break;
                else cap -= weights[i];
                i++;
            }
            days++;
        }
        return days;   
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int left = 0;
        int right = 1;
        for(int w : weights) {
            left = max(left, w); // 船的运载能力至少要能装下最重的那个包裹
            right += w;
        }
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(f(weights, mid) <= days) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5,6,7,8,9,10]\n5\n
// @lcpr case=end

// @lcpr case=start
// [3,2,2,4,1,4]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,1,1]\n4\n
// @lcpr case=end

 */

