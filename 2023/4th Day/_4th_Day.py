

input = open("true.txt", "r")

winSum = 0

for line in input:
    words = line.split()
    words = words[2:]

    lotNumbers = []
    winNumbers = []

    pickingWinNumbers  = False
    for word in words:
        if word == "|":
            pickingWinNumbers = True
            continue
        
        if pickingWinNumbers:
            lotNumbers.append(int(word))
        else:
            winNumbers.append(int(word))

    
    winCount = 0
    for lot in lotNumbers:

        for win in winNumbers:
            if lot == win:
                winCount += 1

    score = 0
    if winCount > 0:
        score = 1

        for i in range(winCount-1):
            score = score + score

    winSum += score


print (winSum)


   