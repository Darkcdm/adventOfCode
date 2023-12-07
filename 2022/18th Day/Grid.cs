using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _18th_Day {
    public class Grid {

        public List<List<List<Cube>>> Matrix = new List<List<List<Cube>>>();

        int[] dimensions = new int [3];


        public Grid(string inputPath) {
            string[] input = File.ReadAllLines(inputPath);


            int[] maxLimits = getHighestIndexes(input);

            for(int i = 0; i < 3; i++) { 
                dimensions[i] = maxLimits[i];
            }


            for (int x = 0; x <= dimensions[0]; x++) {
                List<List<Cube>> YLine = new List<List<Cube>>();

                for (int y = 0; y <= dimensions[1]; y++) {

                    List<Cube> ZLine = new List<Cube>();

                    for (int z = 0; z <= dimensions[2]; z++) {
                        Cube cell = new Cube(x,y,z);

                        ZLine.Add(cell);

                    }

                    YLine.Add(ZLine);

                }

                Matrix.Add(YLine);

            }

        }

        private int[] getLowestIndexes(string[] input) {
            string[] startValue = input[0].Split(',');
            int[] results = { int.Parse(startValue[0]), int.Parse(startValue[1]), int.Parse(startValue[2]) };


            foreach (string line in input) {
                string[] values = line.Split(',');
                


                for (int i = 0; i < 3; i++) {
                    int value = int.Parse(values[i]);
                    
                    if (value < results[i]) {
                        results[i] = value;
                    }
                }
            }

            return results;
        }
        
        private int [] getHighestIndexes(string[] input) {
            string[] startValue = input[0].Split(',');
            int[] results = { int.Parse(startValue[0]), int.Parse(startValue[1]), int.Parse(startValue[2]) };


            foreach (string line in input) {
                string[] values = line.Split(',');



                for (int i = 0; i < 3; i++) {
                    int value = int.Parse(values[i]);

                    if (value > results[i]) {
                        results[i] = value;
                    }
                }
            }

            return results;
        }

        
        public int simulateDroplets(string inputPath) {

            List<Cube> allDroplets = new List<Cube>(); 


            string[] inputLines = File.ReadAllLines(inputPath);

            foreach (string line in inputLines) {
                string[] stringValues = line.Split(',');
                
                int[] values = new int[3];
                
                for (int i = 0; i<stringValues.Length; i++) {
                    values[i] = int.Parse(stringValues[i]);
                }

                Cube selectedCell = Matrix[values[0]][values[1]][values[2]];

                selectedCell.occupied = true;

                allDroplets.Add(selectedCell);

                checkCubeBorders(selectedCell);
            }


            //check for Bubbles
            



            int result = 0;

            foreach (Cube selectedCell in allDroplets) {
                result += selectedCell.freeSides;
            }

            return result;
        }


        void checkCubeBorders(Cube selectedCube) {
            

            //Checking Xs
            if (Matrix.Count > selectedCube.X + 1 && Matrix[selectedCube.X+1][selectedCube.Y][selectedCube.Z].occupied) {
                Matrix[selectedCube.X + 1][selectedCube.Y][selectedCube.Z].freeSides--;
                selectedCube.freeSides--;
            }
            if (selectedCube.X-1 >= 0 && Matrix[selectedCube.X-1][selectedCube.Y][selectedCube.Z].occupied) {
                Matrix[selectedCube.X - 1][selectedCube.Y][selectedCube.Z].freeSides--;
                selectedCube.freeSides--;
            }


            //Checking Ys
            if (Matrix[0].Count > selectedCube.Y + 1 && Matrix[selectedCube.X][selectedCube.Y + 1][selectedCube.Z].occupied) {
                Matrix[selectedCube.X][selectedCube.Y + 1][selectedCube.Z].freeSides--;
                selectedCube.freeSides--;
            }
            if (selectedCube.Y-1 >= 0 && Matrix[selectedCube.X][selectedCube.Y - 1][selectedCube.Z].occupied) {
                Matrix[selectedCube.X][selectedCube.Y - 1][selectedCube.Z].freeSides--;
                selectedCube.freeSides--;
            }

            if (Matrix[0][0].Count > selectedCube.Z+1 && Matrix[selectedCube.X][selectedCube.Y][selectedCube.Z + 1].occupied) {
                Matrix[selectedCube.X][selectedCube.Y][selectedCube.Z + 1].freeSides--;
                selectedCube.freeSides--;
            }
            if (selectedCube.Z-1 >= 0 && Matrix[selectedCube.X][selectedCube.Y][selectedCube.Z - 1].occupied) {
                Matrix[selectedCube.X][selectedCube.Y][selectedCube.Z - 1].freeSides--;
                selectedCube.freeSides--;
            }

        }

    }
}
