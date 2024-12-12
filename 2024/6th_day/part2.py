import sys
import time


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
        masterX = 0
        masterY = 0
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
                    self.guard.masterX = x
                    self.guard.masterY = y
            
            self.map.append(row)

    def resetGuard(self):
        self.guard.x = self.guard.masterX
        self.guard.y = self.guard.masterY


patrolArea = PatrolArea(input)


result = 0

totalOptions = len(patrolArea.map) * len(patrolArea.map[0])

start = time.time()

for y in range(len(patrolArea.map)):
    for x in range(len(patrolArea.map[y])):
        
        simulations_left = totalOptions - (y * len(patrolArea.map[0]) + x + 1)
        percentage_left = (simulations_left / totalOptions) * 100
        if int(percentage_left) != int((simulations_left + 1) / totalOptions * 100):
            print(f"Simulations left: {percentage_left:.2f}%")

        # Check that it's in valid position
        if patrolArea.map[y][x].obstacle:
            continue

        if y == patrolArea.guard.y and x == patrolArea.guard.x:
            continue

        # Place a box
        patrolArea.map[y][x].obstacle = True

        # Calculate the max distance of the guard
        max_steps = 0
        for yy in range(len(patrolArea.map)):
            for xx in range(len(patrolArea.map[yy])):
                if patrolArea.map[yy][xx].obstacle:
                    continue

                if yy == patrolArea.guard.y and xx == patrolArea.guard.x:
                    continue
                
                max_steps += 1

        # Simulate until a counter of steps is reached or the guard is caught out of bounds
        movement_vector = [0, -1]
        simulation_steps = 0

        while 0 <= patrolArea.guard.x < len(patrolArea.map[0]) and 0 <= patrolArea.guard.y < len(patrolArea.map):
            if simulation_steps > max_steps * 2:
                result += 1
                break

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
            simulation_steps += 1

        patrolArea.map[y][x].obstacle = False
        patrolArea.resetGuard()



print(f"Execution time: {time.time() - start}")
print(result)