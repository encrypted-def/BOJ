def numkind(N):
  if type(N) == int:
    N = str(N)
  return len(set(list(N)))

def numList(N):
  if type(N) == int:
    N = str(N)
  tmpL = [0]*10
  for c in N:
    tmpL[ord(c)-ord('0')] = 1
  unused = []
  used = []
  for i in range(10):
    if tmpL[i] == 0: unused.append(i)
    else: used.append(i)
  return unused,used

def concat(L):
  s = ''
  for c in L:
    s += str(c)
  return s
def solve(N,K): 
  N = str(N)
  if numkind(N) == K:
    print(N)
    return 0
  for prefix_i in range(len(N)-1, -1,-1):
    for prefix_last in range(ord(N[prefix_i])-48+1,10):
      prefix = N[:prefix_i]+chr(prefix_last+48)
      leftnum = K-numkind(prefix) # 추가되어야 하는 종류의 갯수
      leftlen = len(N)-prefix_i-1 # leftlen만큼의 길이가 추가되어야 함
      if leftnum < 0 or leftnum > leftlen: continue # 잘 조정해도 절대 수의 종류를 K개로 만들 수 없다면
      unused,used = numList(prefix)
      if leftnum == 0:
        print(prefix+str(used[0])*leftlen)
        return 0
      print(prefix+'0'*(leftlen-leftnum)+concat(unused[:leftnum]))
      return 0
  # 여기에 도달했다는 것은 N자리로는 절대 완성이 불가능해서 N+1자리가 필요한 상황
  N = max(K,len(N)+1)
  print("1"+"0"*(N-K+1)+"23456789"[:K-2])

N,K=map(int,input().split())
solve(N,K)
