#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
using namespace std;
const double eps = 1e-7;
double x[510]; // data type
double y[1050], A[1050][510]; //stupid!!!

/*void DEBUG(int m, int n){
	for(int i=0; i<m; ++i){
		for(int j=0; j<n; ++j)
			cout<<A[i][j]<<" ";
		cout<<y[i]<<endl;
	}
	cout<<endl;
}*/

string solve(int m, int n){
	int col, row;
	for(col=0, row=0; col<n&&row<m; row++, col++){ 
		int max_index = row;
		for (int i=row+1; i<m; ++i)
			if(fabs(A[i][col])>fabs(A[max_index][col]))
				max_index = i;
		
		if(max_index != row){
			for(int j=col; j<n; ++j)
				swap(A[max_index][j], A[row][j]);
			swap(y[max_index], y[row]);
		}
		
		if(fabs(A[row][col]) < eps){ // caution: row != max_index now
			row --; // same row
			continue;
		}
		
		for(int i=row+1; i<m; ++i){
			if(fabs(A[i][col]) < eps) // fabs() not abs()
				continue;
			for(int j = col+1; j<n; ++j)
				A[i][j] = (A[i][j]*A[row][col] - A[row][j]*A[i][col])/A[row][col];// reduce error
			y[i] = (y[i]*A[row][col]-y[row]*A[i][col])/A[row][col];
			A[i][col] = 0; // in the end!
		}
	}
	
	for(int i=row; i<m; i++)
		if(col<n && fabs(A[i][col]) > eps || \
		  fabs(y[i]) > eps) // no solution checked first
			return "No solutions";
	
	if(row < n) // row is column rank
		return "Many solutions";
	
	for(int i=n-1; i>=0; --i){
		double temp = 0;
		for(int j=i+1; j<n; ++j)
			temp += A[i][j]*x[j];
		x[i] = (y[i]-temp)/A[i][i];
	}
	return "";
}
int main(){
	int N,M;
	cin>>N>>M;
	for(int i=0; i<M; ++i){
		for(int j=0; j<N; ++j)
			cin>>A[i][j];
		cin>>y[i];
	}
	string ans = solve(M, N);
	if(ans != "")
		cout<<ans<<endl;
	else{
		for(int i=0; i<N; ++i)
			cout<<int(x[i]+eps)<<endl;
	}
	return 0;
}