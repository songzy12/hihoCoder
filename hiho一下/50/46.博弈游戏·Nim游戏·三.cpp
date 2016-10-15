#include<iostream>
using namespace std;

int sg(int k){
	if (k==0)
		return 0;
	if (k%4 == 1||k%4==2)
		return k;
	if (k%4 == 3) 
		return k+1;
	if (k%4 == 0) // 0, not 4
		return k-1;
}

int main(){
	int N;
	cin>>N;
	int sum = 0, t;
	for(int n=0; n<N; n++){
		cin>>t;
		sum ^= sg(t); // ^ not |
	}
	if(sum==0)
		cout<<"Bob"<<endl;
	else
		cout<<"Alice"<<endl;
	return 0;
}