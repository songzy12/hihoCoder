#include <stdio.h>

#define N 100001

int a[N];
int b[N];
long long cnt = 0;

inline int readInt()
{
    int val = 0, ch;
    while(((unsigned)(ch = getchar() - '0')) > 9)
        ;
    val = ch;
    while(((unsigned)(ch = getchar() - '0')) <= 9)
        val = (val << 3) + (val << 1) + ch;
    return val;
}

void mergeSort(int l,int r){
    if(l >= r){return;}
    int m = l + (r - l) / 2;
    mergeSort(l,m);
    mergeSort(m+1,r);
    int i = l;
    int j = m+1;
    int k = l;
    while(i <= m && j <= r){
        if(a[i] <= a[j]){
            b[k++] = a[i++];        
        }
        else{
            b[k++] = a[j++];
            cnt += m - i + 1;
        }
    }
    while(i <= m){
        b[k++] = a[i++];
    }
    // just leave the larger part alone
    for(int i = l;i < k;i++){
        a[i] = b[i];
    }
}

int main(){
    //freopen("w39.in","r",stdin);
    int n = readInt();
    for(int i = 0;i < n;i++){
        a[i] = readInt();
    }
    mergeSort(0,n-1);
    printf("%lld\n",cnt);
}