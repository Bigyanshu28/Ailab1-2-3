#include <bits/stdc++.h>
using namespace std;

void print_board(const vector<vector<int>>& board) 
{
    for (auto &row : board) 
    {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
}

bool isGoal(const vector<vector<int>>& puzzle, const vector<vector<int>>& goal) 
{
    return puzzle == goal;
}

pair<int,int> findEmptyBox(const vector<vector<int>>& puzzle) 
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(puzzle[i][j] == 0)
                return {i,j};
    return {-1,-1};
}

int misplaced_tiles(const vector<vector<int>>& puzzle, const vector<vector<int>>& goal) 
{
    int count = 0;
    for(int i=0; i<3; i++) 
    {
        for(int j=0; j<3; j++) 
        {
            if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j])
                count++;
        }
    }
    return count;
}

vector<vector<vector<int>>> get_neighbors(const vector<vector<int>>& board) 
{
    vector<vector<vector<int>>> neighbors;
    auto [x, y] = findEmptyBox(board);
    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    for(auto [dx,dy] : dirs)
    {
        int nx = x + dx, ny = y + dy;
        if(nx>=0 && ny>=0 && nx<3 && ny<3){
            auto new_board = board;
            swap(new_board[x][y], new_board[nx][ny]);
            neighbors.push_back(new_board);
        }
    }
    return neighbors;
}

bool hillClimbing(vector<vector<int>> start, vector<vector<int>> goal) 
{
    vector<vector<int>> current = start;
    int current_h = misplaced_tiles(current, goal);

    cout << "Starting hill climbing...\n";
    print_board(current);
    cout << "Heuristic: " << current_h << "\n\n";

    while (true) 
    {
        if (isGoal(current, goal)) {

            cout << "Goal reached!\n";
            return true;
        }

        auto neighbors = get_neighbors(current);
        vector<vector<int>> best_neighbor = current;
        int best_h = current_h;

        for (auto &nb : neighbors) 
        {
            int h = misplaced_tiles(nb, goal);
            if (h < best_h) 
            {
                best_h = h;
                best_neighbor = nb;
            }
        }

        if (best_h >= current_h) 
        {
            cout << "No better neighbor found. Stopping.\n";
            return false;
        }

        current = best_neighbor;
        current_h = best_h;

        print_board(current);
        cout << "Heuristic: " << current_h << "\n\n";
    }
}

int main() 
{
    vector<vector<int>> puzzle = {{1, 2, 3}, {4, 5, 6}, {0, 7, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    hillClimbing(puzzle, goal);
    return 0;
}
