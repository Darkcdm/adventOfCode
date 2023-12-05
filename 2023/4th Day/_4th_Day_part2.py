

class Card:
    def __init__(self, lotNumbers, winNumbers):
        self.lotNumbers = lotNumbers
        self.winNumbers = winNumbers
        self.count = 1
        self.checked = 0

input = open("true.txt", "r")


cardList = []



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

    cardList.append(Card(lotNumbers, winNumbers))


index = 0

while(index < len(cardList)):

    card = cardList[index]


    print(f"Index: {index}|Count:{card.count}|Checked:{card.checked}")



    winCount = 0

    for lot in card.lotNumbers:
        for win in card.winNumbers:
            if lot == win:
                winCount += 1


    for i in range(1 ,winCount + 1):
        cardList[index+i].count += card.count

    

    index+=1

    
    
    
result = 0
for card in cardList:
    result += card.count

print(result)

   