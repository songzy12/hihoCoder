#include<iostream>
using namespace std;

const int maxn = 200;
const int maxm = 200;
char grid[2*maxn+1][2*maxm+1];

pair<int,int> next_pos(pair<int,int> cur_pos, char &cur_dir, 
                       int l, int f, int r, char dir) {
    int x = cur_pos.first, y = cur_pos.second;
    grid[2*x+1][2*y+1] = ' ';
    if (cur_dir == 'd') {
        grid[2*x][2*y+1] = ' '; // u
        grid[2*x+1][2*(y+1)] = l ? '|' : ' '; // r
        grid[2*(x+1)][2*y+1] = f ? '-' : ' '; // d
        grid[2*x+1][2*y] = r ? '|' : ' '; // l
    } else if (cur_dir == 'r') {
        grid[2*x+1][2*y] = ' ';
        grid[2*x][2*y+1] = l ? '-' : ' ';
        grid[2*x+1][2*(y+1)] = f ? '|' : ' ';
        grid[2*(x+1)][2*y+1] = r ? '-' : ' ';
    } else if (cur_dir == 'l') {
        grid[2*x+1][2*(y+1)] = ' ';
        grid[2*(x+1)][2*y+1] = l ? '-' : ' ';
        grid[2*x+1][2*y] = f ? '|' : ' ';
        grid[2*x][2*y+1] = r ? '-' : ' ';
    } else { // u
        grid[2*(x+1)][2*y+1] = ' ';
        grid[2*x+1][2*y] = l ? '|' : ' ';
        grid[2*x][2*y+1] = f ? '-' : ' ';
        grid[2*x+1][2*(y+1)] = r ? '|' : ' ';
    }
    cur_dir = dir;
    if (dir == 'r') {
        return {x, y+1};
    } else if (dir == 'l') {
        return {x, y-1};
    } else if (dir == 'u') {
        return {x-1, y};
    } else {
        return {x+1, y};
    }
}

int main() {
    int n, m;
    cin>>n>>m;
    char cur_dir = 'd';
    pair<int, int> cur_pos = make_pair(0, 0);
    
    
    for (int i = 0; i < 2*n+1; ++i) {
        for (int j = 0; j < 2*m+1; ++j) {
            grid[i][j] = '+';
        }
    }
    
    for (int i = 0; i < 2*n*m-1; ++i) {
        int l, f, r;
        char d;
        cin>>l>>f>>r>>d;
        cur_pos = next_pos(cur_pos, cur_dir, l, f, r, d);
    }
    
    for (int i = 0; i < 2*n+1; ++i) {
        for (int j = 0; j < 2*m+1; ++j) {
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    return 0;
}