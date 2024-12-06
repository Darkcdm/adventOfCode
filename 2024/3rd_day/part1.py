import sys
import re

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")

mul_patterns = []

for line in input:
    matches = re.findall(r'mul\(\d{1,3},\d{1,3}\)', line)
    mul_patterns.extend(matches)



result = 0

for mul in mul_patterns:
    a, b = map(int, re.findall(r'\d{1,3}', mul))
    result += a * b

print(result)