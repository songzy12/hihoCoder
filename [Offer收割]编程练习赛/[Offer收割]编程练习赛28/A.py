T = int(raw_input())
for t in range(T):
    time = raw_input().strip()
    nums = set()
    for t in time:
        if '0' <= t <= '9':
            nums.add(t)

    def possible(nums):
        res = []
        # print nums
        
        for h0 in nums:
            for h1 in nums:
                res.append(h0 + h1)
        res.sort()
        return res
    
    pos_times = possible(nums)

    h, m, s = time.split(':')
    si = pos_times.index(s)
    if si+1 < len(pos_times) and int(pos_times[si+1]) <= 59:
        print h + ':' + m + ':' + pos_times[si+1]
        continue
    mi = pos_times.index(m)
    if mi+1 < len(pos_times) and int(pos_times[mi+1]) <= 59:
        print h + ':' + pos_times[mi+1] + ':' + pos_times[0]
        continue
    hi = pos_times.index(h)
    if hi+1 < len(pos_times) and int(pos_times[hi+1]) <= 23:
        print pos_times[hi+1] + ':' + pos_times[0] + ':' + pos_times[0]
    else:
        print pos_times[0] + ':' + pos_times[0] + ':' + pos_times[0]
