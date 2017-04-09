#include<stdio.h>
#include<iostream>
#include<string.h>
#include<map>
using namespace std;
typedef unsigned long long ll;

// just stimulation the situation.
// notice the initial value 
struct node
{
    int z,a[4];
    bool operator<(const node &no) const
    {
        if(z!=no.z) return z<no.z;
        for(int i=0;i<4;i++)
            if(a[i]!=no.a[i]) return a[i]<no.a[i];
    }
};
map<node,ll> M;
int num[100],n;
ll dfs(node no)
{
    if(M.count(no))
    {
        return M[no];
    }
    if(no.a[0]==0&&no.a[1]==0&&no.a[2]==0&&no.a[3]==0)
    {
        return 1;
    }
    ll ans=0;
    for(int i=0;i<4;i++)
    {
        if(no.a[i]!=0)
        {
            node no2;
            no2.z=i-1;
            no2.a[0]=no.a[0];
            no2.a[1]=no.a[1];
            no2.a[2]=no.a[2];
            no2.a[3]=no.a[3];
            no2.a[i]--;
            if(i!=0) no2.a[i-1]++;
            if(i==no.z)
            {
                ans+=(no.a[i]-1)*(i+1)*dfs(no2);
            }
            else
            {
                ans+=(no.a[i])*(i+1)*dfs(no2);
            }
        }
    }
    return M[no]=ans;
}
int main()
{
    int t,i,cas=1;
    char s[5];
    scanf("%d",&t);
    while(t--)
    {
        memset(num,0,sizeof(num));
        scanf("%d",&n);
        for(i=0;i<n;++i)
        {
            scanf("%s",s);
            if(s[0]>='2'&&s[0]<='9')
            {
                num[s[0]-'0']++;
            }
            else
            {
                if(s[0]=='A')
                {
                    num[1]++;
                }
                else if(s[0]=='T')
                {
                    num[10]++;
                }
                else if(s[0]=='J')
                {
                    num[11]++;
                }
                else if(s[0]=='Q')
                {
                    num[12]++;
                }
                else if(s[0]=='K')
                {
                    num[13]++;
                }
            }
        }
        node no;
        no.z=-1;
        memset(no.a,0,sizeof(no.a));
        for(i=1;i<=13;i++)
        {
            if(num[i]!=0) no.a[num[i]-1]++;
        }
        printf("Case #%d: %llu\n",cas++,dfs(no));
    }
    return 0;
}

/*#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
// http://www.cnblogs.com/syiml/p/4480372.html
// http://blog.csdn.net/dumeichen/article/details/45288265
typedef unsigned long long ULL;

int card[13];
int a[52], n;
ULL ans, factor;

void Main(int caseNumber)
{
    memset(card, 0, sizeof(card));
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char ch1, ch2;
        cin >> ch1 >> ch2;
        switch (ch1) {
            case 'A': ++card[0]; break;
            case '2': ++card[1]; break;
            case '3': ++card[2]; break;
            case '4': ++card[3]; break;
            case '5': ++card[4]; break;
            case '6': ++card[5]; break;
            case '7': ++card[6]; break;
            case '8': ++card[7]; break;
            case '9': ++card[8]; break;
            case 'T': ++card[9]; break;
            case 'J': ++card[10]; break;
            case 'Q': ++card[11]; break;
            case 'K': ++card[12]; break;
        }
    }
    factor = 1;
    n = 0;
    for (int i = 0; i < 13; ++i) {
        int factorial = 1;
        for (int j = 1; j <= card[i]; ++j) {
            factorial *= j;
            a[n++] = i;
        }
        factor *= factorial;
    }
    ans = 0;
    do {
        bool isValid = true;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] == a[i + 1]) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            ans += factor;
        }
    }
    while (next_permutation(a, a + n)); // next permutation
    cout << "Case #" << caseNumber << ": " << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i)
        Main(i);
}*/