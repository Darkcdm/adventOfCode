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

function checkDirection(pipe, checkDir, actualPipe) {

    if (actualPipe.directions.length == 4) {
        directions = pipe.directions;

        for (let i = 0; i < directions.length; i++) {
            if (directions[i] === checkDir) {
                return true;
            }
        }

    }



    if (pipe.directions.length == 2 && actualPipe.directions.length == 2) {


        directions = pipe.directions;

        for (let i = 0; i < directions.length; i++) {
            if (directions[i] === checkDir) {
                return true;
            }
        }


    }



    return false;
}
function reverseDirection(direction) {
    switch (direction) {
        case 'N':
            return 'S';
        case 'E':
            return 'W';
        case 'S':
            return 'N';
        case 'W':
            return 'E';

        default: console.error("Invalid direction");
    }
}

function checkPath(scannedPipe, path) {



    for (let i = 0; i < path.length; i++) {
        if (JSON.stringify(scannedPipe) == JSON.stringify(path[i])) {
            return false;
        }
    }
    return true;

}

function checkLimits(actualPipe, map) {
    if (actualPipe.x == 0 || actualPipe.y == 0) return true;
}

let map = new Array();


let input = fs.readFileSync("test", 'utf-8');
input = input.split('\n');

let startingPipe;

//load the input into a 2D map
for (let x = 0; x < input.length; x++) {
    let line = input[x].trim();

    mapRow = [];
    for (let y = 0; y < line.length; y++) {
        let pipe = new Pipe(line[y], [x, y]);
        //find the starting pipe
        if (pipe.type == "start") {
            startingPipe = pipe;
        }

        mapRow.push(pipe);



    }
    map.push(mapRow);

}

//start the math finding
let pipePath = [];
let actualPipe = startingPipe;

//set an actualPipe and then scan in cardinal directions
do {

    let scannedPipe;



    for (let dirIndex = 0; dirIndex < actualPipe.directions.length; dirIndex++) {

        //scan 
        if (!checkLimits(actualPipe, map)) {
            continue;
        }
        scannedPipe = map[actualPipe.x - 1][actualPipe.y];

        if (checkDirection(scannedPipe, reverseDirection(actualPipe.directions[dirIndex]), actualPipe)) {

            if (checkPath(scannedPipe, pipePath)) {

                actualPipe = scannedPipe;

                pipePath.push(actualPipe);
                continue;
            }
        }
    }




    console.log(pipePath.length);


} while (actualPipe.type != "start")



console.log(pipePath);
console.log(pipePath.length);
console.log(pipePath.length / 2);