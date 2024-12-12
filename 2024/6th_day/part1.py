import sys

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")


class PatrolArea:
    class Cell:
        char = None
        visited = False
        obstacle = False

        def __init__(self, char):
            self.char = char

            if char == "#":
                self.obstacle = True

    class Guard:
        x = 0
        y = 0

    def __init__(self, input):
        self.map = []
        self.guard = ()

        for y, line in enumerate(input):
            row = []
            for x, char in enumerate(line):
                row.append(self.Cell(char))
                if char == "^":
                    self.guard = self.Guard()
                    self.guard.x = x
                    self.guard.y = y
            
            self.map.append(row)


patrolArea = PatrolArea(input)



movement_vector = [0,-1]

while 0 <= patrolArea.guard.x < len(patrolArea.map[0]) and 0 <= patrolArea.guard.y < len(patrolArea.map):
    patrolArea.map[patrolArea.guard.y][patrolArea.guard.x].visited = True

    next_x = patrolArea.guard.x + movement_vector[0]
    next_y = patrolArea.guard.y + movement_vector[1]

    if not (0 <= next_x < len(patrolArea.map[0]) and 0 <= next_y < len(patrolArea.map)):
        patrolArea.guard.x += movement_vector[0]
        patrolArea.guard.y += movement_vector[1]
        continue

    if patrolArea.map[next_y][next_x].obstacle:
        movement_vector = [-movement_vector[1], movement_vector[0]]
        continue

    patrolArea.guard.x = next_x
    patrolArea.guard.y = next_y


print(sum([1 for row in patrolArea.map for cell in row if cell.visited]))

for y in range(len(patrolArea.map)):
    for x in range(len(patrolArea.map[y])):
        if patrolArea.map[y][x].visited:
            print("X", end="")
        else:
            print(patrolArea.map[y][x].char, end="")
    print()