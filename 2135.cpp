s = input()
n = len(s)
d = [[0]*(n+1) for i in range(n+1)]

for i in range(n):
  d[i][i+1] = 1

for sz in range(2,n+1):
  divs = []
  for i in range(1,sz):
    if sz%i == 0: divs.append(i)
  for st in range(n-sz+1):
    val = sz
    for div in divs:
      if all(s[st:st+div] == s[k:k+div] for k in range(st, st+sz, div)):
        val = min(val, 2 + d[st][st+div] + len(str((sz//div))))
      
    
    for sep in range(st+1, st+sz):
      val = min(val, d[st][sep] + d[sep][st+sz])

    d[st][st+sz] = val

st,div,sz=4,2,6

print(d[0][n])

