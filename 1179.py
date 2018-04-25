import sys
def solve(N,M):
  if M == 1: return N-1
  if N == 1: return 0
  if 1 < N <= M:
    return (solve(N-1,M)+M)%N
  NN = N-N//M
  tmp = (solve(NN,M)-N%M) % NN
  return M*tmp // (M-1)
sys.setrecursionlimit(0x100000)
N,M = map(int,input().split())
print(solve(N,M)+1)
