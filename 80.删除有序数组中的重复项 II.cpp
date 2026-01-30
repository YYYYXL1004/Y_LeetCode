/*
 * @lc app=leetcode.cn id=80 lang=cpp
 * @lcpr version=30307
 *
 * [80] 删除有序数组中的重复项 II
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n;

        // 方法一：只要当前元素和 slow-2 位置不同，就可以写入
        // int slow = 2;
        // for(int fast = 2; fast < n; fast++) {
        //     if(nums[fast] != nums[slow-2]) {
        //         nums[slow++] = nums[fast];
        //     }
        // }
        // return slow;

        // 方法二：到重复元素时，用内层循环跳过多余的，只保留两个
        int slow = 0, fast = 0;
        while(fast < n) {
            int x= nums[fast];
            int count = 0;
            while(fast < n && nums[fast] == x) {
                fast++;
                count++;
            }
            int writeCount = min(count, 2);
            for(int i = 0; i < writeCount; i++) {
                nums[slow++] = x;
            }
        }
        return slow;        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,2,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,1,2,3,3]\n
// @lcpr case=end

 */

