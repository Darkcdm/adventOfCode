import sys




input_file = sys.argv[1]
input = open(input_file, "r")

input = input.read().split()


leftList = []
rightList = []

for i in range(0, len(input), 2):
    leftList.append(input[i])
    if i + 1 < len(input):
        rightList.append(input[i + 1])

leftList.sort()
rightList.sort()

print(leftList, rightList)

countLeftDict = {}
countRightDict = {}

for i in range(len(leftList)):
    countLeftDict[leftList[i]] = countLeftDict.get(leftList[i], 0) + 1
    countRightDict[rightList[i]] = countRightDict.get(rightList[i], 0) + 1

print(countLeftDict, countRightDict)


similarScore = 0
for value in leftList:
    similarScore += int(value) * int(countRightDict.get(value, 0))
    

print(similarScore)