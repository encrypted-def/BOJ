N = int(input())
D = [0]*40 # 좌우 대칭과 무관하게 채우는 갯수
symmetric = [0]*40 # 좌우 대칭인 형태의 갯수
D[1] = 1
D[2] = 3
symmetric[1] = 1
symmetric[2] = 3
symmetric[3] = 1
symmetric[4] = 5
for i in range(3,N+1):
  D[i] = 2*D[i-2]+D[i-1]
for i in range(5,N+1):
  symmetric[i] = symmetric[i-2]+2*symmetric[i-4] 
print((D[N]-symmetric[N])//2 + symmetric[N])
