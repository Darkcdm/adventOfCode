import re

example_string = "xmul(200,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"

example_string = "do()" + example_string + "don't()"

# Define the regex pattern
pattern = r"do\(\).*?mul\((\d{1,3}),(\d{1,3})\).*?don't\(\)"

# Find all matches
matches = re.findall(pattern, example_string)

# Print the matches
print(matches)