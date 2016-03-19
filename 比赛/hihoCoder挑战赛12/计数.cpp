#include<iostream>
#include<cstdio>
#include<cstring>
#define SZY
using namespace std;
// not suitable to start with 1<<(L_len - n_len)
// just brute force, the simplest one
int val[10000001];

int bin_len(int x){
	int len = 1;
	while((1<<len) <= x)
		len++;
	return len;
}

int main(){
#ifdef SZY
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	memset(val, 0, sizeof (val));
	int n, L, R;
	cin>>n>>L>>R;
	for(long long x = 1; x<10000001; x++){
		if(x*n-x > R) 
			break; // break timely
		long long temp = (x*n)^x;
		if(temp > R) 
			continue; // otherwise index out of range
		val[(x*n) ^ x] = 1;
	}
	int count = 0;
	for(int i = L; i <= R; i++)
		if(val[i] == 1)
			count++;
	cout<<count<<endl;
	return 0;
}