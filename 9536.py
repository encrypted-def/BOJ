T = int(input())
for _ in range(T):
    FoxSound = input().split()
    AnimalSound = []
    while True:
        S = input()
        if S[:5] == "what ": break
        AnimalSound.append(S.split()[2])
    for word in FoxSound:
        if word in AnimalSound:
            continue
        print(word, end = ' ')
    print()
