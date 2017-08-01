// if for one [A,B], it consume more than M, then -1
// otherwise, the answer always exists

#include <bits/stdc++.h> 

using namespace std;
 
typedef long long ll;
const int maxn = 2000005;
const int maxh = 20;
const int inf = 1<<29;

int n, m, t, busy, wt;

int oc[maxn];
bool vs[maxn];

int get(int l, int r)
{
    if(l==r)
        return 0;
    if(l)
        return oc[r-1] - oc[l-1];
    return oc[r-1];
}

int gt[maxn][maxh];

int pre[maxn];
int main() 
{
    cin >> n >> m >> t >> busy >> wt;
    int a, b;
    for(int i=0;i<2*t;i++)
        oc[i] = wt;
    for(int i=1;i<=n;i++)
    {
        cin >> a >> b;
        for(int j=a;j<b;j++)
        {
            oc[j] = busy;
            oc[j+t] = busy;
        }
        for(int j=a+1;j<b;j++)
        {
            vs[j] = 1;
            vs[j+t] = 1;
        }
    }
    pre[0] = 0;
    for(int i=1;i<2*t;i++)
    {
        if(vs[i]==0)
            pre[i] = i;
        else
            pre[i] = pre[i-1];
    }
    for(int i=1;i<2*t;i++)
        oc[i] += oc[i-1];
    //for(int i=0;i<2*t;i++)
    //    printf("oc[%d]=%d\n",i,oc[i]);
    for(int i=0;i<2*t;i++)
    {
        int l = i, r = 2 * t;
        int res = i;
        while(l<=r)
        {
            int mid = (l+r)>>1;
            if(get(i, mid)<=m)
            {
                res = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        //printf("i=%d, res=%d\n", i, res);
        gt[i][0] = max(i, pre[res]);
    }
    for(int j=1;j<maxh;j++)
    {
        for(int i=0;i<2*t;i++)
        {
            if(gt[i][j-1]>=2*t)
                gt[i][j] = 2 * t;
            else
                gt[i][j] = gt[gt[i][j-1]][j-1];
        }
    }
    int res = inf;
    for(int i=0;i<t;i++)
    {
        int cnt = 0;
        int p = i;
        for(int j=maxh-1;j>=0;j--)
        {
            if(gt[p][j]<i+t)
            {
                p = gt[p][j];
                cnt += (1<<j);
            }
        }
        if(gt[p][0]>=i+t)
            res = min(res, cnt + 1);
    }
    if(res==inf)
        cout << -1 << endl;
    else
        cout << res << endl;
}