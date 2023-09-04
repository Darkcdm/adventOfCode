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
					return new Line(grid, y);
				case 1:
					return new Cross(grid, y);
				case 2:
					return new LType(grid, y);
				case 3:
					return new Collum(grid, y);
				case 4:
					return new Square(grid, y);
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


			if (!stationary)
			{
				foreach (Cell selectedCell in cells)
				{

					


					//is not at side and the looked at cell is not already occupied 
					if (selectedCell.X + dirValue < 0 || selectedCell.X + dirValue > grid[0].Count - 1 || grid[selectedCell.Y][selectedCell.X + dirValue].Occupied)
					{
						newCells.Add(selectedCell);
						continue;

					}
					else
					{
						

						Cell newCell = grid[selectedCell.Y][selectedCell.X + dirValue];

						

						newCells.Add(newCell);

					}
				}
			}

			foreach(Cell cell in cells) {
				cell.Occupied = false;
			}
			foreach(Cell cell in newCells) {
				cell.Occupied = true;
			}
			cells = newCells;

			return 0;
		}

		public int moveDown(List<List<Cell>> grid) {
			List <Cell> newCells = new List <Cell> ();

			
			while (cells.Count > 0 && !stationary) {
				Cell selectedCell = cells[0];
				cells.RemoveAt(0);

				if (selectedCell.Y == 0 || grid[selectedCell.Y - 1][selectedCell.X].Solid || grid[selectedCell.Y-1][selectedCell.X].Occupied)
				{
					selectedCell.Solid = true;
					makeSolid();
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

			Cell cell = grid[y+4][2];
			cell.Occupied = true;
			cells.Add(cell);

		}


	}

	class Line : Rock {
		/*
		####
		*/
		public Line(List<List<Cell>> grid, int y)
		{
			for(int i = 0; i < 4; i++)
			{
				Cell cell = grid[y + 4][2 + i];
				cell.Occupied = true;
				cells.Add(cell);
			}

		}

	}

	class Cross : Rock {
		/*
	   .#.
	   ###
	   .#.
		*/

		public Cross(List<List<Cell>> grid, int y){

			Cell cell;

			cell = grid[y + 4][2];
			cell.Occupied = true;
			cells.Add(cell);
            
			cell = grid[y + 4][3];
            cell.Occupied = true;
            cells.Add(cell);

			cell = grid[y + 4][4];
			cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 3][3];
			cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 5][3];
            cell.Occupied = true;
            cells.Add(cell);


        }
    }

	class LType : Rock{
		/*
		..#
		..#
		###
		 */

		public LType(List<List<Cell>> grid, int y) {
            Cell cell;

            cell = grid[y + 4][2];
            cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 4][3];
            cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 4][4];
            cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 5][4];
            cell.Occupied = true;
            cells.Add(cell);

            cell = grid[y + 6][4];
            cell.Occupied = true;
            cells.Add(cell);
        }

	}

	class Collum : Rock {
		/*
		#
		#
		#
		#
		*/


		public Collum(List<List<Cell>> grid, int y) {
			for(int i = 0; i < 4; i++) {
				Cell cell = grid[y+4+i][2];
				cell.Occupied = true;
				cells.Add(cell);
			}
		}

	}

	class Square : Rock {
		/*
		##
		##
		*/

		public Square(List<List<Cell>> grid, int y) {
            Cell cell = grid[y + 4][2];
            cell.Occupied = true;
            cells.Add(cell);
             cell = grid[y + 4][3];
            cell.Occupied = true;
            cells.Add(cell);
             cell = grid[y + 5][2];
            cell.Occupied = true;
            cells.Add(cell);
             cell = grid[y + 5][3];
            cell.Occupied = true;
            cells.Add(cell);
        }


	}
}
