#include<iostream>
#include<cstring>
using namespace std;
#define mod 100007
int dp[1005][1005];
char s[1005];

int F(int l, int r){
	if (dp[l][r] != -1)
		return dp[l][r];
	if (l > r){
		//cout<<"l: "<<l<<" r: "<<r<<" dp: "<<dp[l][r]<<endl;
		return dp[l][r] = 0;
	}
	if (l == r){
		//cout<<"l: "<<l<<" r: "<<r<<" dp: "<<dp[l][r]<<endl;
		return dp[l][r] = 1;
	}
	// discussed by a. l and r, b. l and not r, 
	// c. not l and r, d. not l and not r
	int & ret = dp[l][r];
	ret = (F(l+1, r) + F(l, r-1)) % mod;
	if (s[l] == s[r]) 
		ret++;
	else
		ret -= F(l+1, r-1);
	ret = (ret + mod) % mod; // for the subtraction
	//cout<<"l: "<<l<<" r: "<<r<<" dp: "<<dp[l][r]<<endl;
	return ret;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		memset(dp, -1, sizeof(dp));
		cin>>s;
		cout<<"Case #"<<i+1<<": "<< F(0, strlen(s)-1)<<endl;
	}
	return 0;
}

/*int sub(string s, int l, int r, int **temp){
	if (temp[l][r] != -1)
		return temp[l][r];
	if (l > r){
		temp[l][r] = 0;
		return 0;
	}
	if (l == r){
		temp[l][r] = 1;
		return 1;
	}
	if (l == r - 1){
		temp[l][r] = 2 + (s[l]==s[r] ? 1 : 0);
		return temp[l][r];
	}
	int result = 1 + sub(s, l, r - 1, temp);
	for(int i=l; i<r; i++){
		if(s[i]==s[r])
			result += 1 + sub(s, i+1, r-1, temp);
	}
	temp[l][r]=result % 100007;
	return temp[l][r];
}*/

/*int count(string s){
	int count[1000];
	int len = s.size();
	if(len == 0 || len == 1)
		return len;
	count[0] = (s[0] == s[1]) ? 3 : 2;
	count[1] = 1;
	if(len == 2)
		return count[0];
	for(int i=2; i<len; i++){
		for(int j=0; j<=i-2; j++){
			count[j] += 1;
			for(int k=j+1; k<i; k++)
				count[j] += (s[k-1] == s[i]) ? (1 + count[k]): 0;
			count[j] += (s[i-1] == s[i]) ? 1 : 0;
			count[j] %= 100007;
			if(i == len - 1)
				return count[0];
		}
		count[i-1] = (s[i-1] == s[i]) ? 3 : 2;
		count[i] = 1;
	}
}*/