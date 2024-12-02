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


sum = 0

for i in range(len(leftList)):
    sum = sum + abs(int(leftList[i]) - int(rightList[i]))

print(sum)