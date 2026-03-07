/*
 * @lc app=leetcode.cn id=1329 lang=cpp
 * @lcpr version=30307
 *
 * [1329] 将矩阵按对角线排序
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> res(m, vector<int>(n));

        // 方法一：哈希表搭配list
        // unordered_map<int,list<int> > mp;

        // for(int i = 0; i < m; i++) {
        //     for(int j = 0; j < n; j++) {
        //         int cha = i - j;   // 每条对角线上差一样
        //         mp[cha].push_back(mat[i][j]);
        //     }
        // }
        // // // list使用sort()函数
        // // for(auto& m : mp) {
        // //     m.second.sort();
        // // }
        // // // 双向链表神力，删除非常方便
        // // for(int i = 0; i < m; i++) {
        // //     for(int j = 0; j < n; j++) {
        // //         int cha = i - j;
        // //         res[i][j] = mp[cha].front();
        // //         mp[cha].pop_front();
        // //     }
        // // }

        // 听说在尾部删除效率更高(?)但是貌似都是0（1）
        // for(auto& m : mp) m.second.sort(greater<int>());
        // for(int i = 0; i < m; i++) {
        //     for(int j = 0; j < n; j++) {
        //         int cha = i - j;
        //         res[i][j] = mp[cha].back();
        //         mp[cha].pop_back();
        //     }
        // }

        // 方法二：哈希表搭配vector
        unordered_map<int, vector<int>> mp;
        unordered_map<int, int> idx; // 记录每条对角线当前的索引
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int cha = i - j;
                mp[cha].push_back(mat[i][j]);
            }
        }

        for(auto& m : mp) {
            sort(m.second.begin(), m.second.end());
            idx[m.first] = 0; // 初始化索引
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int cha = i - j;
                res[i][j] = mp[cha][idx[cha]++]; // 按照从小到大取值
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[3,3,1,1],[2,2,1,2],[1,1,1,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]\n
// @lcpr case=end

 */

