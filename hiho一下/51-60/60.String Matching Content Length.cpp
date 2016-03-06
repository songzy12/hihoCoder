#include<stdio.h>
#include<string.h>
#define max(a, b) a>b?a:b

/*
dp1[i][j] = max{dp[i-k][j-k]+k} = max{dp[i-3][j-3]+3, dp[i-4][j-4]+4, dp[i-5][j-5]+5, ... }
dp1[i-1][j-1] = max{dp[i-1-3][j-1-3]+3, dp[i-1-4][j-1-4] + 4, dp[i-1-5][j-1-5]+5 ... } = max{dp[i-4][j-4]+3, dp[i-5][j-5]+4, dp[i-6][j-6]+5, ... }
dp1[i][j] = max{dp1[i-1][j-1] + 1, dp[i-3][j-3]+3}
*/

char a[2101];
char b[2101];
char dp[2100][2100];
char dp1[2100][2100];
char ff[2100][2100];
int main(void)
{
    int len_a, len_b;
    int i_a, i_b;
    int j;
    
    scanf("%s%s", a, b);
    len_a = strlen(a);
    len_b = strlen(b);
    
    for (i_a=1; i_a<=len_a; i_a++)
    {
        for (i_b=1; i_b<=len_b; i_b++)
        {
            if (a[i_a-1] == b[i_b-1])
            {
                ff[i_a][i_b] = ff[i_a-1][i_b-1] + 1;
            }
            else
            {
                ff[i_a][i_b] = 0;
            }
            // printf("ff %2d %2d %d\n", i_a, i_b, ff[i_a][i_b]);
        }
    }
    
    for (i_a=1; i_a<=len_a; i_a++)
    {
        for (i_b=1; i_b<=len_b; i_b++)
        {
            dp[i_a][i_b] = max(dp[i_a-1][i_b], dp[i_a][i_b-1]);
            if (ff[i_a][i_b] >= 3)
            {
                dp[i_a][i_b] = max(dp[i_a][i_b], dp1[i_a-3][i_b-3] + 3);
                if (ff[i_a][i_b] > 3)
                {
                    dp[i_a][i_b] = max(dp[i_a][i_b], dp[i_a-1][i_b-1] + 1);
                }
            }
            dp1[i_a][i_b] = max(dp1[i_a-1][i_b], dp1[i_a][i_b-1]);
            dp1[i_a][i_b] = max(dp1[i_a][i_b], dp[i_a][i_b]);
            // printf("dp %2d %2d %d\n", i_a, i_b, dp[i_a][i_b]);
        }
    }
    printf("%d\n", dp[len_a][len_b]);
    return 0;
}
