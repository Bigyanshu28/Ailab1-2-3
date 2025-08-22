#include <bits/stdc++.h>
using namespace std;

bool waterJugBFS(int jug1Cap, int jug2Cap, int target) 
{
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;

    q.push({0, 0});

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        cout << "Current state: (" << curr.first << ", " << curr.second << ")\n";

        if (curr.first == target || curr.second == target || curr.first + curr.second == target) 
        {
            cout << "Reached target: (" << curr.first << ", " << curr.second << ")\n";
            return true;
        }

        if (visited.count({curr.first, curr.second})) continue;
        visited.insert({curr.first, curr.second});

        vector<pair<int, int>> nextStates;

        nextStates.push_back({jug1Cap, curr.second});

        nextStates.push_back({curr.first, jug2Cap});

        nextStates.push_back({0, curr.second});

        nextStates.push_back({curr.first, 0});

        {
            int pour = min(curr.first, jug2Cap - curr.second);
            nextStates.push_back({curr.first - pour, curr.second + pour});
        }

        {
            int pour = min(curr.second, jug1Cap - curr.first);
            nextStates.push_back({curr.first + pour, curr.second - pour});
        }

        for (auto &s : nextStates) 
        {
            if (!visited.count({s.first, s.second})) 
            {
                q.push(s);
            }
        }
    }

    return false;
}

int main() {
    int jug1Cap, jug2Cap, target;
    cout << "Enter capacity of Jug 1: ";
    cin >> jug1Cap;
    cout << "Enter capacity of Jug 2: ";
    cin >> jug2Cap;
    cout << "Enter target amount: ";
    cin >> target;

    if (waterJugBFS(jug1Cap, jug2Cap, target))
        cout << "Solution found!\n";
    else
        cout << "No solution possible!\n";

    return 0;
}
