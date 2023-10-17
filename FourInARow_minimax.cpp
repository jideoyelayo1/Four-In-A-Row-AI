

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
private:
    string _name;
    int _number;
public:
    Player(string name, int number) {
        _name = name;
        _number = number;
    }
    int getNo() {
        return _number;
    }
    string getName() {
        return _name;
    }
};

class Game {
private:
    const unsigned int COLS = 7;
    const unsigned int ROWS = 6;
    const string playerOneChar = "X";
    const string playerTwoChar = "O";
    const string emptySpace = " ";
    int round = 0;
    bool _gameOver = false;
    bool playOneTurn = true;
    

    const Player player = Player("You", 1);
    const Player AI = Player("AI", 2);

    void setupBoard() {
        _gameOver = false;
        board.clear();
        board = vector<vector<int>>(COLS, vector<int>(ROWS, 0));
    }
    string getChar(int num) {
        if (num == 0) return emptySpace;
        return num == 1 ? playerOneChar : playerTwoChar;
    }
    bool findWinner(int playerPiece) {
        for (int i = 0; i < COLS; i++) {
            for (int j = 0; j <= ROWS - 4; j++) {
                if (board[i][j] == playerPiece &&
                    board[i][j + 1] == playerPiece &&
                    board[i][j + 2] == playerPiece &&
                    board[i][j + 3] == playerPiece) {
                    return true;
                }
            }
        }
        for (int i = 0; i <= COLS - 4; i++) {
            for (int j = 0; j < ROWS; j++) {
                if (board[i][j] == playerPiece &&
                    board[i + 1][j] == playerPiece &&
                    board[i + 2][j] == playerPiece &&
                    board[i + 3][j] == playerPiece) {
                    return true;
                }
            }
        }
        for (int i = 0; i <= COLS - 4; i++) {
            for (int j = 0; j <= ROWS - 4; j++) {
                if (board[i][j] == playerPiece &&
                    board[i + 1][j + 1] == playerPiece &&
                    board[i + 2][j + 2] == playerPiece &&
                    board[i + 3][j + 3] == playerPiece) {
                    return true;
                }
            }
        }
        for (int i = 3; i < COLS; i++) {
            for (int j = 0; j <= ROWS - 4; j++) {
                if (board[i][j] == playerPiece &&
                    board[i - 1][j + 1] == playerPiece &&
                    board[i - 2][j + 2] == playerPiece &&
                    board[i - 3][j + 3] == playerPiece) {
                    return true;
                }
            }
        }
        return false;
    }
    bool CheckWinner() {
        return findWinner(1) || findWinner(2);
    }
    bool IsFull(int col) {
        return board[col][ROWS-1] != 0;
    }
    bool allIsFilled() {
        for (int i = 0; i < COLS; i++)
            if (!IsFull(i)) return false;
        return true;
    }
    bool isDraw() {
        return allIsFilled();
    }
    void dropPiece(Player player, int col) {

        
        if (_gameOver) {
            setupBoard();
        }
        
        if (col < 0 || col >= COLS || IsFull(col)) {
            return;
        }
        int row = 0;
        while (row < ROWS && board[col][row] != 0) {
            //cout << col << " " << row << endl;
            row++;
        }

        board[col][row] = player.getNo();
    }
    int dropPieceAT(Player player, int col) {


        if (_gameOver) {
            setupBoard();
        }

        int row = 0;
        while (row < ROWS && board[col][row] != 0) {
            //cout << col << " " << row << endl;
            row++;
        }

        board[col][row] = player.getNo();
        return row;
    }
    void checkUser(int pos) {
        if (findWinner(pos)) {
            cout << (pos == 1 ? "You win" : "AI wins") << " \n";
            _gameOver = true;
            setupBoard();
        }
    }
    void gameCheck() {
        checkUser(1);
        checkUser(2);
    }
    bool isGameOver() {
        return isDraw() || CheckWinner();
    }
    vector <int> validLocations() {
        vector<int>locations;
        for (int i = 0; i < COLS; i++)
            if (validMove(i)) locations.push_back(i);
        return locations;
    }

    int minimax(int depth, bool isMaximizing, int alpha, int beta) {
        // Check if it's a terminal state (win/draw) or depth limit reached.
        if (depth == 0 || isGameOver()) {
            return evaluate(); // Your evaluation function.
        }

        vector<int> validMoves = validLocations();
        if (isMaximizing) {
            int bestScore = INT_MIN;
            for (int col : validMoves) {
                if (!validMove(col)) continue;
                int row = dropPieceAT(AI, col);
                int score = minimax(depth - 1, false, alpha, beta);
                board[col][row] = 0; // Reset the board
                bestScore = max(bestScore, score);
                alpha = max(alpha, score);
                if (beta <= alpha)
                    break;
            }
            return bestScore;
        }
        else {
            int bestScore = INT_MAX;
            for (int col : validMoves) {
                if (!validMove(col)) continue;
                int row = dropPieceAT(player, col);
                int score = minimax(depth - 1, true, alpha, beta);
                board[col][row] = 0; // Reset the board
                bestScore = min(bestScore, score);
                beta = min(beta, score);
                if (beta <= alpha)
                    break;
            }
            return bestScore;
        }
    }
    int findBestMove() {
        int bestMove = -1;
        int bestScore = INT_MIN;
        vector<int> validMoves = validLocations();
        for (int col : validMoves) {
            
            if (!validMove(col)) continue;
            int row = dropPieceAT(AI, col);
            int score = minimax(MAX_AI_DEPTH, false, INT_MIN, INT_MAX);
            //cout << col << " : " << score << endl;
            board[col][row] = 0;
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
        return bestMove;
    }
    int evaluate() {
        int aiScore = 0;
        int playerScore = 0;

        for (int col = 0; col <= COLS - 4; col++) {
            for (int row = 0; row < ROWS; row++) {
                int line[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[col + i][row];
                }
                aiScore += evaluateLine(line, 2);
                playerScore += evaluateLine(line, 1);
            }
        }

        for (int col = 0; col < COLS; col++) {
            for (int row = 0; row <= ROWS - 4; row++) {
                int line[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[col][row + i];
                }
                aiScore += evaluateLine(line, 2);
                playerScore += evaluateLine(line, 1);
            }
        }

        for (int col = 0; col <= COLS - 4; col++) {
            for (int row = 0; row <= ROWS - 4; row++) {
                int line[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[col + i][row + i];
                }
                aiScore += evaluateLine(line, 2);
                playerScore += evaluateLine(line, 1);
            }
        }

        for (int col = 0; col <= COLS - 4; col++) {
            for (int row = 3; row < ROWS; row++) {
                int line[4];
                for (int i = 0; i < 4; i++) {
                    line[i] = board[col + i][row - i];
                }
                aiScore += evaluateLine(line, 2);
                playerScore += evaluateLine(line, 1);
            }
        }

        return aiScore - playerScore;
    }

    int evaluateLine(const int line[4], int playerNo) {
        int aiCount = 0;
        int playerCount = 0;
        int emptyCount = 0;

        for (int i = 0; i < 4; i++) {
            if (line[i] == 2) {
                aiCount++;
            }
            else if (line[i] == playerNo) {
                playerCount++;
            }
            else {
                emptyCount++;
            }
        }

        if (aiCount == 4) {
            return 10000; // AI wins
        }
        else if (playerCount == 4) {
            return -10000; // Player wins
        }
        else if (aiCount == 3 && emptyCount == 1) {
            return 1000; // AI has a winning move
        }
        else if (playerCount == 3 && emptyCount == 1) {
            return -1000; // Player has a winning move
        }
        else if (aiCount == 2 && emptyCount == 2) {
            return 100; // AI has a potential two-in-a-row
        }
        else if (playerCount == 2 && emptyCount == 2) {
            return -100; // Player has a potential two-in-a-row
        }
        else if (aiCount == 2 && playerCount == 1) {
            return 100; // advantage
        }else if (playerCount == 2 && aiCount == 1) {
            return -100; // advantage
        }else if (playerCount == 1 && aiCount == 1) {
            return 10; // 
        }

        return 0; // No advantage
    }

public:
    bool SinglePlayer = false;
    unsigned int MAX_AI_DEPTH = 5;
    vector<vector<int>> board;
    Game() {
        board = vector<vector<int>>(COLS, vector<int>(ROWS, 0));
    }

    void printBoard() {
        cout << "Turn: " << round++ << " \n";
        for (int i = ROWS - 1; i >= 0; i--) {
            cout << "|";
            for (int j = 0; j < COLS; j++) { // board[col][row]
                cout << getChar(board[j][i]) << "|";
            }
            cout << '\n';
        }
        cout << "|";
        for (int j = 0; j < COLS; j++) {
            cout << j << "|";
        }
        cout << '\n';
        gameCheck();
    }

    void AIMAkeMove(int col) {
        dropPiece(AI, col);
        printBoard();
    }
    void PlayerMakeMove(int col) {
        //cout << board.size() << " " << board[0].size();
        dropPiece(player, col);
        printBoard();
        //if (SinglePlayer) { AIMove(); }
    }
    bool validMove(int col) {
        if (col < 0 || col >= COLS || IsFull(col)) {
            return false;
        }
        return true;
    }
    void AIMove() {
        cout << "AI MOVE" << endl;
        int bestmove = findBestMove();
        cout << "The best move is " << bestmove << endl;
        AIMAkeMove(bestmove);
    }
    bool gameOver() {
        return isGameOver();
    }
    

};

int main()
{
    Game game;
    game.printBoard();    
    /*
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 20; i++) {        
    player_selection:
        int Pmove = rand() % 7;
        if (!game.validMove(Pmove)) goto player_selection;
        game.PlayerMakeMove(Pmove);
    AI_selection:
        int AImove = rand() % 7;
        if (!game.validMove(AImove)) goto AI_selection;
        game.AIMAkeMove(AImove);
    }
    */
    game.SinglePlayer = true;
    game.MAX_AI_DEPTH = 8;
    int num;
    cout << "enter 9 to exit at any time\n";
    while (!game.gameOver()) {
        selection:
        cout << "Enter column\n";
        cin >> num;
        if (num == 9) break;
        if (!(0 <= num && num < 7)) goto selection;
        game.PlayerMakeMove(num); 
        game.AIMove();
    }
    cout << "GAME OVER";
}

