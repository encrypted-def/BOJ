import sys
N = int(sys.stdin.readline())
for i in range(N):
    url = sys.stdin.readline()[:-1]
    sys.stdout.write("URL #{}\n".format(i+1))
    sys.stdout.write("Protocol = " + url.split("://")[0] + "\n")
    url = url[url.find("://")+3:]
    SlashIdx = -1
    ColonIdx = -1
    for i in range(len(url)):
        if url[i] == ":":
            if ColonIdx == -1: ColonIdx = i
        if url[i] == "/":
            if SlashIdx == -1: SlashIdx = i
    if ColonIdx == -1 and SlashIdx == -1:
        sys.stdout.write("Host     = " + url + "\n")
        sys.stdout.write("Port     = <default>\nPath     = <default>\n")
    elif ColonIdx == -1 or (SlashIdx > -1 and SlashIdx < ColonIdx):
        sys.stdout.write("Host     = " + url[:SlashIdx] + "\n")
        sys.stdout.write("Port     = <default>\n")
        sys.stdout.write("Path     = " + url[SlashIdx+1:] + "\n")
    elif SlashIdx == -1:
        sys.stdout.write("Host     = " + url[:ColonIdx] + "\n")
        sys.stdout.write("Port     = " + url[ColonIdx+1:] + "\n")
        sys.stdout.write("Path     = <default>\n")
    else:
        sys.stdout.write("Host     = " + url[:ColonIdx] + "\n")
        sys.stdout.write("Port     = " + url[ColonIdx+1:SlashIdx] + "\n")
        sys.stdout.write("Path     = " + url[SlashIdx+1:] + "\n")
    sys.stdout.write("\n")
