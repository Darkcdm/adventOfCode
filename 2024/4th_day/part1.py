import sys

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")

keyword = "XMAS"

sum = 0


for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y + i >= len(input) or input[y + i][x] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if x + i >= len(input[y]) or input[y][x + i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y - i < 0 or input[y - i][x] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if x - i < 0 or input[y][x - i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1



for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y + i >= len(input) or x + i >= len(input[y]) or input[y + i][x + i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y - i < 0 or x + i >= len(input[y]) or input[y - i][x + i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y + i >= len(input) or x - i < 0 or input[y + i][x - i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

for y in range(len(input)):
    for x in range(len(input[y])):
            for i, key in enumerate(keyword):
                if y - i < 0 or x - i < 0 or input[y - i][x - i] != key:
                    break
                if i == len(keyword) - 1:
                    sum += 1

print(sum)