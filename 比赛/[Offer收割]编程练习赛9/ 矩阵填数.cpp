// no idea, Catalan number
// https://mathoverflow.net/questions/74908/generalizing-the-catalan-number-enumerative-combinatorics/74913#74913

#include<stdio.h>  
#include<iostream>  
#include<string.h>  
#include<string>  
#include<ctype.h>  
#include<math.h>  
#include<set>  
#include<map>  
#include<vector>  
#include<queue>  
#include<bitset>  
#include<algorithm>  
#include<time.h>  
using namespace std;  
void fre() { freopen("c://test//input.in", "r", stdin); freopen("c://test//output.out", "w", stdout); }  
#define MS(x, y) memset(x, y, sizeof(x))  
#define ls o<<1  
#define rs o<<1|1  
typedef long long LL;  
typedef unsigned long long UL;  
typedef unsigned int UI;  
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b > a)a = b; }  
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b < a)a = b; }  
const int N = 0, M = 0, Z = 1e9 + 7, inf = 0x3f3f3f3f;  
template <class T1, class T2>inline void gadd(T1 &a, T2 b) { a = (a + b) % Z; }  
int casenum, casei;  
int n, m;  
LL qpow(LL x, int p)  
{  
    LL y = 1;  
    while (p)  
    {  
        if (p & 1) y = y * x % Z;  
        x = x * x % Z;  
        p >>= 1;  
    }  
    return y;  
}  
int main()  
{  
    while(~scanf("%d%d", &n, &m))  
    {  
        LL ans = 1;  
        for (int i = 2; i <= n * m; ++i)ans = ans * i % Z;  
        for (int i = 1; i <= n; ++i)  
        {  
            for (int j = 1; j <= m; ++j)  
            {  
                ans = ans * qpow(i + j - 1, Z - 2) % Z;  
            }  
        }  
        printf("%lld\n", ans);  
  
    }  
    return 0;  
}  
/* 
【题意】 
n * m个点放入矩阵使得行列有序 
 
【分析】 
★这种思维模式很重要★ 
其实，我们发现，这题，不光最后形成的n * m的矩阵需要满足横增竖增的条件，其他的任何一个子矩阵也都要满足这个条件。 
也就是说。我们在形成一个n * m矩阵的过程中，从细到巨，每一步也都要符合目标的限制条件。 
这样做法就有了—— 
我们for循环形成i*j的矩阵，之前的 
(i - 1) * (j - 1)、(i)*(j - 1)、(i - 1)*j 这三种类型的矩阵显然都是满足目标条件的。 
那么其实我们只要调整使得(i, j)这个点也满足这个条件即可。 
如何调整呢？ 
与(i, j)产生关系的是其上面的i - 1个点和其左边的j - 1个点 
这一共i + j - 1个点中，我们要调整(i, j)为相对最大的，所以/=(i + j - 1) 
这样全部扫描一遍。就AC啦！ 
 
*/ 