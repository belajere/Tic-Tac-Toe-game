#include <iostream>
#include <vector>
using namespace std;

class Board {
    private:
        vector<vector<char>> grid;

    public:
        Board() : grid(3, vector<char>(3,' ')) {}
        
    void display() const { // display and print the board
        int numRows = grid.size();
        int numCols = grid[0].size();
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    cout << (grid[i][j] == ' ' ? '.' : grid[i][j] )<< " ";
                }
                cout << endl;
            }
    }
    bool update(int row, int column, char playerSymbol) {  //update(int row, int column, char playerSymbol) //update the board
    if (grid[row][column] == ' ') {
            grid[row][column] = playerSymbol;
            return true;
        }
        return false;
    }
    bool checkWin() {   //checkWin() //check for winner
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (grid[0][j] != ' ' && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
            return true;
        }
        if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
            return true;
        }

        return false;

    }
        //checkDraw() //check if there is a draw
    bool checkDraw() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};    

class Player {
public:
    char symbol;
    Player(char sym) : symbol(sym) {}
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

    void switchPlayer() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    void playTurn() {
        
        int row, col;
        cout << "Player " << currentPlayer->symbol << ", enter ROW (1-3): ";
        cin >> row;
        cout << "COLUMN: ";
        cin >> col;
        row -= 1; // Adjusting for 0-based index
        col -= 1; // Adjusting for 0-based index

        if (row < 0 || row>2 || col<0 || col>2) {
            cout<< "invalid input, try again"<<endl;
            return;
        }
        if (board.update(row, col, currentPlayer->symbol)) {
            if (board.checkWin()) {
                board.display();
                cout << "Player " << currentPlayer->symbol << " wins!" << endl;
                exit(0); // End the game
            }
            if (board.checkDraw()) {
                board.display();
                cout << "The game is a draw!" << endl;
                exit(0); // End the game
            }
            switchPlayer();
        } else {
            cout << "Invalid move, try again." << endl;
        }
    }

public:
    Game() : player1('X'), player2('O'), currentPlayer(&player1) {}

    void start() {
        while (true) {
            board.display();
            playTurn();
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}