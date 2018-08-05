N = int(raw_input())
A = map(int, raw_input().split())

head = 1
while head < len(A) and A[head] >= A[head - 1]:
    head += 1

tail = len(A) - 1
while tail - 1 >= 0 and A[tail - 1] <= A[tail]:
    tail -= 1

# A[:head] is valid
# A[tail:] is valid


# print(head, tail)
def solve():
    if head > tail:
        return 0 # rather than N

    ans = min(N - head, tail)
    j = tail
    for i in range(head):
        # for each head, we compute the tail
        while j < N and A[j] < A[i]:
            j += 1
        if j == N:
            break
        # print(i, j)
        ans = min(ans, j - i - 1)
    return ans

print(solve())
