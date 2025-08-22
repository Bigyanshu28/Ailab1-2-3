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

string boardToString(const vector<vector<int>>& board) 
{
    string s;
    for(auto &row : board)
        for(int x : row) s += to_string(x);
    return s;
}

bool greedyBestFirst(vector<vector<int>> start, vector<vector<int>> goal) 
{
    auto cmp = [&](const vector<vector<int>>& a, const vector<vector<int>>& b) 
    {
        return misplaced_tiles(a, goal) > misplaced_tiles(b, goal);
    };

    priority_queue<vector<vector<int>>, vector<vector<vector<int>>>, decltype(cmp)> pq(cmp);
    set<string> visited;

    pq.push(start);

    vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

    while(!pq.empty())
    {
        auto current = pq.top(); pq.pop();

        if(isGoal(current, goal))
        {
            cout << "Solution found!\n";
            print_board(current);
            return true;
        }

        string key = boardToString(current);
        if(visited.count(key)) continue;
        visited.insert(key);

        auto [x,y] = findEmptyBox(current);

        for(auto [dx,dy] : directions)
        {
            int nx = x + dx, ny = y + dy;
            if(nx>=0 && ny>=0 && nx<3 && ny<3)
            {
                auto new_board = current;
                swap(new_board[x][y], new_board[nx][ny]);
                string newKey = boardToString(new_board);
                if(visited.count(newKey)) continue;
                pq.push(new_board);
            }
        }
    }

    cout << "No solution found!\n";
    return false;
}

int main() 
{
    vector<vector<int>> puzzle = {{1, 2, 3}, {4, 5, 6}, {0, 7, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    cout << "Start state:\n";
    print_board(puzzle);

    greedyBestFirst(puzzle, goal);

    return 0;
}
