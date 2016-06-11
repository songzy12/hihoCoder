#include<iostream>
#include<cstdio>
#include<algorithm>
#define SZY
using namespace std;

int number[4];
char color[4];

int main(){
#ifdef SZY
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	string s;
	for(int i=0; i<4; i++){
		cin>>s;
		if('2'<=s[0] && s[0]<= '9')
			number[i] = s[0] - '2' + 2;
		else if(s[0] == 'J')
			number[i] = 11;
		else if(s[0] == 'Q')
			number[i] = 12;
		else if(s[0] == 'K')
			number[i] = 13;
		else if(s[0] == 'A')
			number[i] = 14;
		else
			number[i] = 10;
		if(s.size() == 2)
			color[i] = s[1];
		else
			color[i] = s[2];
	}
	sort(number, number+4);
	int dif = number[3] - number[0];
	
	bool repeat_n = false;
	if(number[0] == number[1] || number[1] == number[2] || number[2] == number[3])
		repeat_n = true;
	bool repeat_c = false;
	if(color[0] == color[1] && color[1] == color[2] && color[2] == color[3])
		repeat_c = true;
	
	//cout<<dif<<" "<<repeat_c<<" "<<repeat_n<<endl;
	if(repeat_n)
		cout<<"0/1"<<endl;
	else if(dif > 4){
		if(number[3] == 14 && number[2]<6){
			if(repeat_c)
				cout<<"1/16"<<endl;
			else
				cout<<"1/12"<<endl;
		}
		else
			cout<<"0/1"<<endl;
	}
	else if(number[3] == 14 || dif == 4){
		if(repeat_c)
			cout<<"1/16"<<endl;
		else
			cout<<"1/12"<<endl;
	}
	else if(dif == 3){
		if(repeat_c)
			cout<<"1/8"<<endl; // 6/48 = 1/8
		else
			cout<<"1/6"<<endl;
	}
	return 0;
}