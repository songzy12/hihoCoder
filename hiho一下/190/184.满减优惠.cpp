// http://hihocoder.com/contest/hiho184/problem/1

#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn = 20;
int value[maxn];

int N;

int dp[1000*20];

int solve(int M) {
	memset(dp,0,sizeof(dp));
 
	/* 01背包 */
	for(int i = 0; i < N; ++i)
	{
		//printf("value[%d]: %d, M: %d\n", i, value[i], M);
		
		for(int j = M; j >= value[i]; --j)
		{
			int tmp = dp[j-value[i]] + value[i];
			if(tmp > dp[j])
			{
				dp[j] = tmp;
			}
			//printf("dp[%d]: %d\n", j, dp[j]);
		}
	}
	//printf("dp[M]: %d\n", dp[M]);
	return dp[M];
}

int main() {
	//freopen("in.txt", "r", stdin);
	int X;
	int sum = 0;
	cin>>N>>X;
	for (int i = 0; i < N; ++i) {
		cin>>value[i];
		sum += value[i];
	}
	if (sum < X) {
		cout<<-1<<endl;
		return 0;
	}
	//cout<<sum<<" "<<X<<endl;
	int target = sum - X;
	
	// now it is a 01 knapsack to get target
	// the answer would be X - result
	cout<<X + target - solve(target)<<endl;
	return 0;
}

// reference: http://www.ahathinking.com/archives/110.html