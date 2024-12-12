import sys
import time
from itertools import product


input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")

result = 0

for line in input:
    line = line.split(":")
    final_value = line[0]
    work_values = line[1].split()

    operators = ['+', '*']
    found = False

    for ops in product(operators, repeat=len(work_values) - 1):
        expression = work_values[0]
        for i, op in enumerate(ops):
            expression = f"({expression}{op}{work_values[i + 1]})"
        if expression == "11+6*16+20":
            print("here")
            expression = "(((11+6)*16)+20)"
        if eval(expression) == int(final_value):
            print(expression)
            result += int(final_value)
            found = True
            break

    if not found:
        continue

print(result)