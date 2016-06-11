#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 200000;//数组要开大些，防止越界
int n , dis[maxn] , isQueue[maxn];
vector < pair < int , int > > graph[maxn];//注意后面两个尖括号之前有空格！

class nodd
{
public:
    int x , y , num;
    //重载"<"符号
    bool operator < (const nodd  A) const {
        return x < A.x;
    }
} A[maxn];

void build()
{
    sort( A , A + n );
    for ( int i = 0; i < n; i ++ ) {
        int nex = i + 1;
        while ( nex < n && A[nex].x == A[i].x ) { //当两个点的x值相等时
            int a = A[nex].num , b = A[i].num; //排序后点的序号改变，不能直接用i表示，建立新的变量获取该点原来的序号
            graph[a].push_back( make_pair( b , 0 ) );//建立一条从a到b的边，距离为0
            graph[b].push_back( make_pair( a , 0 ) );//因为是无向图，同样建立一条从b到a的边，距离为0
            nex ++; //把所有x相等的点连起来
        }
        if ( i > 0 ) {
            int a = A[i].num , b = A[i-1].num;
            graph[a].push_back( make_pair( b , A[i].x - A[i-1].x ) );
            graph[b].push_back( make_pair( a , A[i].x - A[i-1].x ) );
        }
        i = nex - 1; //因为while中进行nex++操作，所以i要从最后一个x与前面一个点x值相同的点开始
    }
}

int main()
{
    scanf("%d",&n);
    for ( int i = 0; i < n; i ++ ) {
        scanf("%d%d",&A[i].x,&A[i].y);
        A[i].num = i;
    }
    build(); //将x之间的差作为距离
    for ( int i = 0; i < n; i ++ )
        swap( A[i].x , A[i].y );
    build(); //将y之间的差作为距离

    queue < int > q;
    for ( int i = 0; i < n; i ++ )
        dis[i] = 2000000000;
    dis[0] = 0;
    q.push( 0 ); //第一个点入队
    isQueue[0] = 1;
    while ( !q.empty() ) {
        int now = q.front() , nex;
        q.pop(); //当前点出队
        isQueue[now] = 0;
        for ( int i = graph[now].size()-1; i >= 0; i -- ) { //遍历跟当前点有边的所有点
            nex = graph[now][i].first; //获得与当前点相连的点的编号
            if ( dis[now] + graph[now][i].second < dis[nex] ) { //当前点到起点的距离+当前点到下一个点的距离<下一个点到起点的距离
                dis[nex] = dis[now] + graph[now][i].second;
                if ( isQueue[nex] == 0 ) { //如果下一个点不在队列中，入队；否则让它留在队中供其他点做判断
                    isQueue[nex] = 1 ;
                    q.push( nex );
                }
            }
        }
    }
    cout << dis[n-1] << endl;
    return 0;
}
