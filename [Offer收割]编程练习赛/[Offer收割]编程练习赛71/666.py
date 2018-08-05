N = int(raw_input())

dp = {}


def get_dp(n, i):
    if (n, i) in dp:
        return dp[n, i]
    if i == 0:
        if n < 0:
            return 0
        if n == 0:
            return 1
        ans = 9 * (get_dp(n - 1, 0) + get_dp(n - 2, 0) + get_dp(n - 3, 0))
    elif i == 1:
        if n < 3:
            return 0
        if n == 3:
            return 1
        ans = 9 * (get_dp(n - 1, 1) + get_dp(n - 2, 1) +
                   get_dp(n - 3, 1)) + get_dp(n - 3, 0)
    dp[n, i] = ans % 1000000007
    return dp[n, i]


print(get_dp(N, 1))
