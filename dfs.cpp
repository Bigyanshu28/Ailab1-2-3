#include <iostream>
#include <stack>
#include <set>
#include <string>
using namespace std;

const int goal[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char dirChar[] = {'U', 'D', 'L', 'R'};
const int MAX_DEPTH = 200; 
struct Node {
    int state[3][3];
    Node* parent;
    string path;
};
set<string> visited;
string serialize(int b[3][3]) {
    string s;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            s += '0' + b[i][j];
    return s;
}
void findZero(int b[3][3], int &x, int &y) {
    for (x = 0; x < 3; ++x)
        for (y = 0; y < 3; ++y)
            if (b[x][y] == 0)
                return;
}
void printSolution(Node* node) {
    if (!node) return;
    printSolution(node->parent);
    static int step = 0;
    cout << "Step " << step++ << ":\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            cout << node->state[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}
void DFS(int start[3][3]) {
    stack<Node*> s;

    Node* root = new Node();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            root->state[i][j] = start[i][j];
    root->parent = nullptr;
    root->path = "";

    s.push(root);
    visited.insert(serialize(start));

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        if (current->path.length() > MAX_DEPTH) {
            delete current;
            continue;
        }

        bool isGoal = true;
        for (int i = 0; i < 3 && isGoal; ++i)
            for (int j = 0; j < 3 && isGoal; ++j)
                if (current->state[i][j] != goal[i][j])
                    isGoal = false;

        if (isGoal) {
            cout << "Solution found in " << current->path.length() << " moves: " << current->path << "\n\n";
            printSolution(current);
            return;
        }
        int x, y;
        findZero(current->state, x, y);

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
                continue;
            Node* child = new Node();
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    child->state[i][j] = current->state[i][j];

            child->state[x][y] = child->state[nx][ny];
            child->state[nx][ny] = 0;

            string key = serialize(child->state);

            if (visited.count(key) == 0) {
                child->parent = current;
                child->path = current->path + dirChar[dir];
                s.push(child);
                visited.insert(key);
            } else {
                delete child;
            }
        }
    }

    cout << "No solution found within depth " << MAX_DEPTH << ".\n";
}
int main() {
    int start[3][3] = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };
    DFS(start);
    return 0;
}
