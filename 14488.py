def left_reach(x, v):
  return x-v*T
def right_reach(x,v):
  return x+v*T
def main():
  bound = [0,0] # 학생이 T초간 도달할 수 있는 범위
  bound[0] = left_reach(x[0],v[0])
  bound[1] = right_reach(x[0],v[0])
  for i in range(1,N):
    left = left_reach(x[i],v[i])
    right = right_reach(x[i],v[i])
    if bound[1] < left or bound[0] > right:
      print("0")
      return None
    if bound[0] <= left:
      bound[0] = left
    if bound[1] >= right:
      bound[1] = right
  print("1")

S = input()
N = int(S.split()[0])
T = 0
if S.find('.') == -1:
  T = int(S.split()[1])
else:
  T = int(S.split()[1].split('.')[0]+S.split()[1].split('.')[1].ljust(4, '0'))
x = list(map(int, input().split())) 
v = list(map(int, input().split()))
x = list(map(lambda a : a*10000, x))
main()
