#include<iostream>
#include<cstring>
using namespace std;
int const maxn = 100;

string map[maxn+5];
int state[maxn+5][maxn+5]; 
// 1 for whole
// 2 for left bottom, 3 for right top
// 4 for left top, 5 for right bottom

int n0, m0;

void expand(int m, int n, char dir) {
    if (m < 0 || m >= m0)
        return;
    if (n < 0 || n >= n0)
        return;
    int s = state[m][n];
    char c = map[m][n];
    if (s == 1)
        return;
    if (c == ' ') {
        state[m][n] = 1;
        if (dir != 'd')
            expand(m+1,n,'u');
        if (dir != 'u')
            expand(m-1,n,'d');
        if (dir != 'r')
            expand(m,n+1,'l');
        if (dir != 'l')
            expand(m,n-1,'r');
    } else if (c == '\\') {
        if (dir == 'l' || dir == 'd') {
            if (s == 2)
                return;
            if (s == 3) 
                state[m][n] = 1;
            else 
                state[m][n] = 2;
            if (dir == 'l')
                expand(m+1,n,'u');
            else 
                expand(m,n-1,'r');
        } else {
            if (s == 3)
                return;
            if (s == 2)
                state[m][n] = 1;
            else 
                state[m][n] = 3;
            if (dir == 'u')
                expand(m,n+1,'l');
            else
                expand(m-1,n,'d');
        }
    } else if (c == '/') {
        if (dir == 'l' || dir == 'u') {
            if (s == 4)
                return;
            if (s == 5)
                state[m][n] = 1;
            else 
                state[m][n] = 4;
            if (dir == 'u')
                expand(m,n-1,'r');
            else 
                expand(m-1,n,'d');
        } else {
            if (s == 5)
                return;
            if (s == 4)
                state[m][n] = 1;
            else 
                state[m][n] = 5;
            if (dir == 'd')
                expand(m,n+1,'l');
            else
                expand(m+1,n,'u');
        }
    }
}

int count;

void bfs(int m, int n) {
    if (map[m][n] != ' ' && state[m][n] == 0) 
        count += 2;
    else 
        count += 1;
    
    int s = state[m][n];
    state[m][n] = 1;
    if (s != 2 && s != 5)
        expand(m+1,n,'u');
    if (s != 4 && s != 3)
        expand(m-1,n,'d');
    if (s != 3 && s != 5)
        expand(m,n+1,'l');
    if (s != 2 && s != 4)
        expand(m,n-1,'r');
}

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d %d ", &m0, &n0);
    for (int i = 0; i < m0; ++i) {
        getline(cin, map[i]);
    }
    
    memset(state, 0, sizeof state);
    
    /*for (int i = 0; i < m0; ++i) {
        for (int j = 0; j < n0; ++j)
            cout<<state[i][j]<<" ";
        cout<<endl;
    }*/
    
    count = 0;
    for (int i = 0; i < m0; ++i) {
        for (int j = 0; j < n0; ++j) {
            if (state[i][j] != 1) {
                bfs(i, j);
            }
        }
    }
    cout<<count<<endl;
    return 0;
}