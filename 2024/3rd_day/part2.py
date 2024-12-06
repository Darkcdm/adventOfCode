import sys
import re

input_file = sys.argv[1]

with open(input_file, "r") as f:
    content = f.read()

    pattern = r"mul\(\d+,\d+\)|do\(\)|don\'t\(\)"
    numbers = r"\d+,\d+"

    muls = re.findall(pattern, content)

    muls = ["y" if i == "don't()" else i for i in muls]
    muls = ["x" if i == "do()" else i for i in muls]

    digitList = [re.findall(numbers,i) if i.__contains__("mul") else i for i in muls]

    listOfMultiplyedValues = []

    enabled = True

    for entry in digitList:

        if entry == "x":
            enabled = True
            continue

        if entry == "y":
            enabled = False
            continue

        if not enabled:
            continue

        singleDigitList = entry[0].split(",")
        multiplyedValue = int(singleDigitList[0]) * int(singleDigitList[1])
        listOfMultiplyedValues.append(multiplyedValue)
    
    print("Sum of all Mul's in file:",sum(listOfMultiplyedValues))