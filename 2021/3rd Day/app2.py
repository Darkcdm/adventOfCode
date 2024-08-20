

def getCommonBits(input:list):
    commonBits = []

    for line in input:
        line = line.strip()
        if commonBits == []:
            commonBits = [0] * len(line)

        for index, bit in enumerate(line):
            if bit == "0":
                commonBits[index] -= 1
            else:
                commonBits[index] += 1


    commonBitsString = ""
    inverseCommonBitsString = ""
    print(commonBits)
    for index, bit in enumerate(commonBits):

        if bit > 0:
            commonBitsString += "1"
            inverseCommonBitsString += "0"
        elif bit < 0:
            commonBitsString += "0"
            inverseCommonBitsString += "1"
        else:
            commonBitsString += "1"
            inverseCommonBitsString += "0"

    return commonBitsString, inverseCommonBitsString


oxygenList = []
carbonList = []

input = []

with open("input", "r") as file:
    for line in file:
        line = line.strip()
        input.append(line)


commonBitsString, inverseCommonBitsString = getCommonBits(input)
oxygenList = input.copy()
carbonList = input.copy()




while len(oxygenList) > 1:
    commonBitsString, inverseCommonBitsString = getCommonBits(oxygenList)


    for index, bit in enumerate(commonBitsString):
        messyList = []
        for value in oxygenList:
            if value[index] == bit:
                messyList.append(value)
        

        #if len(messyList) < 1:
            #break

        oxygenList = messyList

    print(oxygenList)
    print(commonBitsString)
    

while len(carbonList) > 1:

    for index, bit in enumerate(inverseCommonBitsString[1:], start=1):
        
        messyList = []
        for value in carbonList:
            if value[index] == bit:
                messyList.append(value)
        

        if len(messyList) < 1:
            break

        carbonList = messyList

    commonBitsString, inverseCommonBitsString = getCommonBits(carbonList)
    

#print(oxygenList)
#print(carbonList)
#print(int(oxygenList[0], 2) * int(carbonList[0], 2))