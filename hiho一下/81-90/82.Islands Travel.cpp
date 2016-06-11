#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 200000;//����Ҫ����Щ����ֹԽ��
int n , dis[maxn] , isQueue[maxn];
vector < pair < int , int > > graph[maxn];//ע���������������֮ǰ�пո�

class nodd
{
public:
    int x , y , num;
    //����"<"����
    bool operator < (const nodd  A) const {
        return x < A.x;
    }
} A[maxn];

void build()
{
    sort( A , A + n );
    for ( int i = 0; i < n; i ++ ) {
        int nex = i + 1;
        while ( nex < n && A[nex].x == A[i].x ) { //���������xֵ���ʱ
            int a = A[nex].num , b = A[i].num; //���������Ÿı䣬����ֱ����i��ʾ�������µı�����ȡ�õ�ԭ�������
            graph[a].push_back( make_pair( b , 0 ) );//����һ����a��b�ıߣ�����Ϊ0
            graph[b].push_back( make_pair( a , 0 ) );//��Ϊ������ͼ��ͬ������һ����b��a�ıߣ�����Ϊ0
            nex ++; //������x��ȵĵ�������
        }
        if ( i > 0 ) {
            int a = A[i].num , b = A[i-1].num;
            graph[a].push_back( make_pair( b , A[i].x - A[i-1].x ) );
            graph[b].push_back( make_pair( a , A[i].x - A[i-1].x ) );
        }
        i = nex - 1; //��Ϊwhile�н���nex++����������iҪ�����һ��x��ǰ��һ����xֵ��ͬ�ĵ㿪ʼ
    }
}

int main()
{
    scanf("%d",&n);
    for ( int i = 0; i < n; i ++ ) {
        scanf("%d%d",&A[i].x,&A[i].y);
        A[i].num = i;
    }
    build(); //��x֮��Ĳ���Ϊ����
    for ( int i = 0; i < n; i ++ )
        swap( A[i].x , A[i].y );
    build(); //��y֮��Ĳ���Ϊ����

    queue < int > q;
    for ( int i = 0; i < n; i ++ )
        dis[i] = 2000000000;
    dis[0] = 0;
    q.push( 0 ); //��һ�������
    isQueue[0] = 1;
    while ( !q.empty() ) {
        int now = q.front() , nex;
        q.pop(); //��ǰ�����
        isQueue[now] = 0;
        for ( int i = graph[now].size()-1; i >= 0; i -- ) { //��������ǰ���бߵ����е�
            nex = graph[now][i].first; //����뵱ǰ�������ĵ�ı��
            if ( dis[now] + graph[now][i].second < dis[nex] ) { //��ǰ�㵽���ľ���+��ǰ�㵽��һ����ľ���<��һ���㵽���ľ���
                dis[nex] = dis[now] + graph[now][i].second;
                if ( isQueue[nex] == 0 ) { //�����һ���㲻�ڶ����У���ӣ������������ڶ��й����������ж�
                    isQueue[nex] = 1 ;
                    q.push( nex );
                }
            }
        }
    }
    cout << dis[n-1] << endl;
    return 0;
}
