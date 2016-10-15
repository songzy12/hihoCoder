#include<iostream>
#include<cstring>
using namespace std;

// same as Nim
int main(){
	int N;
	cin>>N;
	char t;
	int r = 0;
	for(int i=1; i<=N; i++){
		cin>>t;
		if(t=='H')
			r^=i;
	}
	if (r==0)
		cout<<"Bob"<<endl;
	else
		cout<<"Alice"<<endl;
	return 0;
} 