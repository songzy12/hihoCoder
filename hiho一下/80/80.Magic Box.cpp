#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int mx, cnt, a, b, c, x, y, z;

inline void init(void){
	cnt = a = b = c = 0;
	return;
}

inline bool check(void){
    int A = abs(a), B = abs(b), C = abs(c);
    if(x + y + z == A + B + C){
        if(x*x + y*y + z*z == A*A + B*B + C*C)
            return x*y*z == A*B*C;
    }
    return false;
    
}

int main(void){
	scanf("%d%d%d", &x, &y, &z);
	char ch;
	while ((ch = getchar()) != EOF){
		switch (ch){
        // a = R - Y, b = Y - B, c = B - R
		case 'R': a++; c--; break;
		case 'Y': a--; b++; break;
		case 'B': b--; c++; break;
		default: continue; break;
		}
		cnt++;
		if (check()){
			mx = max(mx, cnt);
			init();
		}
	}
	printf("%d\n", max(mx, cnt));

	return 0;
}
