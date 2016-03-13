#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

char mp[207][207];
char now[4][4][4];
int n,m;

bool check(int x,int y){
    x--;
    y--;
    int i,j,k;
    for(k=0;k<4;k++){
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(mp[x+i][y+j] != now[k][i][j]){
                    break;
                }
            }
            if(j<3) break;
        }
        if(i>=3) return 1;
    }
    return 0;
}

void solve(){
    // rotate for 3 times
    for(int k=1;k<4;k++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                now[k][j][2-i]=now[k-1][i][j];
            }
        }
    }
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            if(check(i,j)){
                printf("%d %d\n",i,j);
            }
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=0;i<3;i++) scanf("%s",now[0][i]);
    solve();
    return 0;
}