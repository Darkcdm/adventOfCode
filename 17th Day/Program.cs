﻿using System;

namespace _17th_Day {
    class Program {
        static void Main() {
            Console.WriteLine("Starting the program");

            Cave cave = new Cave();

            var result = cave.simulateRockHeightLimit(250, false);


            Console.WriteLine("Result is: " + result);
            Console.WriteLine("Ending the program");
        }
    }
}