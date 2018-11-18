n = int(input())
num = 0
tn = n
while tn:
  num += tn//5
  tn //= 5

ret = 1
for i in range(1,n+1):
  ti = i
  while ti % 5 == 0:
    ti //= 5
  if num and ti % 2 == 0:
    num -= 1
    ti //= 2
  ret = (ret*ti)%10
print(ret)
