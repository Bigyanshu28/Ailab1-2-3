#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generateOdd(int n) 
{
    vector<vector<int>> magic(n, vector<int>(n, 0));
    int i = 0, j = n / 2;

    for (int num = 1; num <= n * n; ) 
    {
        magic[i][j] = num++;
        int newi = (i - 1 + n) % n;
        int newj = (j + 1) % n;
        if (magic[newi][newj]) 
        {
            i = (i + 1) % n;
        } 
        else 
        {
            i = newi;
            j = newj;
        }
    }

    return magic;
}

vector<vector<int>> generateDoublyEven(int n) 
{
    vector<vector<int>> magic(n, vector<int>(n));
    int num = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            magic[i][j] = num++;

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) {
            if (((i % 4 == j % 4) || ((i % 4) + (j % 4) == 3))) 
            {
                magic[i][j] = (n * n + 1) - magic[i][j];
            }
        }
    }

    return magic;
}

vector<vector<int>> generateSinglyEven(int n) 
{
    int halfN = n / 2;
    int subSquareSize = n / 2;
    int k = (n - 2) / 4;

    vector<vector<int>> subSquare = generateOdd(halfN);
    vector<vector<int>> magic(n, vector<int>(n));

    for (int i = 0; i < halfN; i++) 
    {
        for (int j = 0; j < halfN; j++) 
        {
            magic[i][j] = subSquare[i][j];
            magic[i + halfN][j] = subSquare[i][j] + 2 * halfN * halfN;
            magic[i][j + halfN] = subSquare[i][j] + 3 * halfN * halfN;
            magic[i + halfN][j + halfN] = subSquare[i][j] + halfN * halfN;
        }
    }

    for (int i = 0; i < halfN; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            swap(magic[i][j], magic[i + halfN][j]);
        }
        
        for (int j = n - k + 1; j < n; j++) 
        {
            swap(magic[i][j], magic[i + halfN][j]);
        }
    }

    swap(magic[k][0], magic[k + halfN][0]);
    swap(magic[k][k], magic[k + halfN][k]);

    return magic;
}

int main() {
    int n;
    cout << "Enter n (n >= 3, n != 2): ";
    cin >> n;

    if (n < 3 || n == 2) {
        cout << "Magic square not possible for this n." << endl;
        return 0;
    }

    vector<vector<int>> magic;

    if (n % 2 == 1)
        magic = generateOdd(n);
    else if (n % 4 == 0)
        magic = generateDoublyEven(n);
    else
        magic = generateSinglyEven(n);

    cout << "Magic Square of size " << n << ":\n";
    for (auto &row : magic) {
        for (auto &val : row)
            cout << setw(4) << val;
        cout << endl;
    }

    cout << "\nMagic constant: " << n * (n * n + 1) / 2 << endl;
}
