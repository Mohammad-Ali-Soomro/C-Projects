#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;

#define capacity 50

class gumoku { //class for creating  game
	
public:  // public access to data members


char board[capacity][capacity];
    int dim;
    int ri, ci;
    char Pname[2][30];                    //data members of game
    char Psym[2] = { '#', '@' };
    int turn;
    int winCount;
    bool gameover = false;
    int winner = -1;
    
    //Initializing the board with its parameters
    void init(char board[][capacity], int& dim, char Pname[][30], int& turn, int& winCount) {
        int choice;
        cout << "Enter Grid choice:" << endl << "1 for 9x9" << endl << "2 for 15 x 15" << endl << endl;
        cin >> choice;

        if (choice == 1) {   //for 9x9 grid
            dim = 9;
        }
        else if (choice == 2) {    // for 15x15 grid
            dim = 15;
        }

        for (int ri = 0; ri < dim; ri++) {
            for (int ci = 0; ci < dim; ci++) {
                board[ri][ci] = '-';
            }
        }

        cout << "Enter Player 1 name " << endl;
        cin >> Pname[0];

        if (choice == 1) {
            cout << "Enter Player 2 name " << endl;
            cin >> Pname[1];
        }
        else {
            strcpy(Pname[1], "Bot");
        }

        cout << endl << "Win count:" << endl;
        cin >> winCount;

        turn = rand() % 2;

        displayboard(board, dim);
    }
// Displaying board function with its parameters
    void displayboard(char board[][capacity], int dim) {
        for (int ri = 0; ri < dim; ri++) {
            for (int ci = 0; ci < dim; ci++) {
                cout << board[ri][ci] << "  ";
            }
            cout << endl;
        }
    }
// Displays turn message of player
    void display_turn_message(char aikNaam[], char aikSym) {
        cout << endl << " Symbol: " << aikSym << endl << aikNaam << "'s Turn [ri, ci]: " << endl;
    }

    void selectPosition(int& ri, int& ci) {
        cin >> ri >> ci;
        ri--;
        ci--;
    }
//
    bool IsValidDestination(int ri, int ci, int dim, char board[][capacity]) {
        return (ri >= 0 && ci >= 0) && (ri < dim && ci < dim) && (board[ri][ci] == '-');
    }
//Updates board regularly
    void update_board(char board[][capacity], int ri, int ci, char aiksym) {
        board[ri][ci] = aiksym;
    }
//Gives turn to next player
    void turn_change(int& turn) {
        turn = (turn + 1) % 2;
    }
// Checks for match (win condition based on wincount inputted)
    bool isHorizontalCheck(char board[][capacity], int dim, char aikSym, int winCount, int ri, int ci) {
        int count = 1;
        for (int i = 1; i < winCount; i++) {
            if (ci + i < dim && board[ri][ci + i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        for (int i = 1; i < winCount; i++) {
            if (ci - i >= 0 && board[ri][ci - i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        return count >= winCount;
    }
// Vertical column check for game win
    bool isVerticalCheck(char board[][capacity], int dim, char aikSym, int winCount, int ri, int ci) {
        int count = 1;
        for (int i = 1; i < winCount; i++) {
            if (ri + i < dim && board[ri + i][ci] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        for (int i = 1; i < winCount; i++) {
            if (ri - i >= 0 && board[ri - i][ci] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        return count >= winCount;
    }
// Diagonal check for game win
    bool isDiagonalRightCheck(char board[][capacity], int dim, char aikSym, int winCount, int ri, int ci) {
        int count = 1;
        for (int i = 1; i < winCount; i++) {
            if (ri + i < dim && ci + i < dim && board[ri + i][ci + i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        for (int i = 1; i < winCount; i++) {
            if (ri - i >= 0 && ci - i >= 0 && board[ri - i][ci - i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        return count >= winCount;
    }

    bool isDiagonalLeftCheck(char board[][capacity], int dim, char aikSym, int winCount, int ri, int ci) {
        int count = 1;
        for (int i = 1; i < winCount; i++) {
            if (ri + i < dim && ci - i >= 0 && board[ri + i][ci - i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        for (int i = 1; i < winCount; i++) {
            if (ri - i >= 0 && ci + i < dim && board[ri - i][ci + i] == aikSym) {
                count++;
            }
            else {
                break;
            }
        }

        return count >= winCount;
    }
// Win functions that checks the players move vertically, horizontally, diagonally 
    bool IsWin(char board[][capacity], int dim, char aikSym, int winCount) {
        for (int ri = 0; ri < dim; ri++) {
            for (int ci = 0; ci < dim; ci++) {
                if (board[ri][ci] == aikSym) {
                    if (isHorizontalCheck(board, dim, aikSym, winCount, ri, ci) ||
                        isVerticalCheck(board, dim, aikSym, winCount, ri, ci) ||
                        isDiagonalRightCheck(board, dim, aikSym, winCount, ri, ci) ||
                        isDiagonalLeftCheck(board, dim, aikSym, winCount, ri, ci)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
// game draw condition
    bool IsDraw(char board[][capacity], int dim) {
        for (int ri = 0; ri < dim; ri++) {
            for (int ci = 0; ci < dim; ci++) {
                if (board[ri][ci] == '-')
                    return false;
            }
        }
        return true;
    }
// Human vs Bot mode playing function
    void HumanvsComputer(char board[][capacity], int& ri, int& ci, int Dim, int WinCount, char aiksym) {
        for (WinCount = WinCount; WinCount > 3; WinCount--) {
            for (ri = 0; ri < Dim; ri++) {
                for (ci = 0; ci < Dim; ci++) {
                    if (board[ri][ci] == '-')
                        board[ri][ci] = aiksym;
                    if (IsWin(board, Dim, WinCount, aiksym)) {
                        board[ri][ci] = '-';
                        return;
                    }
                    else
                        board[ri][ci] = '-';
                }
            }
        }
        do {
            ri = rand() % Dim;
            ci = rand() % Dim;
        } while (board[ri][ci] != '-');
    }

    void HvsC(char board[][capacity], int& ri, int& ci, int Dim, int WinCount, char CS, char HS) {
        char T[capacity][capacity];
        for (int r = 0; r < Dim; r++) {
            for (int c = 0; c < Dim; c++) {
                T[r][c] = board[r][c];
            }
        }
        for (int WC = WinCount; WC > WinCount - 3; WC--) {
            for (int r = 0; r < Dim; r++) {
                for (int c = 0; c < Dim; c++) {
                    if (IsValidDestination(r, c, Dim, board)) {
                        board[r][c] = CS;
                        if (IsWin(board, Dim, CS, WC)) {
                            ri = r;
                            ci = c;
                            board[r][c] = '-';
                            return;
                        }
                        else {
                            board[r][c] = '-';
                        }
                    }
                }
            }
            for (int r = 0; r < Dim; r++) {
                for (int c = 0; c < Dim; c++) {
                    if (IsValidDestination(r, c, Dim, T)) {
                        T[r][c] = HS;
                        if (IsWin(T, Dim, HS, WC)) {
                            ri = r;
                            ci = c;
                            return;
                        }
                        else {
                            T[r][c] = '-';
                        }
                    }
                }
            }
        }

        // Intelligent Bot Move - Place it near the Human Player's move
        do {
            ri = rand() % Dim;
            ci = rand() % Dim;
        } while (!IsValidDestination(ri, ci, Dim, board) || !isNearHumanMove(ri, ci, Dim, board, HS));
    }
// This function makes bot more intelligent and tries to win the game from human player
    bool isNearHumanMove(int ri, int ci, int dim, char board[][capacity], char HS) {
        for (int i = -1; i <= 1; i += 2) {
            if (ci + i >= 0 && ci + i < dim && board[ri][ci + i] == HS) {
                return true;
            }
            if (ri + i >= 0 && ri + i < dim && board[ri + i][ci] == HS) {
                return true;
            }
        }

        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                if (ri + i >= 0 && ri + i < dim && ci + j >= 0 && ci + j < dim && board[ri + i][ci + j] == HS) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main() {
    gumoku game;  // Instance of class
    srand((0));

    cout<<endl<<"\t\t\t\tWELCOME TO THE STRATEGIC FIVE(GUMOKU) GAME DEVELOPED BY MOHAMMAD ALI"<<endl<<endl;

    cout << "Select Game Mode:" << endl << "1 for Human vs Human" << endl << "2 for Human vs Bot" << endl;
    int mode;
    cin >> mode;  // Selects mode (human vs human) or (human vs bot)

    game.init(game.board, game.dim, game.Pname, game.turn, game.winCount);  //function calling

    do {
        game.displayboard(game.board, game.dim);
        game.display_turn_message(game.Pname[game.turn], game.Psym[game.turn]);

        if (mode == 1) {
            // Human vs Human Mode
            do {
                game.selectPosition(game.ri, game.ci);
            } while (!game.IsValidDestination(game.ri, game.ci, game.dim, game.board));
        }
        else if (mode == 2) {
            // Human vs Bot Mode
            if (game.turn == 0) {
                // Human's Turn
                do {
                    game.selectPosition(game.ri, game.ci);
                } while (!game.IsValidDestination(game.ri, game.ci, game.dim, game.board));
            }
            else {
                // Bot's Turn
                game.HvsC(game.board, game.ri, game.ci, game.dim, game.winCount, game.Psym[game.turn], game.Psym[1 - game.turn]);
            }
        }

        game.update_board(game.board, game.ri, game.ci, game.Psym[game.turn]);
        game.gameover = game.IsWin(game.board, game.dim, game.Psym[game.turn], game.winCount);

        if (game.gameover == true) {
            game.winner = game.turn;
        }

        if (game.gameover == false) {
            game.gameover = game.IsDraw(game.board, game.dim);
        }

        if (game.gameover == false) {
            game.turn_change(game.turn);
        }

    } while (!game.gameover);
    

    if (game.winner == -1) {
        cout << "The Game is Draw " << endl;
    }
    else {
        cout << game.Pname[game.winner] << " has Won the Gumoko Game " << endl;
    }

    return 0;
}
// readme file of this code is attached separately................