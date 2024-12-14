import numpy as np
import sys

def read_input(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    grid_array = np.empty((len(lines), len(lines[0].strip())), dtype=object)
    for x, line in enumerate(lines):
        for y, char in enumerate(line.strip()):
            is_antena = char != '.'
            cell = Cell(is_antena, char, (x, y))
            grid_array[x, y] = cell
    grid = Grid(grid_array)
    return grid

class Grid:
    def __init__(self, grid_array):
        self.grid_array = grid_array

    def get_cell(self, x, y):
        return self.grid_array[x, y]

    def set_cell(self, x, y, value):
        self.grid_array[x, y] = value

    def __str__(self):
        grid_str = ""
        for row in self.grid_array:
            for cell in row:
                if cell.is_antena:
                    grid_str += cell.cell_id
                elif cell.is_antinode:
                    grid_str += '#'
                else:
                    grid_str += cell.cell_id

            grid_str += "\n"
        return grid_str.strip()

class Cell:
    def __init__(self, is_antena, cell_id, coordinates):
        self.is_antena = is_antena
        if is_antena:
            self.is_antinode = True
        else:
            self.is_antinode = False
        self.cell_id = cell_id
        self.coordinates = coordinates
        self.links = []

    def add_link(self, other_cell):
        if other_cell.cell_id == self.cell_id:
            self.links.append(other_cell)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python part1.py <input_file>")
        sys.exit(1)

    file_path = sys.argv[1]
    grid = read_input(file_path)
    print(grid)
    print("######")

    antenas = [cell for row in grid.grid_array for cell in row if cell.is_antena]

    for antena in antenas:
        for other_antena in antenas:
            if antena != other_antena and antena.cell_id == other_antena.cell_id:
                vector = (other_antena.coordinates[0] - antena.coordinates[0], other_antena.coordinates[1] - antena.coordinates[1])
                antinode_x = antena.coordinates[0] - vector[0]
                antinode_y = antena.coordinates[1] - vector[1]

                while 0 <= antinode_x < grid.grid_array.shape[0] and 0 <= antinode_y < grid.grid_array.shape[1]:
                    antinode_cell = grid.get_cell(antinode_x, antinode_y)
                    antinode_cell.is_antinode = True
                    antinode_x -= vector[0]
                    antinode_y -= vector[1]

    for row in grid.grid_array:
        for cell in row:
            if cell.is_antinode:
                cell.cell_id = 'A'

    print(grid)

    antinode_count = sum(cell.is_antinode for row in grid.grid_array for cell in row)
    print(f"Number of antinodes: {antinode_count}")

