
import re

input = open("trueInput.txt", "r")

powerSum = 0

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

        if showType == ';':
            if redCount > redMax:
                redMax = redCount

            if greenCount > greenMax:
                greenMax = greenCount

            if blueCount > blueMax:
                blueMax = blueCount


            redCount = 0
            greenCount = 0
            blueCount = 0

    
    CubePower = redMax * greenMax * blueMax
    powerSum += CubePower
    print(f"{index + 1}:{redMax},{greenMax},{blueMax}={CubePower}::{powerSum}")
    


    

        


print(f"Result is: {powerSum}")

    
    