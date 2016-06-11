#include<iostream>
#include<cstring>
using namespace std;
void DFS(int x, int y, int col, int* d, int K){
	int k = 1<<K;
	if(col == K){
		d[y*k+x] = 1;
		return;
	}
	DFS(x<<1, (y<<1)|1, col+1, d, K); // | instead of +
	DFS((x<<1)|1, y<<1, col+1, d, K);
	if(col + 2 <= K)
		DFS((x<<2)|3, (y<<2)|3, col+2, d, K);
}

void Mult(int *A, int* d, int k){
	int *B = new int [k];
	memset(B, 0, k*sizeof(int));
	for(int i=0; i<k; i++)
		for(int j=0; j<k; j++){
			B[i] += A[j]*d[j * k + i];
			B[i] %= 12357;
		}
	memcpy(A, B, k*sizeof(int));
	delete B;
}

void Mult2(int *r, int *d, int k){
	int *t = new int[k*k];
	memset(t, 0, sizeof(int)*k*k);
	for(int i=0; i<k; i++)
		for(int j=0; j<k; j++)
			for(int l=0; l<k; l++){
				t[i*k +l] += r[i*k+j]*d[j*k+l];
				t[i*k +l] %= 12357; //do mod each time
			}
	memcpy(r, t, k*k*sizeof(int));
	//cannot cpy long long to int
}

void Pow(int *d, int k, int n){
	int *r = new int [k*k];
	for(int i=0; i<k; i++)
		for(int j=0; j<k; j++)
			r[i*k +j]= i==j?1:0;
	

	while(n){
		if(n&1)
			Mult2(r, d, k);
		n >>= 1;
		Mult2(d, d, k);
	}
	memcpy(d, r, sizeof(int)*k*k);
	delete r;
}

int main(){
	int K;
	int N;
	cin>>K>>N;
	int k = 1<<K; //instead of pow(2, K)
	int *d = new int [k*k];
	memset(d, 0, k*k*sizeof(int));
	DFS(0, 0, 0, d, K);
	Pow(d, k, N);

	cout<<d[(k-1)*k + (k-1)]<<endl; 
	//instead of mult(A, d, k)
	delete d;
	return 0;
}