// See https://aka.ms/new-console-template for more information

using System;
using System.Text.RegularExpressions;
using System.Threading;

namespace _1st_Day {
    class Program {
        static void Main() {

            LineReader reader = new LineReader("trueInput.txt");

            Console.WriteLine(reader.returnSumValue());

        }
    }


    public class LineReader {
        string inputFile;
        List<List<string>> filteredInput = new List<List<string>>();
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
                        string line = "";
                        line = reader.ReadLine();

                        string reverseLine = reverse(line);

                        string pattern = "(one|two|three|four|five|six|seven|eight|nine|[1-9])";
                        string reversePattern = "(eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|[1-9])";


                        // Create a Regex object
                        Regex regex = new Regex(pattern);
                        Regex reverseRegex = new Regex(reversePattern);

                        // Use the Matches method to find all matches in the sentence
                        MatchCollection matches = regex.Matches(line);
                        MatchCollection reverseMatches = reverseRegex.Matches(reverseLine);
                        
                        List<String> pair = new List<String>();
                        pair.Add(matches.First().Value);
                        pair.Add(reverse(reverseMatches.First().Value));

                        filteredInput.Add(pair);
         
                    }


                }
                } else {
                    Console.WriteLine("File not found.");
            }
        }
        string reverse(String text) {
            string result = "";
            for (int i = text.Length - 1; i >= 0; i--) {
                result += text[i];
            }
            return result;
        }

        void transformInput() {
            for (int i = 0; i < filteredInput.Count; i++) {

                String numberStr = "";

                foreach(String value in filteredInput[i]) {
                    if (IsNumeric(value)) {
                        numberStr += value;
                    } else {
                        switch(value) {
                            case "one":
                                numberStr += "1";
                                break;
                            case "two":
                                numberStr += "2";
                                break;
                            case "three":
                                numberStr += "3";
                                break;
                            case "four":
                                numberStr += "4";
                                break;
                            case "five":
                                numberStr += "5";
                                break;
                            case "six":
                                numberStr += "6";
                                break;
                            case "seven":
                                numberStr += "7";
                                break;
                            case "eight":
                                numberStr += "8";
                                break;
                            case "nine":
                                numberStr += "9";
                                break;
                            default:
                                
                                Console.WriteLine("FUCK");
                            break;
                        }
                    }
                }

                Console.WriteLine(int.Parse(numberStr) + "=" + numberStr);

                transformedInput.Add(int.Parse(numberStr));
            }
        }

        public int  returnSumValue() {
            loadInput();
            transformInput();

            return transformedInput.AsQueryable().Sum();
        }

        static bool IsNumeric(string input) {
            // Try to parse the string as a number
            return !string.IsNullOrWhiteSpace(input) && double.TryParse(input, out _);
        }

    }

}

