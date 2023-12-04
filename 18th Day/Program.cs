using System;

namespace _18th_Day { 

    internal class Program { 
        static void Main() {
            bool TESTING = true;
            string inputPath;

            if (TESTING) {
                inputPath = "TestInput.txt";
            } else {
                inputPath = "TrueInput.txt";
            }


            Grid grid = new Grid(inputPath);

            int result = grid.simulateDroplets(inputPath);
        
            Console.WriteLine("The result of the simulation is: " + result);
        }

    }

}