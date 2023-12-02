
import re

input = open("trueInput.txt", "r")

RED_LIMIT = 12
GREEN_LIMIT = 13
BLUE_LIMIT = 14

indexSum = 0

for index,line in enumerate(input):
    words = line.split()
    words = words[2:]
    words[-1] = words[-1] + ';'



    redMax = 0
    greenMax = 0
    blueMax = 0

    redCount = 0 
    greenCount = 0 
    blueCount = 0


    for i in range(0, len(words), 2):
        #load the colour and the count && remove the last char in colour
        count = int(words[i])
        colour = words[i + 1] if i + 1 < len(words) else None
        showType = colour[-1]
        colour = colour[:-1]


        if colour == "red":
            redCount+= count
        
        if colour == "green":
            greenCount+= count

        if colour == "blue":
            blueCount+= count

        if showType == ';' or showType == '\n':
            if redCount > redMax:
                redMax = redCount

            if greenCount > greenMax:
                greenMax = greenCount

            if blueCount > blueMax:
                blueMax = blueCount


            redCount = 0
            greenCount = 0
            blueCount = 0




    
    if redMax > RED_LIMIT or greenMax > GREEN_LIMIT or blueMax > BLUE_LIMIT:
        print(f"{line}:NOT")
    else:
        indexSum += index + 1
        print(f"{line}:COUNT")
        


print(f"Result is: {indexSum}")

    
    