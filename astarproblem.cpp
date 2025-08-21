#include <iostream>
using namespace std;
int p,q;
int r,s;
const int rows = 5, cols = 5;
    char matrix[rows][cols];
int g[5],h[5],f[5];
   
void matrixriver(){
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = '-';
        }
    }
    for(int i = 0; i < rows; i++) {
        int j;
        cout << "Enter column" << i << ": ";
        cin >> j;
        if(j >= 0 && j < cols) {
            matrix[i][j] = 'X';
        } else {
            cout << "invalid" << i << endl;
        }
    }
}

int mtravdown(){
     g[0]=0;
    h[0]=0;
    f[0]=0;
 for(int i = p; i < rows; i++) {
        for(int j = q; j < cols; j++) {
            g[i]+=1;
            h[i]+=1;
            if( matrix[i][j] = 'X'){
                i++;
            }
        }
        return i;
    }
    
}
int mtravup(int z){
    g[0]=0;
    h[0]=0;
    f[0]=0;
 for(int i = p; i < rows; i++) {
        for(int j = q; j < cols; j++) {
            g[i]+=1;
            h[i]+=1;
            if( matrix[i][j] = 'X'){
                i++;
            }
        }
        return f[i]=g[i]+h[i];
    }
    
}

void print(){
            cout << "Matrix:\n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout<<"enter source index";
    cin>>p>>q;
    cout<<"enter goal index";
    cin>>r>>s;
    matrixriver();
   mtravdown();
    print();
    int in=mtravdown();
    mtravup(in);
    return 0;
}
