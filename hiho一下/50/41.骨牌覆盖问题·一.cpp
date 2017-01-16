#include<iostream>
#include<ctime>
using namespace std;

int main(){
	long beginTime = clock();
    int N;
	cin>>N;
	if (N == 1){
		cout<< 1 <<endl;
		return 0;
	}
	int temp, first = 1, second = 1;
	for(int i = 2; i <= N; i ++){
		temp = first;
		first = second;
		second = temp;
		second = (first + second) % 19999997;
	}
	cout<<second<<endl;
	long endTime = clock();
	cout<< beginTime<<" "<< endTime<<" "<< endTime - beginTime<<endl;
	system("pause");
	return 0;
}