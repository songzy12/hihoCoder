// too complex

// mktime, tm, time_t: what makes your life easier

// scanf("%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec);

#include<bits/stdc++.h>
using namespace std;
struct node{
    long long Y,M,D,H,MIN,MM;
}a[100];
long long A[100];

long long ans(long long A,long long B,long long C,long long D,long long E,long long F){
    long long ANS;
    ANS=A*1e10;
    ANS+=B*1e8;
    ANS+=C*1e6;
    ANS+=D*1e4;
    ANS+=E*1e2;
    ANS+=F;
    return ANS;
}
void init(){
    int i,j,n,m;
    i=0;
    a[i].Y=1972;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1972;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1973;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1974;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1975;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1976;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1977;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1978;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1979;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1981;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1982;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1983;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1985;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1987;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1989;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1990;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1992;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1993;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1994;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1995;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1997;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=1998;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=2005;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=2008;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=2012;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=2015;a[i].M=6;a[i].D=30;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    a[i].Y=2016;a[i].M=12;a[i].D=31;a[i].H=23;a[i].MIN=59;a[i].MM=60;
    i++;
    for(i=0;i<27;i++){
        A[i]=ans(a[i].Y,a[i].M,a[i].D,a[i].H,a[i].MIN,a[i].MM);
    }
}
int main(void)
{
   struct tm time_cha;
   time_t t1,t2;
   long long d,AA,BB,AAA,BBB;
   int i;
   int year, month, day,hour,min,sec;
   init();
   scanf("%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec);
   time_cha.tm_year = year - 1900; 
   time_cha.tm_mon  = month - 1;
   time_cha.tm_mday = day;
   time_cha.tm_hour = hour;
   time_cha.tm_min  = min;
   time_cha.tm_sec  = sec;
   t1 = mktime(&time_cha);
   AA=ans(year,month,day,hour,min,sec);
   for(i=0;i<27;i++){
        //cout<<AA<<" "<<A[i]<<endl;
        if(AA>A[i]) continue ;
        break;
   }
   //cout<<i<<endl;
   AA=i;
   scanf("%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec);
   time_cha.tm_year = year - 1900;
   time_cha.tm_mon  = month - 1;
   time_cha.tm_mday = day;
   time_cha.tm_hour = hour;
   time_cha.tm_min  = min;
   time_cha.tm_sec  = sec;
   t2 = mktime(&time_cha);
   BB=ans(year,month,day,hour,min,sec);
   for(i=0;i<27;i++){
        if(BB>A[i]) continue ;
        break;
   }
   //cout<<i<<endl;
   BB=i;
   d=t2-t1;
   d+=(BB-AA);
   printf("%lld\n", d);
   return 0;
}
