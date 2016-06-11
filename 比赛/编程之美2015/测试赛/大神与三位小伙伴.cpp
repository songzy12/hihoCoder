#include<iostream>
#include<ctime>
#include<cstdio>
using namespace std;

int main(){
	// just compute the formula
	int tes;  
    long long ans,n,tmp,t1,t2;  
	const int mod = 1e9 + 7;
    cin>>tes;  
  
    for(int cas=1; cas<=tes; cas++)  
    {  
        cin>>n;  
        printf("Case %d: ",cas);  
        if(n%2==0)
        {  
            t1=n/2%mod;  
            t2=(n+1)%mod;  
        }  
        else  
        {  
            t1=(n+1)/2%mod;  
            t2=n%mod;  
        }
  
        tmp=t1*t2%mod;  
        ans=tmp*tmp%mod*tmp%mod;  
        tmp=tmp*(n%mod)%mod*((n+1)%mod)%mod*((n-1)%mod)%mod;  
        ans=(ans-tmp+mod)%mod;  
        cout<<ans<<endl;  
    }
    return 0;  
}

/*
int main(){
	long long m, n, res;
	cin >> m;
	int mod = 1e9+7;
	for(long long i = 0; i < m; i ++){
		cin >> n;
		res = 0;
		for(long long j = 0; j < n; j ++){
			int temp = (n - j) % mod;
			res += (((temp * temp) % mod) * temp) % mod;
		}
		for(long long j = 0; j < n - 2; j ++)
			for(long long k = j + 1; k < n - 1; k ++)
				for(long long l = k + 1; l < n; l ++){
					int temp1 = (n - j) % mod;
					int temp2 = (n - k) % mod;
					int temp3 = (n - l) % mod;
					res += 6 * (((temp1 * temp2) % mod) * temp3) % mod;
				}
		// do not care too much about format(<<endl)
		// remember to do the last modul
		// care for the data scale (long long)
		// be confident about yourself 
		// always TLE
		cout<<"Case "<<i+1<<": "<<res % mod<<endl;
	}
	return 0;
}*/