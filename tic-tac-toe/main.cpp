#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class TicTacToeModel;  // Forward declaration

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}  // Add a virtual destructor to the Command class
};

class MoveCommand : public Command {
private:
    int row, col;
    char player;
    TicTacToeModel& model;

public:
    MoveCommand(int r, int c, char p, TicTacToeModel& m) : row(r), col(c), player(p), model(m) {}

    void execute() override;
    void undo() override;
};

class TicTacToeModel {
private:
    std::vector<std::vector<char>> board;
    std::vector<Command*> moves;
    char currentPlayer;

public:
    TicTacToeModel() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

    bool makeMove(int row, int col);
    bool undoMove();
    bool checkWin() const;  // Add this line
    bool checkDraw() const;  // Add this line

    const std::vector<std::vector<char>>& getBoard() const {
        return board;
    }

    std::vector<std::vector<char>>& getMutableBoard() {
        return board;
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

// Implement the MoveCommand member functions outside the class
void MoveCommand::execute() {
    model.makeMove(row, col);
}

void MoveCommand::undo() {
    model.getMutableBoard()[row][col] = ' ';
}

bool TicTacToeModel::makeMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return false; // Invalid move
    }

    board[row][col] = currentPlayer;
    moves.push_back(new MoveCommand(row, col, currentPlayer, *this));

    // Check for a win or draw
    if (checkWin()) {
        std::cout << "Player " << currentPlayer << " wins!" << std::endl;
        exit(0);
    } else if (checkDraw()) {
        std::cout << "It's a draw!" << std::endl;
        exit(0);
    }

    // Toggle the current player for the next move
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    return true; // Valid move
}

bool TicTacToeModel::checkWin() const {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return true;
    }

    return false;
}

bool TicTacToeModel::checkDraw() const {
    // Check if the board is full
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // The board is not full
            }
        }
    }
    return true; // The board is full, and it's a draw
}

bool TicTacToeModel::undoMove() {
    if (moves.empty()) {
        return false; // No moves to undo
    }

    Command* lastMove = moves.back();
    lastMove->undo();
    moves.pop_back();
    delete lastMove;

    // Toggle the current player back to the one who made the undone move
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    return true; // Undo successful
}

class TextView {
public:
    static void display(const TicTacToeModel& model) {
        const auto& board = model.getBoard();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << board[i][j];
                if (j < 2) std::cout << " | ";
            }
            std::cout << std::endl;

            if (i < 2) std::cout << "---------" << std::endl;
        }

        std::cout << "Current player: " << model.getCurrentPlayer() << std::endl;
        std::cout << std::endl;
    }
};


class SFMLView {
private:
    sf::RenderWindow window;

public:
    SFMLView() : window(sf::VideoMode(300, 300), "Tic-Tac-Toe") {}

    void display(const TicTacToeModel& model) {
    window.clear();

    const auto& board = model.getBoard();
    sf::Font font;
    font.loadFromFile("c:/Windows/Fonts/COMICBD.TTF");

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Draw X or O
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(50);
            text.setPosition(j * 100 + 30, i * 100 + 30);
            text.setString(std::string(1, board[i][j]));
            window.draw(text);
        }
    }

    // Draw grid lines
    for (int i = 1; i < 3; ++i) {
        sf::Vertex horizontalLine[] = {
            sf::Vertex(sf::Vector2f(0, i * 100)),
            sf::Vertex(sf::Vector2f(300, i * 100))
        };
        sf::Vertex verticalLine[] = {
            sf::Vertex(sf::Vector2f(i * 100, 0)),
            sf::Vertex(sf::Vector2f(i * 100, 300))
        };

        window.draw(horizontalLine, 2, sf::Lines);
        window.draw(verticalLine, 2, sf::Lines);
    }

    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(20);
    playerText.setPosition(0, 250);
    playerText.setString("Current player: " + std::string(1, model.getCurrentPlayer()));
    window.draw(playerText);

    window.display();
}


    bool isOpen() const {
        return window.isOpen();
    }

    bool pollEvent(sf::Event& event) {
        return window.pollEvent(event);
    }

    void closeWindow() {
        window.close();
    }
};

int main() {
    char choice;
    std::cout << "Choose display mode (T for terminal, G for GUI): ";
    std::cin >> choice;

    TicTacToeModel model;

    if (choice == 'T' || choice == 't') {
        // Terminal mode
        TextView textView;

        while (true) {
            textView.display(model);

            int row, col;
            std::cout << "Enter row and column (0-2) separated by space: ";
            std::cin >> row >> col;

            model.makeMove(row, col);
        }
    } else if (choice == 'G' || choice == 'g') {
        // GUI mode
        SFMLView sfmlView;

        while (sfmlView.isOpen()) {
            sf::Event event;
            while (sfmlView.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    sfmlView.closeWindow();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int row = event.mouseButton.y / 100;
                    int col = event.mouseButton.x / 100;
                    model.makeMove(row, col);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U) {
                    model.undoMove();
                }
            }

            sfmlView.display(model);
        }
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
    }

    return 0;
}
