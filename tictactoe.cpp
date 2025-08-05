#include <iostream>
#include <limits>
using namespace std;
char board[3][3];
char user, computerPlayer;
void initBoard() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = ' ';
}
void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++) {
        cout << " ";
        for(int j=0;j<3;j++) {
            cout << board[i][j];
            if(j<2) cout << " | ";
        }
        if(i<2) cout << "\n-----------\n";
    }
    cout << "\n\n";
}
char checkWinner() {
    for(int i=0;i<3;i++) {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!=' ')
            return board[i][0];
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!=' ')
            return board[0][i];
    }
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=' ')
        return board[0][0];
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=' ')
        return board[0][2];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return ' '; 
    return 'D';  
}
int minimax(bool isMax) {
    char result = checkWinner();
    if(result == computerPlayer) return 10;
    if(result == user) return -10;
    if(result == 'D') return 0;
    if(isMax) {
        int best = -1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==' ') {
                    board[i][j] = computerPlayer;
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==' ') {
                    board[i][j] = user;
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}
void computerMove() {
    int bestVal = -1000;
    int row = -1, col = -1;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]==' ') {
                board[i][j] = computerPlayer;
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if(moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = computerPlayer;
    cout << "Computer placed " << computerPlayer << " at position: " << (row*3+col+1) << "\n";
}
void userMove() {
    int move;
    while(true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        move--;
        int r = move / 3, c = move % 3;
        if(move >= 0 && move < 9 && board[r][c]==' ') {
            board[r][c] = user;
            break;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    }
}
int main() {
    initBoard();
    cout << "Welcome to Tic Tac Toe!\n";
    while (true) {
        cout << "Choose your symbol (X/O): ";
        cin >> user;
        if(user=='X' || user=='x') {
            user = 'X';
            computerPlayer = 'O';
            break;
        } else if(user=='O' || user=='o') {
            user = 'O';
            computerPlayer = 'X';
            break;
        } else {
            cout << "Invalid choice, please choose X or O.\n";
        }
    }
    bool userTurn = (user == 'X');
    printBoard();
    while(true) {
        if(userTurn) {
            userMove();
        } else {
            computerMove();
        }
        printBoard();
        char winner = checkWinner();
        if(winner == user) {
            cout << "Congratulations! You win!\n";
            break;
        } else if(winner == computerPlayer) {
            cout << "Computer wins! Better luck next time.\n";
            break;
        } else if(winner == 'D') {
            cout << "It's a draw!\n";
            break;
        }
        userTurn = !userTurn;
    }
    return 0;
}
