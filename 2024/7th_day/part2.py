import sys
from itertools import product

def concat(a, b):
    return str(a) + str(b)

def evaluate_expression(ops, values):
    result = values[0]
    for i, op in enumerate(ops):
        if op == '||':
            result = int(concat(result, values[i + 1]))
        elif op == '+':
            result = int(result) + int(values[i + 1])
        elif op == '*':
            result = int(result) * int(values[i + 1])
    return int(result)

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")

result = 0

for line in input:
    line = line.split(":")
    final_value = int(line[0])
    work_values = line[1].split()

    operators = ['||','+', '*']
    found = False

    for ops in product(operators, repeat=len(work_values) - 1):
        evaluated_result = evaluate_expression(ops, work_values)
        if evaluated_result == final_value:
            expression = work_values[0]
            for i, op in enumerate(ops):
                expression = f"{expression}{op}{work_values[i + 1]}"
            print(expression + ":" + str(final_value))
            result += final_value
            found = True
            break

    if not found:
        continue

print(result)