def solve():
  T = input()
  if T.find('__') != -1:
    print("Error!")
    return None
  if T[-1] == '_' or T[0] == '_':
    print("Error!")
    return None
  if T.find('_') != -1:
    if T != T.lower():
      print("Error!")
      return None
    S = T.split('_')
    print(S[0],end='')
    for w in S[1:]:
      print(w[0].upper()+w[1:],end='')
  else:
    if T[0] != T[0].lower():
      print("Error!")
      return None
    for c in T:
      if c == c.lower():
        print(c,end='')
      else:
        print('_'+c.lower(),end='')
solve()
