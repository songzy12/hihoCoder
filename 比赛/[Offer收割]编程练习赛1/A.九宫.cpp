#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

int q[3][3];

int a[8][3][3] = {
    {8,1,6,3,5,7,4,9,2},
    {6,1,8,7,5,3,2,9,4},
    {4,9,2,3,5,7,8,1,6},
    {2,9,4,7,5,3,6,1,8},
    {6,7,2,1,5,9,8,3,4},
    {8,3,4,1,5,9,6,7,2},
    {2,7,6,9,5,1,4,3,8},
    {4,3,8,9,5,1,2,7,6}
};

bool match(int k) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!q[i][j])
                continue;
            if (q[i][j] != a[k][i][j])
                return false;
        }
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cin>>q[i][j];
        
    int count = 0, index = -1;
    for (int k = 0; k < 8; ++k) {
        if (match(k)) {
            count++;
            index = k;
        }
    }
    
    if (count > 1)
        cout<<"Too Many"<<endl;
    else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout<<a[index][i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
	return 0;
}