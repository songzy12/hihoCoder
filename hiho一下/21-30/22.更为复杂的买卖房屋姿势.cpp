#include <stdio.h>
const int N = 100001;
int sum[N << 2], mtag[N << 2], utag[N << 2], v[N], left, right, flag, value;
void build(int pos, int l, int r)
{
    if (l == r)
        sum[pos] = v[l];
    else
    {
        build(pos << 1, l, (l + r) >> 1);
        build(pos << 1 | 1, ((l + r) >> 1) + 1, r);
        sum[pos] = sum[pos << 1] + sum[pos << 1 | 1];
    }
}
void release(int pos, int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) >> 1;
        if (utag[pos])
        {
            utag[pos << 1] = utag[pos << 1 | 1] = utag[pos];
            mtag[pos << 1] = mtag[pos << 1 | 1] = 0;
            sum[pos << 1] = (mid - l + 1) * utag[pos];
            sum[pos << 1 | 1] = (r - mid) * utag[pos];
            utag[pos] = 0;
        }
        if (mtag[pos])
        {
            mtag[pos << 1] += mtag[pos];
            mtag[pos << 1 | 1] += mtag[pos];
            sum[pos << 1] += (mid - l + 1) * mtag[pos];
            sum[pos << 1 | 1] += (r - mid) * mtag[pos]; 
            mtag[pos] = 0;
        }
    }
}
void update(int pos, int l, int r)
{
    if (l >= left && r <= right)
    {
        if (flag)
        {
            utag[pos] = value;
            mtag[pos] = 0;
            sum[pos] = (r - l + 1) * value;
        }
        else
        {
            if (utag[pos])
                utag[pos] += value;
            else
                mtag[pos] += value;
            sum[pos] += (r - l + 1) * value;
        }
    }
    else if (l < r) 
    {
        int mid = (l + r) >> 1;
        if (mtag[pos] || utag[pos]) release(pos, l, r);
        if (right >= l && left <= mid) update(pos << 1, l, mid);
        if (left <= r && right > mid) update(pos << 1 | 1, mid + 1, r);
        sum[pos] = sum[pos << 1] + sum[pos << 1 | 1];
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i)
        scanf("%d", v + i);
    build(1, 0, n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d%d", &flag, &left, &right, &value);
        update(1, 0, n);
        printf("%d\n", sum[1]);
    }
    return 0;
}