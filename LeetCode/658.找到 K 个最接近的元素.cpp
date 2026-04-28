/*
 * @lc app=leetcode.cn id=658 lang=cpp
 * @lcpr version=30403
 *
 * [658] 找到 K 个最接近的元素
 */

// @lc code=start
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // 方法一：中心扩散
        // 把初始的左右指针放在 x 插入点的两侧
        // int r = lower_bound(arr.begin(), arr.end(), x) - arr.begin(); 
        // int l = r - 1;
        // while(k--) {
        //     if(l < 0) {
        //         // 左边到头，只能向右扩
        //         r++;
        //     } else if(r >= arr.size()) {
        //         l--;
        //     } else if(x - arr[l] <= arr[r] - x) {
        //         // 左边更近，或者距离一样但左边更小
        //         l--;
        //     } else {
        //         r++;
        //     }
        // }
        // // 此时 l 和 r分别各多走一步，真正区间 [l+1, r-1]
        // // 迭代器是左闭右开的
        // return vector<int>(arr.begin() + l + 1, arr.begin() + r); 

        // 方法二：一开始我的想法，维持[l, r]区间内是答案
        // int n = arr.size();
        // int pos = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        
        // // 1. 寻找真正的“初始锚点”
        // // pos 可能是越界的，也可能 pos-1 比 pos 更接近 x，我们需要先敲定起始的 1 个元素
        // int start = pos;
        // if (pos == n) {
        //     start = n - 1; // 越界了，最后一个元素最接近
        // } else if (pos > 0 && x - arr[pos - 1] <= arr[pos] - x) {
        //     start = pos - 1; // 左边那个离得更近，或者距离一样但更小
        // }
        
        // // 2. 初始化真实区间，此时区间内只有 1 个元素
        // int l = start, r = start;
        // vector<int> ans;
        // while(r - l + 1 < k) {
        //     if(l == 0) {
        //         r++;
        //     } else if(r == n - 1) {
        //         l--;
        //     } else {
        //         if(x - arr[l-1] <= arr[r+1] - x) {
        //             l--;
        //         } else {
        //             r++;
        //         }
        //     }
        // }
        // // 答案区间[l, r]
        // for(int i = l; i <= r; i++) {
        //     ans.push_back(arr[i]);
        // }
        // return ans;


        // 方案三：排除法
        int l = 0, r = arr.size() - 1;
        // 窗口内的元素个数大于k，就缩小窗口
        while(r - l + 1 > k) {
            if(x - arr[l] > arr[r] - x) {
                l++; // 踢掉l
            } else {
                r--; // 相等或者右边远都踢r
            }
        }
        // 最后[l, r]是答案,注意迭代器左闭右开
        return vector<int>(arr.begin()+l, arr.begin()+r+1);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n4\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2,3,4,5]\n4\n-1\n
// @lcpr case=end

 */

