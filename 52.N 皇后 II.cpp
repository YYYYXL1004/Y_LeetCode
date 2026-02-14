/*
 * @lc app=leetcode.cn id=52 lang=cpp
 * @lcpr version=30400
 *
 * [52] N 皇后 II
 */

// @lc code=start
class Solution {
public:
    int res = 0;

    void backtrack(vector<string>& board, int row, int n) {
        if(row == n) {
            res++;
            return ;
        }

        for(int col = 0; col < n; col++) {
            if(!isValid(board, row, col, n)) continue;
            board[row][col] = 'Q';
            backtrack(board, row + 1, n);
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col, int n) {
        // 检查列
        for(int i = 0; i < row; i++) {
            if(board[i][col] == 'Q') return false;
        }
        // 检查右上
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if(board[i][j] == 'Q') return false;
        }
        // 检查左上
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if(board[i][j] == 'Q') return false;
        }
        return true;
    }


    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0, n);
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

