#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
#include<iomanip>
#define DEBUG
using namespace std;
int x[5][6], y[30], A[30][5][6] = {0};

void debug(){
	for(int i=0; i<30; ++i){
		for(int j=0; j<5; ++j)
			for(int k=0; k<6; ++k)
				cout<<A[i][j][k]<<" ";
		cout<<y[i]<<endl;
	}
	cout<<endl;
}

void solve(){
	for(int i=0; i<30; ++i){
		//debug();
		if(A[i][i/6][i%6]!=1){
			for(int j=i+1; j<30; j++){
				if(A[j][i/6][i%6]){
					for(int k = i; k<30; ++k)
						swap(A[i][k/6][k%6],A[j][k/6][k%6]);
					swap(y[i], y[j]);
					break;
				}
			}
		}
		for(int j=i+1; j<30; j++){
			if(A[j][i/6][i%6]){
				for(int k = i; k<30; ++k)
					A[j][k/6][k%6] ^= A[i][k/6][k%6];
				y[j] ^= y[i];
			}
		}
	}
	for(int i=29; i>=0; --i){
		x[i/6][i%6] = y[i];
		for(int j=i+1; j<30; j++)
			x[i/6][i%6] ^= A[i][j/6][j%6]*x[j/6][j%6];
	}
}

int main(){
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
	string s;
	int t = 0;
	for(int i=0; i<5; ++i){
		cin>>s;
		for(int j=0; j<6; ++j)
		y[t++] = 1^(s[j] == '0' ? 0 : 1);
	}
	/*for(int i=0; i<30; ++i){
		cout<<y[i]<<" ";
	}
	cout<<endl;*/
	for(int i=0; i<30; ++i){
		int row = i/6, col = i%6;
		for(int j=0; j<5; ++j){
			for(int k=0; k<6; ++k){
				if(abs(j-row)+abs(k-col)<=1)
					A[i][j][k] = 1;
				//cout<<A[i][j][k]<<" ";
			}
			//cout<<endl;
		}
		//cout<<endl;
	}
	//A[i][j][k] * x[j][k] = y[i]
	solve();
	t = 0;
	for(int i=0; i<5; ++i)
		for(int j=0; j<6; ++j)
			x[i][j] ? t++: 0;
	cout<<t<<endl;
	for(int i=0; i<5; ++i)
		for(int j=0; j<6; ++j)
			if(x[i][j])
				cout<<(i+1)<<" "<<(j+1)<<endl;
	return 0;
}