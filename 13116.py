T = int(input())
for _ in range(T):
  A,B = map(int, input().split())
  while A != B:
    if A > B:
      A //= 2
    else:
      B //= 2
  print(10*A)
