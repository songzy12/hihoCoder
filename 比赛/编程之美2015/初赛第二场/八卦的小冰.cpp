#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#define N 100005  
int c,T,n,m,q;  
int s[N],first[N],top;  
struct edge{  
    int y,next,w;  
}e[N<<5];  
long long res;  
void add(int x,int y,int w){  
    e[top].y = y;  
    e[top].w = w;  
    e[top].next = first[x];  
    first[x] = top++;  
}  
void update(int x){  
    int i,y;  
    for(i = first[x];i!=-1;i=e[i].next){  
        y = e[i].y;  
        if(s[x] == s[y])  
            res -= e[i].w;  
        else  
            res += e[i].w;  
    }  
}  
int change(int x,int y,int w){  
    int i,tmp = -1;  
    for(i = first[x];i!=-1;i=e[i].next){  
        if(e[i].y == y){  
            tmp = e[i].w;  
            e[i].w = w;  
            return tmp;  
        }  
    }  
    add(x,y,w);  
    return 0;  
}  
int main(){  
    scanf("%d",&T);  
    for(c = 1;c<=T;c++){  
        int i,j,a,b,w,op;  
        res = 0;  
        memset(first, -1, sizeof(first));  
        top = 0;  
        scanf("%d %d %d",&n,&m,&q);  
        for(i = 1;i<=n;i++)  
            scanf("%d",&s[i]);  
        for(i = 1;i<=m;i++){  
            scanf("%d %d %d",&a,&b,&w);  
            add(a,b,w);  
            add(b,a,w);  
            if(s[a] != s[b])  
                res += w;  
        }  
        printf("Case #%d:\n",c);  
        while(q--){  
            scanf("%d",&op);  
            if(op == 1){  
                scanf("%d",&a);  
                s[a] = 1-s[a];  
                update(a);  
            }else if(op == 2){  
                scanf("%d %d %d",&a,&b,&w);  
                j = change(a,b,w);  
                change(b,a,w);  
                if(s[a] != s[b]){  
                    res -= j;  
                    res += w;  
                }  
            }else  
                printf("%lld\n",res);  
        }  
    }  
    return 0;  
}
/*#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int persons[100];
int relations[100][100];

int main(){
	int T;
	cin>>T;
	for(int t=0; t<T; t++){
		cout<<"Case #"<<t+1<<":"<<endl;
		int N, M, Q;
		cin >> N>>M>>Q;
		memset(persons, 0, sizeof(persons));
		memset(relations, 0, sizeof(relations));
		for(int n=0; n<N; n++){
			int sex;
			cin>>sex;
			persons[n] = sex;
		}
		for(int m=0; m<M; m++){
			int x, y, z;
			cin>>x>>y>>z;
			relations[x-1][y-1] = z;
			relations[y-1][x-1] = z;
		}
		for(int q=0; q<Q; q++){
			int op;
			cin>>op;
			if(op == 1){
				int id;
				cin>>id;
				persons[id-1]= 1- persons[id-1];
			}
			else if (op == 2){
				int x, y, z;
				cin >>x>>y>>z;
				relations[x-1][y-1]=z;
				relations[y-1][x-1]=z;
			}
			else{
				int result = 0;
				for(int i=0; i<N; i++){
					for(int j=i+1; j<N; j++){
						if(persons[j] != persons[i]){
							result += relations[i][j];
						}
					}
				}
				cout<<result<<endl;
			}
		}
	}
}*/