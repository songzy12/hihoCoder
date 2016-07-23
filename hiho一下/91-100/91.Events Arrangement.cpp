// what the ...

#include<iostream>
#include <algorithm>
using namespace std;
int n,m,k;
struct EventSequence
{
	int a;
	int b;
	int c;
}event[1005];
int cmp(const void *p,const void *q)
{
	if((*(struct EventSequence*)p).b *1.0 / (*(struct EventSequence*)p).c < (*(struct EventSequence*)q).b *1.0 / (*(struct EventSequence*)q).c)
		return 1;
	else return -1;
}
int calc(int a,int b,int i)
{
	int t = (b-a)/event[i].c*event[i].a-(b-a)/event[i].c*((b-a)/event[i].c-1)/2*event[i].c*event[i].b-(b-a)/event[i].c*a*event[i].b;
	return t;
}
int solve()
{
	int r = 0;
	int tempValue1 = 0,tempValue2 = 0,value1 = 0,value2 = 0,tempValue = 0;
	int **f = new int *[n+1];
	for (int i = 0; i <= n; i++)
	{
		f[i] = new int [m];
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			f[i][j] = 0; 
		}
	}
	qsort(event,n+1,sizeof(struct EventSequence),cmp);
	//cout<<calc(0,4,2)<<endl;
	for (int i = 1; i <= n; i++)
	{
		int **q = new int *[event[i].c];
		for (int j = 0; j < event[i].c; j++)
		{
			q[j] = new int [(m-1)/event[i].c+1];
		}
		int *tail = new int[event[i].c]; 
		int *head = new int[event[i].c] ;
		for (int j = 0; j < event[i].c; j++)
		{
			tail[j] = 0;
			head[j] = 1;
			for (int r = 0; r <= (m-1)/event[i].c; r++)
			{
				q[j][r] = 0;
			}
		}
		for (int v = event[i].c; v <= m-1; v++)
		{
			r = v % event[i].c;   
			tail[r] = tail[r] + 1;
			q[r][tail[r]] = v;   
			while (tail[r] > head[r]) 
			{
				tempValue1 = calc(q[r][ tail[r] ]- event[i].c, v, i);
				value1 = f[i - 1][ q[r][tail[r]] - event[i].c] + tempValue1;
				tempValue2 = calc(q[r][ tail[r]-1 ]- event[i].c, v, i);
				value2 = f[i - 1][ q[r][tail[r]-1] - event[i].c] + tempValue2;
				if(value1 >= value2)
				{
					q[r][ tail[r] - 1 ] = q[r][ tail[r]];
					tail[r] = tail[r] - 1;
				}
				else
					break;
			}

			while((v - q[r][ head[r] ] + event[i].c) / event[i].c > k)
				head[r]++;
			tempValue = calc(q[r][ head[r] ] - event[i].c, v, i);
			//cout << tempValue << endl;
			f[i][v] = f[i - 1][ q[r][head[r]] - event[i].c] + tempValue;
		}
		for (int v = 1; v <= m-1; v++)
		{
			if (f[i][v] < f[i - 1][v])
			{
				f[i][v] = f[i - 1][v];
			}

		}
	}

	int Result = 0;
	for (int i = 0; i <= m-1; i++)
	{
		if (f[n][i] > Result)
		{
			Result = f[n][i];
		}
	}
	return Result;
}
int main()
{
	cin >> n >> m >> k; // different type: n, time: m, times: k
	event[0].b = 10000,event[0].c = 1;
	for (int i = 0; i < n; i++)
	{
		cin >> event[i+1].a >> event[i+1].b >> event[i+1].c; 
	}
	int s = solve();
	cout << s;
	return 0;
}