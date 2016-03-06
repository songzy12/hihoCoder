#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#define fi first
#define se second
#define PA pair<int,int>
#define VI vector<int>
#define VP vector<PA >
#define mk(x,y) make_pair(x,y)
#define N 1000010
#define int64 long long
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
int i,j,k,n,m,te,T,t,K;
int a[N],id[N],b[N],f[N];
inline void read(int &x) {
	char p=getchar();
	for (;p<'0'||p>'9';p=getchar());
	for (x=0;p>='0'&&p<='9';x=x*10+p-48,p=getchar());
}
inline bool cc1(const int &A,const int &B) {
	return a[A]>a[B];
}
int get(int x) {
	return f[x]==x?x:f[x]=get(f[x]); //disjoint sets
}
int main() {
	scanf("%d",&T);
	For(te,1,T) {
		scanf("%d%d%d",&n,&m,&K);
		int64 an=0;
		For(i,1,n) read(a[i]),b[i]=0,id[i]=f[i]=i,an+=a[i];
		sort(id+1,id+n+1,cc1);
		For(i,1,m) {
			int x,y;
			read(x),read(y);
			f[get(x)]=get(y); 
			// f[x] = y, connect all together
		}
		For(i,1,n) {
			int A=get(i); // which set i belongs to
			if (!b[A]) b[A]=i; 
			else if (a[i]<a[b[A]]) b[A]=i; 
			// b[A] is the smallest cost of set A
		}
		m=m-K;
		//For(i,1,n) printf("%d ",b[i]); printf("\n");
		For(i,1,n) {
			int A=id[i]; // loop from smallest cost
			if (b[get(A)]!=A&&m) m--,an-=a[A]; 
			// if A is not the smallest one
		}
		printf("Case #%d: ",te);
		cout<<an<<endl;
	}
	return 0;
}