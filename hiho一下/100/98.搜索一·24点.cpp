// http://hihocoder.com/contest/hiho98/problem/1

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

float add(float a, float b) {
    return a + b;    
}

float mult(float a, float b) {
    return a * b;
}

float sub(float a, float b) {
    return a - b;
}

float inv_minus(float a, float b) {
    return b - a;
}

float div(float a, float b) {
    return a * 1.0 / b;
}

float inv_div(float a, float b) {
    return b * 1.0 / a;
}

bool used[4];
int number[4];
int nowNumber[4];
float (*ops[3])(float, float) ; 
float (*opType[])(float, float) = {&add, &mult, &sub, &inv_minus, &div, &inv_div};

float calcType1() {
    return ops[2](ops[1](ops[0](nowNumber[0], nowNumber[1]), nowNumber[2]), nowNumber[3]);
}

float calcType2() {
    return ops[1](ops[0](nowNumber[0], nowNumber[1]), ops[2](nowNumber[2], nowNumber[3]));
}

bool makeOperation(int depth) {
    if (depth >= 3) {
        float eps = 1e-3;
        if (abs(calcType1() - 24) < eps || abs(calcType2() - 24) < eps)
            return true;
        return false;
    }
    for (int i = 0; i < 6; ++i) {
        ops[depth] = opType[i];
        if (makeOperation(depth+1))
            return true;
    }
    return false;
} 

bool makeNumber(int depth) {
    if (depth>=4) {
        return makeOperation(0);
    }
    for (int i = 0; i < 4; ++i) {
        if (used[i]) 
            continue;
           
        nowNumber[depth] = number[i];
        used[i] = true;
        if (makeNumber(depth+1))
            return true;
        used[i] = false;
    }
    return false;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        memset(used, false, sizeof used);
        for (int i = 0; i < 4; ++i)
            cin>>number[i];
        
        cout<<(makeNumber(0)?"Yes":"No")<<endl;
    }
    return 0;
}