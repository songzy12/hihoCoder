#include <iostream>
#include <cstdio>
using namespace std;

void solve(int n) {
    for (int i = 0; i < n; ++i)
        printf(" ");
    for (int i = 0; i < n; ++i)
        printf("_");
    for (int i = 0; i < 3*n; ++i)
        printf(" ");
    for (int i = 0; i < n; ++i)
        printf("_");
    for (int i = 0; i < n; ++i)
        printf(" ");
    printf("\n");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1-i; ++j)
            printf(" ");
        printf("/");
        for (int j = n-i; j < n; ++j)
            printf(" ");

        for (int j = 0; j < n; ++j)
            printf(" ");

        for (int j = n-i; j < n; ++j)
            printf(" ");
        printf("\\");
        for (int j = 0; j < n-1-i; ++j)
            printf(" ");

        for (int j = 0; j < n; ++j)
            printf((i == n - 1)?"_":" ");

        for (int j = 0; j < n-1-i; ++j)
            printf(" ");
        printf("/");
        for (int j = n-i; j < n; ++j)
            printf(" ");

        for (int j = 0; j < n; ++j)
            printf(" ");

        for (int j = n-i; j < n; ++j)
            printf(" ");
        printf("\\");
        for (int j = 0; j < n-1-i; ++j)
            printf(" ");
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        printf("|");
        for (int j = 1; j < 7*n - 1; ++j)
            printf(" ");
        printf("|");
        printf("\n");
    }

    for (int i = 0; i < 3*n; ++i) {
        for (int j = 0; j < i; ++j)
            printf(" ");
        printf("\\");
        for (int j = 0; j < 7*n - 2*i - 2; ++j)
            printf((i == 3*n - 1) ? "_":" ");
        printf("/");
        for (int j = 0; j < i; ++j)
            printf(" ");
        printf("\n");
    }

    return;
}

int main() {
    int n;
    cin>>n;
    solve(n);
    return 0;
}