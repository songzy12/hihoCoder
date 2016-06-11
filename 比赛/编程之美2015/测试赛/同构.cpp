#include<iostream>
using namespace std;
// stdio, memset, int A[100000]
int main(){
	int T;
	cin >> T;
	
	for(int i = 0; i < T; i ++){
		int N;
		cin >> N;
		int *A = new int [N];
		for(int j = 0; j < N; j ++)
			A[j] = 0;
		int k, l;
		for(int j = 0; j < N - 1; j ++){
			cin >> k >> l;
			A[k - 1] += 1;
			A[l - 1] += 1;
		}
		
		int M;
		cin >> M;
		int* B = new int[M];
		for(int j = 0; j < M; j ++)
			B[j] = 0;
		for(int j = 0; j < M - 1; j ++){
			cin >> k >> l;
			B[k - 1] += 1;
			B[l - 1] += 1;
		}

		int count = 0, max1 = 0;
		// just check whether B is a "flower"
		for(int j = 0; j < M; j ++){
			if(B[j] != 1){
				count ++;
				max1 = B[j];
			}
		}
		// if not, then we can always cross chrome
		if(count > 1){
			cout<<"Case "<<i + 1<<": YES"<<endl;
			continue;
		}

		int max2 = 0;
		for(int j = 0; j < N; j ++){
			if(A[j] > max2)
				max2 = A[j];
		}
		// use pigeon hole principle
		if((max2 + 1) / 2 >= max1){
			cout<<"Case "<<i + 1<<": NO"<<endl;
			continue;
		}
		cout<<"Case "<<i + 1<<": YES"<<endl;
		
		delete B;
		delete A;
	}
	system("pause");
	return 0;
}