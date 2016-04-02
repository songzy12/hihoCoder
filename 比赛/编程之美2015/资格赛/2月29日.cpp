#define _CRT_SECURE_NO_DEPRECATE
// can just use g++ and include<cstdio>
#include<stdio.h>
#include<string.h>

int since2000(int year, char month[10], int day){
    int temp;
	year -= 2000;
	temp = year / 4 - year / 100 + year / 400;
	if(year % 4==0 && year % 100!=0 || year % 400 == 0){
		if (month[0]=='J' && month[1]=='a')
			return temp - 1;
		if (month[0]=='F' && day < 29)
			return temp - 1;
	}
	return temp;
}

int main(){
	int T, i, day, year, temp1, temp2;
	char month[10];
	scanf("%d", &T);
	for(i=0; i<T; i++){
		scanf("%s %d, %d", &month, &day, &year);
		temp1 = since2000(year, month, day - 1);
		scanf("%s %d, %d", &month, &day, &year);
		temp2 = since2000(year, month, day);
		printf("Case #%d: %d\n", i+1, temp2 - temp1);
	}
	return 0;
}