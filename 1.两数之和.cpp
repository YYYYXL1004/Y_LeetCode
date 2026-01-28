/*
 * @lc app=leetcode.cn id=1 lang=cpp
 * @lcpr version=30307
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 方法一：记录原始下标 排序前把值和原始下标绑定，排序后再取回原始下标
        // int n = nums.size();
        // vector<pair<int, int>> arr(n); // 存放原始值和下标的对应关系
        // for(int i = 0; i < n; i++) {
        //     arr[i] = {nums[i], i};
        // }
        // sort(arr.begin(), arr.end()); // 按值排序
        // int left = 0, right = n - 1;
        // while(left < right) {
        //     int sum = arr[left].first + arr[right].first;
        //     if(sum == target) {
        //         return vector<int>{arr[left].second, arr[right].second};
        //     } else if(sum < target) {
        //         left++;
        //     } else {
        //         right--;
        //     }
        // }
        // return vector<int>{-1, -1};

        // 方法二：哈希表（一次遍历）(推荐)
        // unordered_map<int,int> mp; // 值->下标
        // for(int i = 0; i < nums.size(); i++) {
        //     int need = target - nums[i];
        //     if(mp.count(need)) {
        //         return {mp[need], i};
        //     }
        //     mp[nums[i]] = i; // 存入 val -> index的映射
        // }
        // return {};

        // 方法三：哈希表（两次遍历）
        unordered_map<int,int> mp;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            mp[nums[i]] = i;    
        }
        for(int i = 0; i < n; i++) {
            int need = target - nums[i];
            if(mp.count(need) && mp[need] != i) {  // 注意：不能是自己
                return {i, mp[need]};  // 遍历两边只会存储最后出现的索引
            }
        }
        return {};
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,7,11,15]\n9\n
// @lcpr case=end

// @lcpr case=start
// [3,2,4]\n6\n
// @lcpr case=end

// @lcpr case=start
// [3,3]\n6\n
// @lcpr case=end

 */

