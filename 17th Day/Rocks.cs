using System;
using System.Collections.Generic;
using System.Linq;
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

        public Rock getRock() {
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

            return new Grain();
        }

        public Rock getGrain() {
            return new Grain();
        }
    
    }

    public class Rock {
        /*
        The tall, vertical chamber is exactly seven units wide. 
        Each rock appears so that its left edge is two units away from the left wall and its bottom edge is three units above the highest rock in the room (or the floor, if there isn't one).
         */
        List <Cell> cells = new List <Cell> ();
        bool stuck = false;

    }

    class Grain : Rock { 
        /*
         TEST ROCK 
          #
         */



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
