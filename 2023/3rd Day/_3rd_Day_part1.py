

def loadInput(inputName):
    input = open(inputName, 'r')
    
    resultMap = []

    for line in (input):
        row = []
        for char in line:
            if (char != '\n'):
                row.append(char)

        resultMap.append(row)


    return resultMap

def checkRectArea(engineMap, coords):
    rectCoords = []
    
    #create the list of coords to check
    for i in range(len(coords)+2):
        rectCoords.append([coords[0][0] - 1 + i ,coords[0][1] - 1])


    for i in range(len(coords)+2):
        rectCoords.append([coords[0][0] - 1 + i ,coords[0][1] + 1])

    rectCoords.append([coords[0][0] - 1, coords[0][1]])
    rectCoords.append([coords[-1][0] + 1, coords[-1][1]])

    #check&remove negative and outofrange coords 

    checkCoords = []
    for coord in rectCoords:
        if coord[0] >= 0 and coord[1] >= 0:
            if coord[0] < len(engineMap[0]) and coord[1] < len(engineMap):
                checkCoords.append(coord)


    #read coords and check for symbols

    for coord in checkCoords:
        checkChar = engineMap[coord[1]][coord[0]] #first is Y then X

        if checkChar != '.' and checkChar.isnumeric() == False:
            return True
    return False



engineMap = loadInput("trueInput.txt")
enginePartSum = 0


numberCoords = []
numberString = ""


for y, line in enumerate(engineMap):
    for x, char in enumerate(line):
        if char.isnumeric():
            numberString = numberString + char
            numberCoords.append([x,y]) 
        elif numberString != "":
            if checkRectArea(engineMap, numberCoords):
                enginePartSum += int(numberString)
            else:
                print(numberString)

            
            numberCoords.clear()
            numberString = ""


print(enginePartSum)