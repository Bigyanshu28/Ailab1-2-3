#include <iostream>
#include <vector>
using namespace std;

vector<int> board(10, 2); 
int turn = 1;
bool aiIsX;

int magicMap[10] = {0, 8, 3, 4, 1, 5, 9, 6, 7, 2};

void printBoard() 
{
    cout << "\n";
    for (int i = 1; i <= 9; ++i) 
    {
        char mark = (board[i] == 3) ? 'X' : (board[i] == 5) ? 'O' : ' ';
        cout << " " << mark << " ";
        if (i % 3 == 0) cout << "\n";
        else cout << "|";
    }
    cout << "\n";
}

void Go(int n) 
{
    if (board[n] == 2) 
    {
        board[n] = (turn % 2 == 1) ? 3 : 5;
        turn++;
    }
}

vector<int> getPlayerMoves(int player) 
{
    vector<int> moves;
    for (int i = 1; i <= 9; i++) 
    {
        if (board[i] == player) 
        {
            moves.push_back(magicMap[i]);
        }
    }
    return moves;
}

int possWinMagic(int player) 
{
    vector<int> moves = getPlayerMoves(player);
    int n = moves.size();
    if (n < 2) return 0;

    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            int needed = 15 - (moves[i] + moves[j]);
            if (needed < 1 || needed > 9) continue;
            for (int pos = 1; pos <= 9; pos++) 
            {
                if (magicMap[pos] == needed && board[pos] == 2) 
                {
                    return pos;
                }
            }
        }
    }
    return 0;
}

int checkWinner() 
{
    vector<int> xMoves = getPlayerMoves(3);
    vector<int> oMoves = getPlayerMoves(5);

    auto hasWon = [](const vector<int>& moves) 
    {
        int n = moves.size();
        if (n < 3) return false;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    if (moves[i] + moves[j] + moves[k] == 15)
                        return true;
        return false;
    };

    if (hasWon(xMoves)) return 3;
    if (hasWon(oMoves)) return 5;
    return 0;
}

void humanMove() 
{
    int move;
    while (true) 
    {
        cout << "Your move (1-9): ";
        cin >> move;
        if (move >= 1 && move <= 9 && board[move] == 2) 
        {
            Go(move);
            break;
        } 
        else 
        {
            cout << "Invalid move. Try again.\n";
        }
    }
}

void aiMove() 
{
    int move = 0;
    bool aiTurnOdd = ((turn % 2 == 1) == aiIsX);
    int aiSymbol = aiIsX ? 3 : 5;
    int humanSymbol = aiIsX ? 5 : 3;

    if ((move = possWinMagic(aiSymbol))) {}

    else if ((move = possWinMagic(humanSymbol))) {}

    else 
    {
        for (int i = 1; i <= 9; i++) 
        {
            if (board[i] == 2) 
            { 
                move = i; 
                break; 
            }
        }
    }

    cout << "AI chooses square " << move << "\n";
    Go(move);
}

int main() 
{
    cout << "Welcome to Tic-Tac-Toe with Magic Square Logic!\n";
    char choice;
    cout << "Should AI play as X and start first? (y/n): ";
    cin >> choice;
    aiIsX = (choice == 'y' || choice == 'Y');

    printBoard();

    while (turn <= 9) 
    {
        if ((turn % 2 == 1) == aiIsX) 
        {
            aiMove();
        } 
        else 
        {
            humanMove();
        }

        printBoard();

        int winner = checkWinner();
        if (winner == 3) 
        { 
            cout << ((aiIsX) ? "AI wins!\n" : "Human wins!\n");
            return 0;
        }
        else if (winner == 5) 
        { 
            cout << ((!aiIsX) ? "AI wins!\n" : "Human wins!\n");
            return 0;
        }
    }

    cout << "It's a draw!\n";
    return 0;
}
