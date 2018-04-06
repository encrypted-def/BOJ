N = 10**7+5
sieve = [True]*(N+100)
sieve[0] = False
sieve[1] = False
sieve[2] = True
prime = 2
while prime*prime <= N:
  if not sieve[prime]:
    prime += 1
    continue
  for t in range(2*prime, N+3, prime): sieve[t] = False
  prime += 1

	
A,B=map(int, input().split())
cnt = 0
for p in range(2,N):
  if not sieve[p]: continue
  mul = p*p
  while mul <= B:
    cnt += (A <= mul)
    mul *= p
print(cnt)
