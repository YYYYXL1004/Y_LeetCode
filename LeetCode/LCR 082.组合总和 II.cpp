/*
 * @lc app=leetcode.cn id=LCR 082 lang=cpp
 * @lcpr version=30402
 *
 * [LCR 082] 组合总和 II
 */

// @lc code=start
class Solution {
public:
    vector<int> track;
    vector<vector<int>> res;
    int sum = 0;

    // 方法一：事后去重，比较低效
    // void backtrace(vector<int>& nums, int target, int start) {
    //     if(target < sum || start > nums.size()) return ;

    //     if(target == sum) {
    //         // res.insert(track);
    //         // return ;
    //         if(find(res.begin(), res.end(), track) == res.end()) {
    //             res.push_back(track);
    //             return ;
    //         } // 解集不能包含重复的组合
    //     }
    //     for(int i = start; i < nums.size(); i++) {
    //         sum += nums[i];
    //         track.push_back(nums[i]);
    //         backtrace(nums, target, i+1);
    //         sum -= nums[i];
    //         track.pop_back();
    //     }
    // }

    void backtrace(vector<int>& nums, int target, int start) {
        if(target < sum) return ;
        if(target == sum) {
            res.push_back(track);
            return ;
        }
        for(int i = start; i < nums.size(); i++) {
            if(i != start && nums[i] == nums[i - 1]) continue; // 跳过同层重复节点
            sum += nums[i];
            track.push_back(nums[i]);
            backtrace(nums, target, i+1);
            sum -= nums[i];
            track.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtrace(candidates, target, 0);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,1,2,7,6,1,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2,5,2,1,2]\n5\n
// @lcpr case=end

 */

