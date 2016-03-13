#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define pii pair<int, int>
#include<iostream>
#include<cstdio>

using namespace std;

const int MAXN = 1000;
struct Car {
    int id;
    double x, y, v;
    double ans;
}car[MAXN + 5];
int p[MAXN + 5];
double t[MAXN + 5];

bool sortByX(Car car1, Car car2) {
    return car1.x > car2.x;
}

bool sortById(Car car1, Car car2) {
    return car1.id < car2.id;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    int N;
    cin>>N;
    
    for (int i = 0; i < N; ++i) {
        cin>>car[i].x>>car[i].y>>car[i].v;
        car[i].id = i;
        p[i] = car[i].y;
    }
    memset(t, 0, sizeof t);
    sort(p, p + N);
    sort(car, car + N, sortByX);
    
    for (int i = 0; i < N; ++i) {
        int nowPosition = car[i].x;
        double temp = 0;
        for (int j = 0; j < N; ++j) {
            if (p[j] <= car[i].x)
                continue;
            temp += (p[j] - nowPosition) / car[i].v;
            temp = max(t[j], temp);
            t[j] = temp; // time to reach end point p[j].
            if (p[j] == car[i].y) {
                car[i].ans = temp;
                break;
            }
            nowPosition = p[j];
        }
    }
    
    sort(car, car + N, sortById);
    for (int i = 0; i < N; ++i)
        printf("%.2f\n", car[i].ans);
    
	return 0;
}