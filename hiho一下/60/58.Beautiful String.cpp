#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
#include<iomanip>
#define x first
#define y second
#define DEBUG
using namespace std;
int main(){
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	string s;
	while(n--){
		//or (a,2),(b,3),(c,2)
		int size, last_len=0, cur_len = 1, state = 0;
		cin>>size;
		cin>>s;
		char last_char = s[0];
		int i;
		for(i=1; i<size; ++i){
			if(s[i]-last_char == 0){
				cur_len ++;
				if(state == 1 && cur_len > last_len)
					state = 0;
				else if(state == 2 && cur_len == last_len){
					cout<<"YES"<<endl;
					break;
				}
			}else if(s[i]-last_char == 1){
				last_char = s[i];
				last_len = cur_len;
				cur_len = 1;
				if(state == 0){
					state = 1;
				}else{
					if(cur_len >= last_len){
						cout<<"YES"<<endl;
						break;
					}
					if(state == 1){
						state = 2;
					}
				}
			}else{
				state = 0;
				last_char = s[i];
				cur_len = 1;
			}
		}
		if(i==size)
			cout<<"NO"<<endl;
	}
	return 0;
}