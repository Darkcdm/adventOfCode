
class Coord:
    def __init__(self, x, y):
     self.x = x
     self.y = y

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


def getNumber(x, y, engineMap):
    #find start
    line = engineMap[y]


    i = 0
    while x - i >= 0 and line[x-i].isnumeric():
        i += 1
    
    xStart = x - i + 1
    number = ""
    i = 0
    
    #go until the end and record it
    while xStart+i < len(line) and line[xStart+i].isnumeric():
        number += line[xStart+i]
        i += 1


    return int(number)



def getSearchCoords(x, y, xLimit, yLimit):
    coords = []
    for i in range(3): 
        coords.append(Coord(x - 1 + i, y - 1))

    for i in range(3):
        coords.append(Coord(x - 1 + i, y + 1))
    
    coords.append(Coord(x - 1, y))   
    coords.append(Coord(x + 1, y))
    
    filteredCoords = []
    for coord in coords:
        if coord.x >= 0 and coord.y >= 0:
            if coord.x < xLimit and coord.y < yLimit:
                filteredCoords.append(coord)
        
    return filteredCoords



def scan(coords, engineMap):

    numberCoords = []
    
    for coord in coords:
        if engineMap[coord.y][coord.x].isnumeric():
            numberCoords.append(coord)



    numbers = []
    for coord in numberCoords:
        numbers.append(getNumber(coord.x, coord.y, engineMap))


    return list(set(numbers))







engineMap = loadInput("trueInput.txt")
gearRatioSum = 0


numberCoords = []
numberString = ""

for y, line in enumerate(engineMap):
    for x, char in enumerate(line):
        if char == '*':
            numbers = scan(getSearchCoords(x ,y ,len(engineMap), len(engineMap[0])), engineMap)
            if len(numbers) == 2:
                gearRatioSum += numbers[0]*numbers[1]
             

print(gearRatioSum)

