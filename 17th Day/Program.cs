using System;

namespace _17th_Day {
    class Program {
        static void Main() {
            Console.WriteLine("Starting the program");

            Cave cave = new Cave();

            var result = cave.simulateRockHeightLimit(3, true);


            Console.WriteLine("Result is: " + result);
            Console.WriteLine("Ending the program");
        }
    }
}