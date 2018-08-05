# coding: utf-8
# Your code here!

N, M = map(int, raw_input().split())

MAXN = 100000

father = [i for i in range(MAXN+5)]
from collections import defaultdict

not_same = defaultdict(set)

def find(x):
    while father[x] != x :
        x = father[x] = father[father[x]]
    return x

def union(x, y):
    fx = find(x)
    fy = find(y)
    if fx >= fy:
        fx, fy = fy, fx
    # now fx < fy
    father[fy] = fx
    for t in not_same[fy]:
        not_same[t].remove(fy) # optimized for future merge
        not_same[t].add(fx)
    not_same[fx] = not_same[fx].union(not_same[fy])

for m in range(M):
    s = raw_input().split()
    if s[0] == 'R':
        x, y, t = map(int, s[1:])
        if t == 1:
            union(x, y)
        else:
            fx = find(x)
            fy = find(y)
            not_same[fx].add(fy)
            not_same[fy].add(fx)
    else:
        # s[0] == 'Q'
        x, y = map(int, s[1:])
        fx = find(x)
        fy = find(y)
        if fx == fy:
            print 1
        elif fx in not_same[fy]:
            print 2
        else:
            print 3
        
