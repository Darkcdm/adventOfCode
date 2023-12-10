//imports
const fs = require('fs');

class Pipe {
    constructor(char, coords) {
        this.directions = [];
        this.char = char;
        this.coords = coords;
        this.x = coords[0];
        this.y = coords[1];
        this.type;


        if (char == '.') {
            this.type = "ground";
            return;
        }
        if (char == 'S') {
            this.type = "start";
            this.directions = ['N', 'S', 'E', 'W'];
            return;
        }

        this.type = "pipe";
        switch (char) {
            case '|':
                this.directions = ['N', 'S'];
                break;
            case '-':
                this.directions = ['E', 'W'];

                break;
            case 'L':
                this.directions = ['N', 'E'];

                break;
            case 'J':
                this.directions = ['N', 'W'];

                break;
            case '7':
                this.directions = ['W', 'S'];

                break;
            case 'F':
                this.directions = ['E', 'S'];

                break;
            default:
                console.error('Invalid character');
        }
    }
}



//MAIN CODE
//set ALL
let map = new Array();

let input = fs.readFileSync("test", 'utf-8');
input = input.split('\n');
let startPipe;

//Import input into an map
for (let lineIndex = 0; lineIndex < input.length; lineIndex++) {
    let line = input[lineIndex];
    line = line.trim();

    let mapRow = [];
    for (let charIndex = 0; charIndex < line.length; charIndex++) {
        let pipe = new Pipe(line[charIndex], [charIndex, lineIndex]);
        if (pipe.type == "start") {
            startPipe = pipe;
        }

        mapRow.push(pipe);
    }

    map.push(mapRow);
}






console.log(startPipe);





