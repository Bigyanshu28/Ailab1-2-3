#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

const vector<vector<int>> goal = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct State {
    vector<vector<int>> board;
    string path;
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

void bfs(const vector<vector<int>>& start) {
    queue<State> q;
    set<string> visited;

    q.push({start, ""});
    visited.insert(serialize(start));

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.board == goal) {
            cout << "Solution found!\n";
            cout << "Number of moves: " << curr.path.size() << "\n";
            cout << "Moves sequence: " << curr.path << "\n";
            return;
        }

        pair<int, int> pos = findZero(curr.board);
        int x = pos.first;
        int y = pos.second;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> nextBoard = curr.board;
                swap(nextBoard[x][y], nextBoard[nx][ny]);

                string key = serialize(nextBoard);
                if (visited.find(key) == visited.end()) {
                    string moveChar = "UDLR";
                    q.push({nextBoard, curr.path + moveChar[dir]});
                    visited.insert(key);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };
    bfs(start);
    return 0;
}
