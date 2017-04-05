#include <iostream>
#include <math.h>
using namespace std;
typedef long long Long;
Long GCD(Long a, Long b)
{
    if (b == 0)
        return a;
    return GCD(b, a%b);
}
int main()
{
    Long N = 0, M = 0;
    Long countN = 0, countM = 0, countEqu = 0, nume = 0, deno = 0;
    cin >> N >> M;
    Long sqN = sqrt(N), sqM = sqrt(M);
    for (Long i = 1; i <= sqN; i++)
        if (N % i == 0)
        {
            countN += 2;
            if (i * i == N)
                countN--;
            if (M % i == 0)
                countEqu++;
            if (M%(N/i) == 0 && (N/i) != i)
                countEqu++;
        }
    for(Long i = 1; i <= sqM; i++)
        if (M % i == 0)
        {
            countM += 2;
            if (i*i == M)
                countM--;
        }
    nume = countEqu;
    deno = countN * countM;
    Long gcd = GCD(nume, deno);
    nume = nume / gcd;
    deno = deno / gcd;
    cout << deno << " " << nume;
    return 0;
}