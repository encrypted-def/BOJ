T = int(input())
for _ in range(T):
  N = input()
  l = len(N)
  N = int(N)
  if N >= 10**l // 2:
    N = 10**l // 2
  print(N*(10**(l)-1-N))
