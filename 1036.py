def d(c):
  if ord('0') <= ord(c) <= ord('9'):
    return ord(c)-ord('0')
  return ord(c)-ord('A')+10
def to36(n):
  if n == 0:
    return "0"
  S = ""
  d = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
  while n > 0:
    S += d[n%36]
    n = n // 36
  return S[::-1]
N = int(input())
val = [0]*36
for _ in range(N):
  S = input()
  for i in range(len(S)):
    val[d(S[i])] += 36**(len(S)-i-1)
K = int(input())
arr = [[0]*2 for i in range(36)]
for i in range(36):
  arr[i][0] = val[i]*(35-i)
  arr[i][1] = i
arr.sort()
ans = 0
for i in range(36-K):
  ans += val[arr[i][1]]*arr[i][1]
for i in range(36-K, 36):
  ans += val[arr[i][1]]*35
print(to36(ans))
