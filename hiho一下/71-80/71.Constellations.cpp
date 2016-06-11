#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#define MOD 1000000007
using namespace std;
char tem[102];
char mp[1003][1003];
int t,n,m;
typedef pair<int,int> node;
vector<node> v[21];
bool vis[21];
int length,xx,yy;
bool key;

int main()
{
 //   freopen("in.txt","r",stdin);
    while(scanf("%d",&t)!=EOF)
    {
        memset(vis,0,sizeof(vis));
        for(int icase=0;icase<t;icase++)
        {
            scanf("%d%d",&n,&m);
            for(int i=0;i<n;i++)
            {
                scanf("%s",tem);
                for(int j=0;j<m;j++)
                    // v[icase] is the star positions for icase
                    if(tem[j]=='#')
                        v[icase].push_back(node(i,j));
            }
            for(int i=1;i<v[icase].size();i++)
            {
                v[icase][i].first-=v[icase][0].first;
                v[icase][i].second-=v[icase][0].second;
            }
        }
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%s",mp[i]);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(mp[i][j]=='#')
                {
                    for(int k=0;k<t;k++)
                    {
                        if(vis[k]) continue;
                        // check for the k th constellation
                        length=v[k].size();
                        key=true;
                        for(int h=1;h<length;h++)
                        {
                            // map[i][j] as the first star of constellation
                            xx=v[k][h].first+i;
                            yy=v[k][h].second+j;
                            if(xx>=0 && xx<n && yy>=0 && yy<m && mp[xx][yy]=='#')
                                continue;
                            else
                            {
                                key=false;
                                break;
                            }
                        }
                        vis[k]=key;
                    }
                }
            }
        }
        for(int i=0;i<t;i++)
            if(vis[i])
                printf("Yes\n");
            else
                printf("No\n");
    }
    return 0;
}
