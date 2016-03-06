#include<iostream>
using namespace std;

struct Tran{
	int x, y;
	double w;
	double area;
	double prof;
}trans[1001];

int main(){
	int T;
	cin>>T;
	for(int t=0;t<T;t++){
		int N;
		cin>>N;
		for(int n=0; n<N;n++){
			cin>>trans[n].x>>trans[n].y>>trans[n].w;

		}
	}
}
