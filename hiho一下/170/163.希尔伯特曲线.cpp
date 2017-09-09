#include <iostream>
using namespace std;

long long solve(int n, int x, int y) {
    //cout<<n<<" "<<x<<" "<<y<<endl;
    if (n == 1) {
        if (x == 1 && y == 1)
            return 1;
        if (x == 1 && y == 2)
            return 2;
        if (x == 2 && y == 2)
            return 3;
        return 4;
    }
    // left bottom
    long long rows =1L<<(n-1);
    long long prev =1L<<(2*(n-1));
    if (x <= rows && y <= rows) {
        return solve(n-1, y, x);
    } else if (x <= rows && y > rows) {
        return prev + solve(n-1, x, y-rows);
    } else if (x > rows && y > rows) {
        return 2*prev + solve(n-1, x-rows, y-rows);
    } else {
        x -= rows;
        return 3*prev + solve(n-1, rows+1-y, rows+1-x);
    }
}

int main() {
    int n, x, y;
    cin>>n>>x>>y;
    cout<<solve(n, x, y)<<endl;
    return 0;
}

// note 1L<<63