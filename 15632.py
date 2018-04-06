x0,y0,r0=map(int,input().split())
x1,y1,r1=map(int,input().split())
x2,y2,r2=map(int,input().split())
N = 230
area = 0
for i in range(1,100*N+1):
  for j in range(1,100*N+1):
    if (i/N-x0-0.5/N)**2+(j/N-y0-0.5/N)**2 <= r0*r0: area += 1
    elif (i/N-x1-0.5/N)**2+(j/N-y1-0.5/N)**2 <= r1*r1: area += 1
    elif (i/N-x2-0.5/N)**2+(j/N-y2-0.5/N)**2 <= r2*r2: area += 1
    
print(area/N/N)
