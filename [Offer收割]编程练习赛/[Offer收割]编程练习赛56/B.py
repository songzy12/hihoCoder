# coding: utf-8
# Your code here!

s = raw_input()

def dot_list(s):
    res = []
    if len(s) == 1 or s[0] != '0':
        res.append(s)
    if s[-1] == '0':
        return res
        
    for i in range(1, len(s)):
        head = s[:i]
        tail = s[i:]
        if len(head) > 1 and head[0] == '0':
            continue
        # here tail is valid for sure
        res.append(head + '.' + tail)
    return res

def solve(s):
    res = []
    for t in range(1, len(s)):
        
        first_list = dot_list(s[:t])
        second_list = dot_list(s[t:])
        
        for f in first_list:
            for b in second_list:
                res.append([f, b])
    return res

res = solve(s)
res.sort(key = lambda x: map(float, x))
for f,s in res:
    print f+','+s
