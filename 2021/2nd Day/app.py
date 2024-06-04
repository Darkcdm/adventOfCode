depth = 0
position = 0

with open("input", "r") as file:
    for line in file:

        word = line.split()        
    
        if word[0] == "forward":
            position += int(word[1])
            continue

        if word[0] == "down":
            depth += int(word[1])
            continue

        if word[0] == "up":
            depth -= int(word[1])
            continue


print(position, depth)
print(position * depth)