T = int(raw_input())

def valid(S, i, j):
    if (j - i) % 2 == 0:
        return False

    while i < j:
        if S[i] != S[j]:
            return False
        i += 1
        j -= 1
    return True

def get_dp(S, i, j, dp):
    if i == j:
        return 1
    if (i, j) in dp:
        return dp[i, j]
    
    ans = 1 + min(get_dp(S, i + 1, j, dp), get_dp(S, i, j - 1, dp))
    if valid(S, i, j):
        ans = min(ans, 1 + get_dp(S, i, (i + j) // 2, dp))
    dp[i, j] = ans
    return ans


def solve(S):
    dp = {}
    if not S:
        return 0
    return get_dp(S, 0, len(S) - 1, dp)


for t in range(T):
    S = raw_input()
    print(solve(S))
