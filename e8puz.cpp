#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct State {
    vector<vector<int>> board;
    string path;
    State* parent;  
};

string serialize(const vector<vector<int>>& board) {
    string s;
    for (auto& row : board)
        for (int val : row)
            s += to_string(val);
    return s;
}

pair<int, int> findZero(const vector<vector<int>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row)
            cout << val << " ";
        cout << "\n";
    }
    cout << "--------\n";
}

void printSolutionPath(State* goalState) {
    vector<State*> path;
    State* curr = goalState;
    while (curr != nullptr) {
        path.push_back(curr);
        curr = curr->parent;
    }
    reverse(path.begin(), path.end());
    cout << "\n--- Solution Steps (" << path.size() - 1 << " moves) ---\n\n";
    for (size_t i = 0; i < path.size(); i++) {
        cout << "Step " << i << ":\n";
        printBoard(path[i]->board);
    }
}

void bfs(const vector<vector<int>>& start) {
    queue<State*> q;
    set<string> visited;

    State* initial = new State{start, "", nullptr};
    q.push(initial);
    visited.insert(serialize(start));

    while (!q.empty()) {
        State* curr = q.front();
        q.pop();

        if (curr->board == goal) {
            cout << "Solution found!\n";
            cout << "Number of moves: " << curr->path.size() << "\n";
            cout << "Moves sequence: " << curr->path << "\n";
            printSolutionPath(curr);
            return;
        }

        pair<int, int> pos = findZero(curr->board);
        int x = pos.first;
        int y = pos.second;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> nextBoard = curr->board;
                swap(nextBoard[x][y], nextBoard[nx][ny]);

                string key = serialize(nextBoard);
                if (visited.find(key) == visited.end()) {
                    string moveChar = "UDLR";
                    State* nextState = new State{nextBoard, curr->path + moveChar[dir], curr};
                    q.push(nextState);
                    visited.insert(key);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = {
        {1, 0, 3},
        {4, 2, 6},
        {7, 5, 8}
    };
    bfs(start);
    return 0;
}
