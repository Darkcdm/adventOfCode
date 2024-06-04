
inputValues = []

with open("input", "r") as file:
    for line in file:
        inputValues.append(int(line.strip()))


oldTripletSum = float("inf")
result = 0


for index in range(len(inputValues)):


    if index + 2 >= len(inputValues):
        break

    newTripletSum = inputValues[index] + inputValues[index + 1] + inputValues[index + 2]

    if newTripletSum > oldTripletSum:
        result += 1
    
    oldTripletSum = newTripletSum


print(result)

