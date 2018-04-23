def c2i(c):
  if c == '?': return -1
  return ord(c)-ord('0');

def candidate(a_in,b_in,c_in,carryIn,carryOut):
  ret = []
  alist = []
  if a_in == -1: alist = [0,1,2,3,4,5,6,7,8,9]
  else: alist = [a_in]
  blist = []
  if b_in == -1: blist = [0,1,2,3,4,5,6,7,8,9]
  else: blist = [b_in]
  clist = []
  if c_in == -1: clist = [0,1,2,3,4,5,6,7,8,9]
  else: clist = [c_in]
  for a in alist:
    for b in blist:
      for c in clist:
        if a+b+carryIn-c == 10*carryOut:
          ret.append((a,b,c))
  return ret

def val_list(L):
  if not L: return -1
  return int("".join(map(str, L[::-1])))
def solve():
  S = input()
  #S = "?+?=?"
  Astr = S.split('+')[0][::-1]
  S = S.split('+')[1]
  Bstr = S.split('=')[0][::-1]
  Cstr = S.split('=')[1][::-1]
  len_op = max(len(Astr),len(Bstr))  
  notzeroA = len(Astr)-1
  notzeroB = len(Bstr)-1
  if notzeroA == 0: notzeroA = -1
  if notzeroB == 0: notzeroB = -1  
  Astr = Astr.ljust(len_op,'0')
  Bstr = Bstr.ljust(len_op,'0')
  AA = list(map(c2i, list(Astr)))
  BB = list(map(c2i, list(Bstr)))
  CC = list(map(c2i, list(Cstr)))  
  if len(CC) != len_op+1 and len(CC) != len_op:
    print("-1")
    return 0
  Ac,Bc,Cc,An,Bn,Cn = [],[],[],[],[],[]
  for digit in range(0, len_op):    
    An_before,Bn_before,Cn_before = An[:], Bn[:], Cn[:]
    Ac_before,Bc_before,Cc_before = Ac[:], Bc[:], Cc[:]
    # An, Bn, Cn
    An_mx,Bn_mx,Cn_mx = [],[],[]
    if len(An) == digit: # CarryIn = 0
      cand = candidate(AA[digit],BB[digit],CC[digit],0,0)
      for val in cand:
        if notzeroA == digit and val[0] == 0: continue
        if notzeroB == digit and val[1] == 0: continue
        An_tmp2,Bn_tmp2,Cn_tmp2 = An_before[:] + [val[0]],Bn_before[:] + [val[1]],Cn_before[:] + [val[2]]
        if val_list(Cn_tmp2) > val_list(Cn_mx):
          An_mx,Bn_mx,Cn_mx = An_tmp2[:], Bn_tmp2[:], Cn_tmp2[:]
        elif val_list(Cn_tmp2) == val_list(Cn_mx) and val_list(An_tmp2) > val_list(An_mx):
          An_mx,Bn_mx,Cn_mx = An_tmp2[:], Bn_tmp2[:], Cn_tmp2[:]
    
    if len(Ac) == digit and digit != 0: # CarryIn = 1
      cand = candidate(AA[digit],BB[digit],CC[digit],1,0)
      for val in cand:
        if notzeroA == digit and val[0] == 0: continue
        if notzeroB == digit and val[1] == 0: continue
        An_tmp2,Bn_tmp2,Cn_tmp2 = Ac_before[:] + [val[0]],Bc_before[:] + [val[1]],Cc_before[:] + [val[2]]
        if val_list(Cn_tmp2) > val_list(Cn_mx):
          An_mx,Bn_mx,Cn_mx = An_tmp2[:], Bn_tmp2[:], Cn_tmp2[:]
        elif val_list(Cn_tmp2) == val_list(Cn_mx) and val_list(An_tmp2) > val_list(An_mx):
          An_mx,Bn_mx,Cn_mx = An_tmp2[:], Bn_tmp2[:], Cn_tmp2[:]

    # Ac, Bc, Cc
    Ac_mx,Bc_mx,Cc_mx = [],[],[]
    if len(An) == digit: # CarryIn = 0
      cand = candidate(AA[digit],BB[digit],CC[digit],0,1)
      for val in cand:
        if notzeroA == digit and val[0] == 0: continue
        if notzeroB == digit and val[1] == 0: continue
        Ac_tmp2,Bc_tmp2,Cc_tmp2 = An_before[:] + [val[0]],Bn_before[:] + [val[1]],Cn_before[:] + [val[2]]
        if val_list(Cc_tmp2) > val_list(Cc_mx):
          Ac_mx,Bc_mx,Cc_mx = Ac_tmp2[:], Bc_tmp2[:], Cc_tmp2[:]
        elif val_list(Cc_tmp2) == val_list(Cc_mx) and val_list(Ac_tmp2) > val_list(Ac_mx):
          Ac_mx,Bc_mx,Cc_mx = Ac_tmp2[:], Bc_tmp2[:], Cc_tmp2[:]
    
    if len(Ac) == digit and digit != 0: # CarryIn = 1
      cand = candidate(AA[digit],BB[digit],CC[digit],1,1) # CarryIn = 1    
      for val in cand:
        if notzeroA == digit and val[0] == 0: continue
        if notzeroB == digit and val[1] == 0: continue
        Ac_tmp2,Bc_tmp2,Cc_tmp2 = Ac_before[:] + [val[0]],Bc_before[:] + [val[1]],Cc_before[:] + [val[2]]
        if val_list(Cc_tmp2) > val_list(Cc_mx):
          Ac_mx,Bc_mx,Cc_mx = Ac_tmp2[:], Bc_tmp2[:], Cc_tmp2[:]
        elif val_list(Cc_tmp2) == val_list(Cc_mx) and val_list(Ac_tmp2) > val_list(Ac_mx):
          Ac_mx,Bc_mx,Cc_mx = Ac_tmp2[:], Bc_tmp2[:], Cc_tmp2[:]

    Ac,Bc,Cc = Ac_mx[:],Bc_mx[:],Cc_mx[:]
    An,Bn,Cn = An_mx[:],Bn_mx[:],Cn_mx[:]
  if len(CC) == len_op+1:
    if CC[len_op] != -1 and CC[len_op] != 1:
      print(-1)
      return 0
    if len(Ac) != len_op:
      print(-1)
      return 0
    Cc += [1]
    print("{}+{}={}".format(val_list(Ac),val_list(Bc),val_list(Cc)))
    return 0
  # len(CC) == len_op
  if len(An) != len_op:
    print(-1)
    return 0
  print("{}+{}={}".format(val_list(An),val_list(Bn),val_list(Cn)))
  return 0

solve()
