/*
 * @lc app=leetcode.cn id=51 lang=cpp
 * @lcpr version=30307
 *
 * [51] N 皇后
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> res;

    // 路径：board 中小于 row 的那些行都已经成功放置了皇后
    // 选择列表：第 row 行的所有列都是放置皇后的选择
    // 结束条件：row 超过 board 的最后一行
    void backtrack(vector<string>& board, int row) {
        // 触发结束条件
        if(row == board.size()) {
            res.push_back(board);
            return;
        }
        int n = board[row].size();
        for(int col = 0; col < n; col++) {
            if(!isValid(board, row, col)) continue; 
            board[row][col] = 'Q';
            backtrack(board, row + 1);
            board[row][col] = '.';
        }
    }
    // 是否可以在 board[row][col] 放置皇后？
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        // 检查列是否有皇后相互冲突
        for(int i = 0; i < row; i++) {
            if(board[i][col] == 'Q') return false;
        }
        // 检查右上方是否有皇后互相冲突
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if(board[i][j] == 'Q') return false;
        }
        // 检查左上方是否有皇后互相冲突
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if(board[i][j] == 'Q') return false;
        }
        return true;
    }

    vector<vector<string>> solveNQueens(int n) {
        // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

