#include<iostream>
#include<ctime>
using namespace std;

/*int type2(int N);

int type(int N){
	if(N == 0)
		return 1;
	return 3*type(N-2)+2*type2(N-2);
}

int type2(int N){
	if(N == 0)
		return 0;
	return type(N-2) + type2(N-2);
}*/

int main(){
	int N;
	cin>>N;
	if (N % 2 == 1){
		cout<<0<<endl;
		return 0;
	}
	int len = N/2;
	//long time = clock();
	int type = 1;
	int type2 = 0;
	int tmp, tmp2;
	for(int i=1; i<len+1; i++){
		tmp = (3*type+2*type2)%12357;
		tmp2 =(type+type2)%12357;
		type = tmp;
		type2 = tmp2;
	}
	cout<<type<<endl;
	//cout<<"time: "<<clock()-time<<endl;
	return 0;
}