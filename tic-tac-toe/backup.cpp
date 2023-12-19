#include <iostream>
#include <vector>

enum class Player {
    None,
    X,
    O
};

struct Move {
    int row;
    int col;
    Player player;
};

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::X) {}

    void makeMove(int row, int col) {
        if (isValidMove(row, col)) {
            moves.push_back({row, col, currentPlayer});
            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        }
    }

    void undoMove() {
        if (!moves.empty()) {
            moves.pop_back();
            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        }
    }

    bool isGameOver() {
        return isBoardFull() || hasPlayerWon(Player::X) || hasPlayerWon(Player::O);
    }

    Player getCurrentPlayer() {
        return currentPlayer;
    }

    void printBoard() {
        std::cout << "Tic Tac Toe Board:" << std::endl;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                Player player = getPlayerAtPosition(row, col);
                char symbol = '-';
                if (player == Player::X) {
                    symbol = 'X';
                } else if (player == Player::O) {
                    symbol = 'O';
                }
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }
    }

private:
    bool isValidMove(int row, int col) {
        for (const Move& move : moves) {
            if (move.row == row && move.col == col) {
                return false;
            }
        }
        return true;
    }

    bool isBoardFull() {
        return moves.size() == 9;
    }

    bool hasPlayerWon(Player player) {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; i++) {
            if (movesInRow(i, player) == 3 || movesInColumn(i, player) == 3) {
                return true;
            }
        }
        if (movesInDiagonal(player) == 3 || movesInAntiDiagonal(player) == 3) {
            return true;
        }
        return false;
    }

    int movesInRow(int row, Player player) {
        int count = 0;
        for (const Move& move : moves) {
            if (move.row == row && move.player == player) {
                count++;
            }
        }
        return count;
    }

    int movesInColumn(int col, Player player) {
        int count = 0;
        for (const Move& move : moves) {
            if (move.col == col && move.player == player) {
                count++;
            }
        }
        return count;
    }

    int movesInDiagonal(Player player) {
        int count = 0;
        for (const Move& move : moves) {
            if (move.row == move.col && move.player == player) {
                count++;
            }
        }
        return count;
    }

    int movesInAntiDiagonal(Player player) {
        int count = 0;
        for (const Move& move : moves) {
            if (move.row + move.col == 2 && move.player == player) {
                count++;
            }
        }
        return count;
    }

    Player getPlayerAtPosition(int row, int col) {
        for (const Move& move : moves) {
            if (move.row == row && move.col == col) {
                return move.player;
            }
        }
        return Player::None;
    }

    std::vector<Move> moves;
    Player currentPlayer;
};

int main() {
    TicTacToe game;
    while (!game.isGameOver()) {
        game.printBoard();
        int row, col;
        std::cout << "Player " << static_cast<int>(game.getCurrentPlayer()) << ", enter your move (row col): ";
        std::cin >> row >> col;
        game.makeMove(row, col);
    }
    game.printBoard();
    std::cout << "Game over!" << std::endl;
    return 0;
}
