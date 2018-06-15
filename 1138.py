N = int(input())
H = list(map(int,input().split()))
L = []
for i in range(N-1,-1,-1):
  L.insert(H[i],i+1)
for elem in L:
  print(elem,end=' ')
