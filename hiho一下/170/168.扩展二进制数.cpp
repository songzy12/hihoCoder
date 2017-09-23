#include<iostream>
using namespace std;

int calc(int n) {
        if (n == 0) return 1;
        if (n % 2 == 0) return calc(n / 2) + calc(n / 2 - 1);
        return calc(n / 2);
}

int main() {
        int n;
        cin >> n;
        cout << calc(n) << endl;
        return 0;
}