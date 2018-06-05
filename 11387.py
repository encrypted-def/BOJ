def power(h,w):
  return (h[0]+w[0]) * (100+h[1]+w[1]) * ( 100*(100-min(h[2]+w[2],100)) + min(h[2]+w[2],100) * (h[3]+w[3])) * (100+h[4]+w[4])
h1=list(map(int, input().split()))
h2=list(map(int, input().split()))
w1=list(map(int, input().split()))
w2=list(map(int, input().split()))
for i in range(5):
  h1[i] -= w1[i]
  h2[i] -= w2[i]

diff1 = power(h1,w2) - power(h1,w1)
diff2 = power(h2,w1) - power(h2,w2)

if diff1 > 0: print('+')
elif diff1 == 0: print('0')
else: print('-')

if diff2 > 0: print('+')
elif diff2 == 0: print('0')
else: print('-')

