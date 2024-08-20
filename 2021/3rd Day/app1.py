
commonBits = []

with open("input", "r") as file:
    for line in file:
        if commonBits == []:
            commonBits = [0] * len(line)

        for index, bit in enumerate(line):
            if bit == "0":
                commonBits[index] -= 1
            else:
                commonBits[index] += 1


commonBitsString = ""
inverseCommonBitsString = ""
for index, bit in enumerate(commonBits):
    if index == len(commonBits) - 1:
        break

    if bit > 0:
        commonBitsString += "1"
        inverseCommonBitsString += "0"
    else:
        commonBitsString += "0"
        inverseCommonBitsString += "1"

print(int(commonBitsString, 2) * int(inverseCommonBitsString, 2))



