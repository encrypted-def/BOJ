import sys
def isOutOfRange(position):
    if position[0] > ord('H') or position[0] < ord('A'): return True
    if position[1] > ord('8') or position[1] < ord('1'): return True
    return False

tmp1, tmp2, N = tuple(sys.stdin.readline().split())
N = int(N)
position1 = [ord(tmp1[0]), ord(tmp1[1])] # A 1
position2 = [ord(tmp2[0]), ord(tmp2[1])] # A 2
dir0 = [1,-1,0,0,1,-1,1,-1]
dir1 = [0,0,-1,1,1,1,-1,-1]
for _ in range(N):
    mv = sys.stdin.readline()[:-1]
    tmp_pos1 = [None]*2
    tmp_pos2 = [None]*2
    if mv == 'R': dir = 0
    elif mv == 'L': dir = 1
    elif mv == 'B': dir = 2
    elif mv == 'T': dir = 3
    elif mv == 'RT': dir = 4
    elif mv == 'LT': dir = 5
    elif mv == 'RB': dir = 6
    else: dir = 7
    tmp_pos1 = [position1[0]+dir0[dir], position1[1]+dir1[dir]]
    if tmp_pos1 == position2: # 기존의 돌의 위치로 킹이 가게 됐을 경우
        tmp_pos2 = [position2[0]+dir0[dir], position2[1]+dir1[dir]]
    else:
        tmp_pos2 = position2
    if isOutOfRange(tmp_pos1) or isOutOfRange(tmp_pos2): continue # 밀고보니 체스판 밖으로 밀려날 경우
    position1 = [tmp_pos1[0], tmp_pos1[1]]
    position2 = [tmp_pos2[0], tmp_pos2[1]]
sys.stdout.write(chr(position1[0])+chr(position1[1])+'\n'+chr(position2[0])+chr(position2[1]))
