#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <cstdio>
#include <climits>
#include <cmath>
#include <cstring>

using namespace std;

double dp[2100];//dp[j]��ʾ[0,j]��Χ�ڵ��������
struct atom{
	int l, r, w;//ÿ�������ε���߽磬�ұ߽磬����
}x[1100];
int n;
int compare(atom k1, atom k2) {//������߽���С��������
	return k1.l<k2.l;
}
double cal(int k) {//����Ϊk�ĵױߵ����������
	return k*k / 4.0;
}

double solve() {
	scanf("%d", &n); int lim = 0;//lim��ʾ�����ұ߽�
	for (int i = 1; i <= n; i++){
		int k1, k2, k3; 
        scanf("%d%d%d", &k1, &k2, &k3);
		x[i] = atom{ k1 - k2, k1 + k2, k3 }; 
        lim = max(lim, k1 + k2);
	}
	sort(x + 1, x + n + 1, compare);//������߽���С��
	for (int i = 0; i <= lim; i++) 
        dp[i] = -1e18;//��ʼ��Ϊ����С
	for (int i = 1; i <= n; i++) {
        // right most point chosen so far is j already
        // also note current left point is the right most one.
		for (int j = lim; j >= 0; j--)
            if (j >= x[i].r)
                dp[j] = max(dp[j], dp[j] + x[i].w);
            else if (j >= x[i].l) 
                dp[x[i].r] = max(dp[x[i].r], dp[j] - cal(x[i].r - x[i].l) + cal(j - x[i].l) + x[i].w);
            else 
                dp[x[i].r] = max(dp[x[i].r], dp[j] - cal(x[i].r - x[i].l) + x[i].w);
            
		dp[x[i].r] = max(dp[x[i].r], x[i].w - cal(x[i].r - x[i].l));
	}
	double ans = 0;
	for (int i = 0; i <= lim; i++) 
        ans = max(ans, dp[i]);//ȡ���з�Χ�е������
	return ans;
}
int main(){
	//freopen("t.txt", "r", stdin);
	int t; 
    scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		printf("Case #%d: %.2lf\n", i, solve());
	}
	return 0;
}