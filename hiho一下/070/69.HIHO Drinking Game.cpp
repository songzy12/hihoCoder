#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000;
int a[N];
int n, k;

int getScore(int t)
{
	int res = 0;
	int rest = 0;
	for(int i = 0; i < n; ++i){
		rest = rest + t;
		if(rest > a[i]) {
			res++;
			rest = rest-a[i];
		}else 
			rest = 0;
	}
	return res;
}

int main()
{
	while(cin >> n >> k){
		for(int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		int low = 0, high = k+1;
		while(low < high){
		    if(low+1 == high) {
		        int res = getScore(low);
		        if(res*2<n) low=high;
		        break;
		    }
			int mid = (low+high)/2;
			int res = getScore(mid);
			if(res*2 < n) low = mid+1;
			else high = mid;
		}
		printf("%d\n", low);
	}
	return 0;
}

/*
The larger is T, the better is for Ho.
*/