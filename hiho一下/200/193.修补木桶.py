# http://hihocoder.com/contest/hiho193/problem/1
n, m, l = map(int, input().split())
a = list(map(int, input().split()))

def solve(m, l):

    def check(t):
        # whether it is possible to make all >= t

        def get_count(index):
            # start from index, and make all >= t
            temp_a = a[index:] + a[:index]
            cnt = 0
            cur_i = 0
            while cur_i < len(temp_a):
                if temp_a[cur_i] >= t:
                    cur_i += 1
                    continue
                else:
                    cur_i += l
                    cnt += 1
            return cnt
            
        return min([get_count(i) for i in range(len(a))]) <= m

    left = min(a) # NOTE: use left rather than l
    right = max(a) + 1 # NOTE: here max(a) may be reachable

    # l is possible, r is not possible
    while right - left > 1:
        temp = (right + left) // 2
        if check(temp):
            left = temp
        else:
            right = temp
    return left

print(solve(m, l))

# Wrong Answer
