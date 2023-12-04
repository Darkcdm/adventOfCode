using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _20th_Day {
    internal class Process {
        public void iterateTransmition(Input input) {

            List<int> result = input.transmition;


            for (int index = 0; index < input.transmition.Count; index++) {
                int value = input.transmition[index];

                result[getShiftedIndex(index, value, input.transmition.Count)] = value;

            }

            input.transmition = result;
        }

        int getShiftedIndex (int index, int value, int max) {
            int result = index + value;

            while(result >= max || result < 0) { 

                if (result < 0) {
                    result = result + max;
                }
                if (result >= max) {
                    result = result - max;
                }
            }
            return result;
        }
        int getZeroIndex(Input input) {
            for (int index = 0; index < input.transmition.Count; index++) {
                if (input.transmition[index] == 0) {
                    return index;
                }
            }
            return -1;
        }

        public int getResult(Input input) {

            int zeroIndex = getZeroIndex(input);

            int index1 = getShiftedIndex(zeroIndex, 1000, input.transmition.Count);
            int index2 = getShiftedIndex(zeroIndex, 2000, input.transmition.Count);
            int index3 = getShiftedIndex(zeroIndex, 3000, input.transmition.Count);

            Console.WriteLine(index1 + ", " + index2 + ", " + index3);

            return index1 + index2 + index3;
        }

    }
}
