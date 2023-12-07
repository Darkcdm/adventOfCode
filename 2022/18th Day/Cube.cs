using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _18th_Day {
    public class Cube {

        public Cube(int x = -1, int y = -1, int z = -1) { 
            
            this.X = x;
            this.Y = y;
            this.Z = z;
        }

        public int X;
        public int Y;
        public int Z;

        public bool occupied = false;
        public int freeSides = 6;

    }

}
