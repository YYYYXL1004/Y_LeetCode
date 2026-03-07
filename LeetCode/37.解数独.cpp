/*
 * @lc app=leetcode.cn id=37 lang=cpp
 * @lcpr version=30307
 *
 * [37] 解数独
 */

// @lc code=start
class Solution {
public:
    bool found = false; // 标记是否已经找到可行解

    // 路径：board 中小于 index 的位置所填的数字
    // 选择列表：数字 1~9
    // 结束条件：整个 board 都填满数字
    void backtrack(vector<vector<char>>& board, int index) {
        int m = 9, n = 9;
        int i = index / n, j = index % n;

        if(found) return;   // 第1个判断：防止继续深入搜索
        if(index == m * n) { // 因为存在唯一解，所以遍历一遍一定有解
            found = true;
            return;
        }
        if(board[i][j] != '.') {
            // 如果有预设数字，不用我们穷举
            backtrack(board, index + 1);
            return;
        }
        for(char ch = '1'; ch <= '9'; ch++) {
            // 剪枝，遇到不合法的数字跳过
            if(!isValid(board, i, j, ch)) continue;

            board[i][j] = ch;  
            backtrack(board, index + 1);
            if(found) return ;  // 第2个判断：防止回溯（撤销选择）
            // 如果找到一个可行解，立即结束
            // 不要撤销选择，否则 board[i][j] 会被重置为 '.'
            board[i][j] = '.';
        }
    }

    // 判断是否可以在 (r, c) 位置放置数字 num
    bool isValid(vector<vector<char>>& board, int r, int c, char num) {
        for(int i = 0; i < 9; i++) {
            // 判断行是否存在重复
            if(board[r][i] == num) return false;
            // 判断列是否存在重复
            if(board[i][c] == num) return false;
            // 判断 3 * 3方框是否重复
            // 整数除法 r/3 定位你在哪个大宫格，乘 3 得到宫格左上角坐标
            // 再加 i/3 和 i%3 在小宫格内游走。
            if(board[(r / 3) * 3 + i / 3][(c / 3) * 3 + i % 3] == num) return false;
        }
        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]\n
// @lcpr case=end

 */

