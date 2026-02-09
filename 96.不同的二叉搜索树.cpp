/*
 * @lc app=leetcode.cn id=96 lang=cpp
 * @lcpr version=30307
 *
 * [96] 不同的二叉搜索树
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> memo; // 备忘录，降低时间复杂度
    int numTrees(int n) {
        // 初始化备忘录为0
        memo = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        return count(1, n);
    }

    // 闭区间[lo, hi]的数字能组成count(lo, hi)种BST
    int count(int lo, int hi) {
        if(lo > hi) return 1; // base case 空节点也是一种情况
        if(memo[lo][hi] != 0) return memo[lo][hi]; // 查备忘录
        int res = 0;
        for(int i = lo;i <= hi; i++) {
            // i的值作为根节点root
            int left = count(lo, i-1);
            int right = count(i+1, hi);
            res += left * right;
        }
        memo[lo][hi] = res; // 结果存入备忘录
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

