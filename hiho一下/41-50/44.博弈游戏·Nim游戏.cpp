#include<iostream>
using namespace std;

int main(){
	int N;
	cin >> N;
	int A[100];
	for(int i=0; i<N; i++)
		cin>>A[i];
	int result = 0;
	// {0,0,0,\dots,0}, P-position, xor A[i] == 0
	for(int i=0; i<N; i++)
		result ^= A[i];
	if (result == 0)
		cout<<"Bob";
	else	
		cout<<"Alice";
	return 0;
}