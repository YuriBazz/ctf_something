n = int(input())

l= [0]*n

for ind in range (n):
    l[ind] = int(input())


k = int(input())
for i in range (k):
    res = 0
    inp = list(map(int,input().split()))
    if len(inp) > 0: inp.pop(0)
    for x in inp:
        res += l[x-1]
    print (res)