p1,p2,p3,x = map(int, input().split())
seq = []
pow1 = p1
INF = 10**18
for i in range(0,60):
  if p1**i > INF: break
  for j in range(0,60):
    if p1**i * p2**j > INF: break
    for k in range(0,60):
      if i+j+k == 0: continue
      if p1**i * p2**j * p3**k > INF: break
      seq.append(p1**i * p2**j * p3**k)
seq.sort()
print(seq[x-1])
