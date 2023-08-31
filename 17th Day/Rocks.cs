using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.ExceptionServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace _17th_Day {



    public class Rocks {
        
        private int rockIndex = 0;
        private int RockIndex {
            
            get { return rockIndex; }
            set{
                if (rockIndex == 4) {
                    rockIndex = 0;
                } else {
                    rockIndex++;
                }
            }
        }


        public Rock getRock(List<List<Cell>> grid, int y) {
            switch (rockIndex) {
                case 0:
                    return new Line();
                case 1:
                    return new Cross();
                case 2:
                    return new LType();
                case 3:
                    return new Collum();
                case 4:
                    return new square();
            }

            return new Grain(grid, y);
        }

        public Rock getGrain(List<List<Cell>> grid, int y) {
            return new Grain(grid, y);
        }
    
    }

    public class Rock {
        /*
        The tall, vertical chamber is exactly seven units wide. 
        Each rock appears so that its left edge is two units away from the left wall and its bottom edge is three units above the highest rock in the room (or the floor, if there isn't one).
         */
        public List <Cell> cells = new List <Cell> ();
        bool stationary = false;

        public bool Stationary {
            get { return stationary; }
            set { stationary = value; }
        }

        public int moveSide(List<List<Cell>> grid, char direction) {

            int dirValue;
            if (direction == '<') {
                dirValue = -1;
            } else {
                dirValue = 1;
            }


            List<Cell> newCells = new List<Cell>();

            while (cells.Count > 0 && !stationary) {
                Cell selectedCell = cells[0];
                cells.RemoveAt(0);

                if (selectedCell.X == 0 || selectedCell.X == grid[0].Count - 1) {
                    newCells.Add(selectedCell);
                    continue;

                } else {
                    selectedCell.Occupied = false;

                    Cell newCell = grid[selectedCell.Y][selectedCell.X + dirValue];

                    newCell.Occupied = true;

                    newCells.Add(newCell);

                }

            }
            cells = newCells;

            return 0;
        }

        public int moveDown(List<List<Cell>> grid) {
            List <Cell> newCells = new List <Cell> ();

            
            while (cells.Count > 0 && !stationary) {
                Cell selectedCell = cells[0];
                cells.RemoveAt(0);

                if (selectedCell.Y == 0 || grid[selectedCell.Y - 1][selectedCell.X].Solid) {
                    this.makeSolid();
                    newCells.Add(selectedCell);
                    stationary = true;

                    return 1;

                } else {
                    selectedCell.Occupied = false;

                    Cell newCell = grid[selectedCell.Y - 1][selectedCell.X];

                    newCell.Occupied = true;

                    newCells.Add(newCell);

                }

            }

            cells = newCells;
            return 0;
        }

        public void  makeSolid() {
            foreach (Cell cell in cells) {
                cell.Solid = true;
                cell.Occupied = true;
              
            }
        }
    }

    public class Grain : Rock {
        /*
         TEST ROCK 
          #
         */
        public Grain(List<List<Cell>> grid, int y) {

            if (y > 0) {
                y -= 3;
            }
            Cell cell = grid[y][2];
            cell.Occupied = true;
            cells.Add(cell);

        }


    }

    class Line : Rock {
        /*
        ####
        */


    }

    class Cross : Rock {
         /*
        .#.
        ###
        .#.
         */


    }

    class LType : Rock{
        /*
        ..#
        ..#
        ###
         */

    }

    class Collum : Rock {
        /*
        #
        #
        #
        #
        */

    }

    class square : Rock {
        /*
        ##
        ##
        */

    }
}
