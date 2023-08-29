using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _17th_Day {
    public class Cave {

        private int width;
        private int height;
        private int rockCount;
        public List<List<Cell>> grid;

        public Cave () {
            this.width = 7;
            this.height = 4;

            grid = new List<List<Cell>>();

            for (int y = 0; y < height; y++) {
                List<Cell> line = new List<Cell>();
                for (int x = 0; x < width; x++) {
                    Cell cell = new Cell(x, y);
                    line.Add(cell);
                }
                grid.Add(line);
            }

        }

        public void addHeight (int height) {

            height += this.height;
            while (this.height < height) {
                List<Cell> line = new List<Cell>();
                for (int x = 0; x < width; x++) {
                    Cell cell = new Cell(x, this.height + 1);

                    line.Add(cell);
                }
                grid.Add(line);
                this.height++;
            }

        }
        public void printCave (){
            for (int y = 0; y < height; y++) {
                Console.Write('|');
                for (int x = 0; x < width; x++) {
                    grid[y][x].printCell();
                }
                Console.Write("|\n");
            }
            Console.Write('+');
            for (int x = 0; x < width; x++) {
                Console.Write('-');
            }
            Console.Write("+\n");
        }
        public int simulateRockHeightLimit(int rockMax, bool printout) {
            int result = 0;
            Rocks rocks = new Rocks();
            while (rockCount < rockMax) {
                Rock rock = rocks.getGrain(); //TESTING 

            }

            return result;
        }

        private int getHighestPoint() {
            for (int y = height-1; y >= 0; y--) {
                for (int x = 0; x < width; x++) {
                    if (grid[y][x].Solid) {
                        return y;
                    }
                }
            }
            return 0;
        }
    }

    public class Cell {
        int X;
        int Y;
        private bool occupied;
        private bool solid;


        public bool Occupied {

            set { occupied = value; }
            get { return occupied; }
            
        }
        public bool Solid{

            set { solid = value; }
            get { return solid; }
        
        }

        public Cell(int X, int Y) {
            this.X = X;
            this.Y = Y;
            this.occupied = false;
            this.solid = false;
        }

        public void printCell() {
            if (occupied) {
                if (solid) {
                    Console.Write('#');
                    return;
                }
                Console.Write('@');
                return;
            }
            Console.Write('.');
        }

    }
}
