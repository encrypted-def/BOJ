def parse():
  S = input().split()
  return int(S[0]), int(''.join(S[1].split('.')))

while True:
  n,m = parse()
  D = [0]*(m+1)
  if n == 0: break
  for _ in range(n):
    c,p = parse()
    for i in range(p,m+1):
      D[i] = max(D[i],D[i-p]+c)
  print(D[m])
  
  
