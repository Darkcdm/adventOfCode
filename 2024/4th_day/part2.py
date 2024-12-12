import sys

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")

# Remove any empty lines from the input
input = [line for line in input if line.strip()]

sum = 0

"""
M . M   
. A .         
S . S        

M . S
. A .
M . S

S . S
. A .
M . M

S . M
. A .
S . M
"""

# Create a copy of the input for debugging
debug_input = [list(line) for line in input]

for y in range(1, len(input)-1):
    for x in range(1 , len(input[y])-1):
        if input[y][x] == "A":
            if input[y-1][x-1] == "M" and input[y-1][x+1] == "M" and input[y+1][x-1] == "S" and input[y+1][x+1] == "S":
                sum += 1
                debug_input[y][x] = 'a'
                debug_input[y-1][x-1] = 'm'
                debug_input[y-1][x+1] = 'm'
                debug_input[y+1][x-1] = 's'
                debug_input[y+1][x+1] = 's'

            elif input[y-1][x-1] == "M" and input[y-1][x+1] == "S" and input[y+1][x-1] == "M" and input[y+1][x+1] == "S":
                sum += 1
                debug_input[y][x] = 'a'
                debug_input[y-1][x-1] = 'm'
                debug_input[y-1][x+1] = 's'
                debug_input[y+1][x-1] = 'm'
                debug_input[y+1][x+1] = 's'

            elif input[y-1][x-1] == "S" and input[y-1][x+1] == "S" and input[y+1][x-1] == "M" and input[y+1][x+1] == "M":
                sum += 1
                debug_input[y][x] = 'a'
                debug_input[y-1][x-1] = 's'
                debug_input[y-1][x+1] = 's'
                debug_input[y+1][x-1] = 'm'
                debug_input[y+1][x+1] = 'm'

            elif input[y-1][x-1] == "S" and input[y-1][x+1] == "M" and input[y+1][x-1] == "S" and input[y+1][x+1] == "M":
                sum += 1
                debug_input[y][x] = 'a'
                debug_input[y-1][x-1] = 's'
                debug_input[y-1][x+1] = 'm'
                debug_input[y+1][x-1] = 's'
                debug_input[y+1][x+1] = 'm'

# Print the debug input
for line in debug_input:
    print("".join(line))

# Evaluate the expression step-by-step
expression = "11 + 6 * 16 + 20"
parts = expression.split()
result = int(parts[0])
for i in range(1, len(parts), 2):
    operator = parts[i]
    value = int(parts[i + 1])
    if operator == '+':
        result += value
    elif operator == '*':
        result *= value

print(result)  # Should print 292

print(sum)