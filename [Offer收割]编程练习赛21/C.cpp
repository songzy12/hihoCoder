#include<bits/stdc++.h>
using namespace std;
#define MEM(a,b) memset(a,b,sizeof(a))
#define bug puts("bug");
#define MP make_pair
#define X first
#define Y second
typedef pair<int,pair<int,int> > pii;
int n,m,k,q;
pair<int,int> Q[10],S,T;
int d[8][2]={0,1,1,0,0,-1,-1,0,1,1,-1,1,1,-1,-1,-1};

int dis(pair<int,int> P){
    return abs(P.X-T.X)+abs(P.Y-T.Y);
}

int ok(pair<int,int> P){
    if(P.X<0||P.X>n||P.Y<0||P.Y>m) return 0;
    for(int i=0;i<q;i++)
        if(abs(P.X-Q[i].X)+abs(P.Y-Q[i].Y)<k) return 0;
    return 1;
}

bool BFS(){
    priority_queue<pii> que;
    if(ok(S)==0||ok(T)==0) return 0; // ok == 0: can be seen. return 0: cannot escape
    if(S==T) return 1;
    set<pair<int,int> > vis;
    que.push(MP(-dis(S),S));
    vis.insert(S);
    int cnt=0;
    while(!que.empty()){
        pii tm=que.top();
        que.pop();
        cnt++;
        if(cnt>5e4) return 0; // how many steps have been searched
        for(int i=0;i<8;i++){
            pii nxt=MP(0,MP(tm.Y.X+d[i][0],tm.Y.Y+d[i][1]));
            nxt.X=-dis(nxt.Y);
            if(ok(nxt.Y)){
                if(vis.count(nxt.Y)) continue;
                if(nxt.Y==T) return 1;
                vis.insert(nxt.Y),que.push(nxt);
            }
        }
    }
    return 0;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m>>k>>q;
        q++;
        for(int i=0;i<q;i++) cin>>Q[i].X>>Q[i].Y;
        cin>>S.X>>S.Y>>T.X>>T.Y;
        // use bfs to heuristically search a path from S to T
        if(BFS()) puts("Yes");
        else puts("No");
    }
    return 0;
}


/***
const int maxn=1e5+10;
int a[maxn],b[maxn],p[maxn],k[maxn],m,n;
int dp[11][maxn];
int main(){
    while(cin>>n>>m){
        for(int i=0;i<n;i++) cin>>a[i]>>b[i];
        for(int i=0;i<m;i++) cin>>k[i]>>p[i];
        for(int id=0;id<=10;id++){
            for(int i=0;i<=1000;i++){
                for(int j=0;j<=m;j++){
                    int hit=p[j]-id,val=k[j];

                }
            }
        }
    }
    return 0;
}
****/
