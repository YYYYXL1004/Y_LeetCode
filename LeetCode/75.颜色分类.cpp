/*
 * @lc app=leetcode.cn id=75 lang=cpp
 * @lcpr version=30307
 *
 * [75] 颜色分类
 */

// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 方法1：双指针进阶
        // // 定义[0, p0)为元素0的区间，左闭右开
        // // 定义(p2,n-1)为元素2的区间，左开右闭
        // int p0 = 0, p2 = nums.size() - 1;
        // int p = 0;

        // while(p <= p2) {
        //     if(nums[p] == 0) {
        //         swap(nums[p0], nums[p]);
        //         p0++;
        //         p++; // 交换0后p也要移动，因为从p0交换来的一定是0或1
        //     } else if(nums[p] == 2) {
        //         swap(nums[p], nums[p2]);
        //         p2--;
        //         // 注意：这里p不移动，因为从p2交换来的元素还未处理
        //     } else {
        //         p++;
        //     }
        // }

        // 方法2：计数排序
        vector<int> count(3, 0); // 统计0， 1, 2出现次数
        for(int i : nums) {
            count[i]++;
        }
        int index = 0;
        for(int element = 0; element < 3; element++) {
            for(int i = 0; i < count[element]; i++) {
                nums[index++] = element; 
            }
        }
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,0,2,1,1,0]\n
// @lcpr case=end

// @lcpr case=start
// [2,0,1]\n
// @lcpr case=end

 */

