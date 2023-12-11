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
        this.visited = false;


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


function checkNorth(pipe, map) {
    if (pipe.y == 0) {
        return;
    }

    let selectedPipe = map[pipe.y - 1][pipe.x];

    for (let i = 0; i < selectedPipe.directions.length; i++) {
        if (selectedPipe.directions[i] == 'S') {
            return selectedPipe;
        }
    }

    return;
}
function checkSouth(pipe, map) {
    if (pipe.y == map.length - 1) {
        return;
    }

    let selectedPipe = map[pipe.y + 1][pipe.x];
    for (let i = 0; i < selectedPipe.directions.length; i++) {
        if (selectedPipe.directions[i] == 'N') {
            return selectedPipe;
        }
    }

    return;

}
function checkWest(pipe, map) {
    if (pipe.x == 0) {
        return;
    }

    let selectedPipe = map[pipe.y][pipe.x - 1];
    for (let i = 0; i < selectedPipe.directions.length; i++) {
        if (selectedPipe.directions[i] == 'E') {
            return selectedPipe;
        }
    }

    return;



}
function checkEast(pipe, map) {

    if (pipe.x == map.length - 1) {
        return;
    }

    let selectedPipe = map[pipe.y][pipe.x + 1];
    for (let i = 0; i < selectedPipe.directions.length; i++) {
        if (selectedPipe.directions[i] == 'W') {
            return selectedPipe;
        }
    }

    return;



}


function reverseDirection(dir) {
    switch (dir) {
        case 'N':
            return 'S';
        case 'E':
            return 'W';
        case 'S':
            return 'N';
        case 'W':
            return 'E';
    }
}

function getForConnections(pipe, map, path) {
    for (let directionIndex = 0; directionIndex < pipe.directions.length; directionIndex++) {
        let type = pipe.directions[directionIndex];
        let scannedPipe;


        //check for the connection.
        //connection must be shared by both sides
        //if there is a correct connection, then it is outputed int scannedPipe
        switch (type) {
            case 'N':
                scannedPipe = checkNorth(pipe, map);
                break;
            case 'S':
                scannedPipe = checkSouth(pipe, map);

                break;
            case 'E':
                scannedPipe = checkEast(pipe, map);

                break;
            case 'W':
                scannedPipe = checkWest(pipe, map);

                break;
        }


        if (scannedPipe != undefined) {
            if (JSON.stringify(scannedPipe) == JSON.stringify(path[path.length - 2])) {
                continue;
            }
            return scannedPipe;
        }
    }
    console.error('PIPE IS NOT CONNECTED', pipe);

}


//MAIN CODE
//set ALL
let map = new Array();

let input = fs.readFileSync("true", 'utf-8');
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


let activePipe = startPipe;

let maxPathLength = map.length * map[0].length;

let path = [];
do {
    path.push(activePipe);
    activePipe.visited = true;

    //check all the other pipes in the direction that the activePipe has pipes through
    let connection = getForConnections(activePipe, map, path);
    if (connection !== undefined) {
        //choose the first pipe that matches in both directions and make it the first activePipe
        activePipe = connection;
    }

    if (path.length >= maxPathLength) {
        console.error('max path length exceeded');
        break;
    }


} while (activePipe != startPipe);

console.log(path);
console.log(path.length / 2);


