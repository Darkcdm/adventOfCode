// See https://aka.ms/new-console-template for more information

using System;

namespace _1st_Day {
    class Program {
        static void Main() {

            LineReader reader = new LineReader("trueInput.txt");

            Console.WriteLine(reader.returnSumValue());

        }
    }


    public class LineReader {
        string inputFile;
        List<string> filteredInput = new List<string>();
        List<int> transformedInput = new List<int>();
        
        public LineReader(string inputFile) {
            this.inputFile = inputFile;
        }

        void loadInput() {
            if (File.Exists(inputFile)) {
                // Open the file with a StreamReader
                using (StreamReader reader = new StreamReader(inputFile)) {
                    // Read lines until the end of the file is reached
                    while (!reader.EndOfStream) {
                        // Read the current line
                        string line = reader.ReadLine();

                        string foundChars = "";

                        // Process the line
                        //checking from front
                        for(int i = 0; i < line.Length; i++) {
                            if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9') {
  
                                foundChars = foundChars + line[i];
                                break;
                            }
                        }
                        //checking from the back
                        for(int i = line.Length - 1 ; i >= 0; i--) {
                            if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9') {
     
                                foundChars = foundChars + line[i];
                                break;
                            }
                        }
                        filteredInput.Add(foundChars);
                    }
                }
            } else {
                Console.WriteLine("File not found.");
            }
        }

        void transformInput() {
            for (int i = 0; i < filteredInput.Count; i++) {


                transformedInput.Add(int.Parse(filteredInput[i]));
            }
        }

        public int  returnSumValue() {
            loadInput();
            transformInput();

            return transformedInput.AsQueryable().Sum();
        }

    }

}

