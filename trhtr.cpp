#include<iostream>
#include<queue>
using namespace std;

const int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
const int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
const char dirChar[] = {'U','D','L','R'};

struct Node {
    int state[3][3];
    Node* parent;
    string path;
};

string visited[1000];
int visitedCount = 0;

string serialize(int b[3][3]) {
    string s;
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
        s += '0'+b[i][j];
    return s;
}

void findZero(int b[3][3], int &x, int &y) {
    for (x=0; x<3; x++)
    for (y=0; y<3; y++)
        if (b[x][y] == 0) return;
    x = y = -1;
}

void printSolution(Node* node) {
    if (!node) return;
    printSolution(node->parent);
    
    static int step = 0;
    cout << "Step " << step++ << ":\n";
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++)
            cout << node->state[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void BFS(int start[3][3]) {
    queue<Node*> q;
    
    Node* root = new Node();
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
        root->state[i][j] = start[i][j];
    root->parent = 0;
    root->path = "";
    
    q.push(root);
    visited[visitedCount++] = serialize(start);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        bool same = true;
        for (int i=0; i<3 && same; i++)
        for (int j=0; j<3 && same; j++)
            if (current->state[i][j] != goal[i][j])
                same = false;
        
        if (same) {
            cout << "Solution found in " << current->path.size() << " moves: " << current->path << "\n\n";
            printSolution(current);
            return;
        }
        
        int x, y;
        findZero(current->state, x, y);
        
        for (int i=0; i<4; i++) {
            int nx = x+dx[i], ny = y+dy[i];
            if (nx<0 || nx>2 || ny<0 || ny>2) continue;
            
            Node* child = new Node();
            for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                child->state[i][j] = current->state[i][j];
            
            child->state[x][y] = child->state[nx][ny];
            child->state[nx][ny] = 0;
            
            string key = serialize(child->state);
            bool found = false;
            for (int j=0; j<visitedCount && !found; j++)
                if (visited[j] == key) found = true;
                
            if (!found) {
                child->parent = current;
                child->path = current->path + dirChar[i];
                q.push(child);
                visited[visitedCount++] = key;
            }
            else delete child;
        }
    }
    cout << "No solution found.\n";
}

int main() {
    int start[3][3] = {{1,0,3},{4,2,6},{7,5,8}};
    BFS(start);
    return 0;
}