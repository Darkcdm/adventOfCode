
using _20th_Day;
using System;

namespace _20th_Day {
    internal class Program {
        static void Main() {
            Input input = new Input(false);
            Process process = new Process();

            process.iterateTransmition(input);

            for (int i = 0; i < input.transmition.Count; i++) {
                Console.Write(input.transmition[i] + " ");
            }
            Console.Write("\n");

            Console.WriteLine("he sum of the three numbers that form the grove coordinates is: " + process.getResult(input));
        }

    }

}