N, K = map(int, raw_input().split())
A = list(map(int, raw_input().split()))

def solve(A):
    
    ans = sum([1 if (x % K == 0) else 0 for x in A])
    if K % 2 == 0:
        ans = max(ans, sum([1 if (x % K == K // 2) else 0 for x in A]))
    if ans >= 2:
        return ans
    
    A = set([x % K for x in A])
    for t in range(K):
        if K - t in A:
            return 2
    
    return -1

print(solve(A))
