def gcd(a,b):
  if a == 0: return b
  return gcd(b%a,a)

def PrimeFactorization(N):
  f = {}
  factor = 2
  while factor*factor <= N:
    while N % factor == 0:
      if factor in f:  f[factor] += 1
      else: f[factor] = 1
      N //= factor
    factor += 1
  if N > 1:
    f[N] = 1
  return f

def lcm(f1, f2):
  f = {}
  for factor in f1:
    if factor in f2:
      f[factor] = max(f1[factor],f2[factor])
    else:
      f[factor] = f1[factor]
  for factor in f2:
    if not factor in f1:
      f[factor] = f2[factor]
  return f

S = input()
D = list(map(int, input().split()))
M = list(map(int, input().split()))
gcdM = M[0]
lcmD = PrimeFactorization(D[0])
for m in M:
  gcdM = gcd(gcdM, m)

for d in D:
  lcmD = lcm(lcmD, PrimeFactorization(d))
gcdM = PrimeFactorization(gcdM)
val = 1
for factor in lcmD:
  if not factor in gcdM:
    val = 0
  else:
    gcdM[factor] -= lcmD[factor]
    if gcdM[factor] < 0:
      val = 0
if val == 0:
  print("0")
else:
  for factor in gcdM:
    val *= (gcdM[factor]+1)
  print(val)
