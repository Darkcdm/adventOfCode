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
        this.piping = false;
        this.leftOfPipe = false;
        this.rightOfPipe = false;
        this.isInside = false;

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

    if (pipe.x == map[0].length - 1) {
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

function printMap(map) {
    for (let y = 0; y < map.length; y++) {
        let line = "";
        for (let x = 0; x < map[0].length; x++) {
            if (map[y][x].piping) {
                line += map[y][x].char;
            } else {
                if (map[y][x].leftOfPipe && map[y][x].rightOfPipe) {
                    line += "H";
                }
                else if (map[y][x].leftOfPipe) {
                    line += "L";
                } else if (map[y][x].rightOfPipe) {
                    line += "R";
                } else {
                    line += "O";
                }
            }

        }
        console.log(line);
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


let activePipe = startPipe;

let maxPathLength = map.length * map[0].length;

let path = [];
do {
    path.push(activePipe);
    activePipe.piping = true;

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

console.log(path.length / 2);


let { minX, minY, maxX, maxY } = path.reduce((acc, pipe) => {
    return {
        minX: Math.min(acc.minX !== undefined ? acc.minX : pipe.x, pipe.x),
        minY: Math.min(acc.minY !== undefined ? acc.minY : pipe.y, pipe.y),
        maxX: Math.max(acc.maxX !== undefined ? acc.maxX : pipe.x, pipe.x),
        maxY: Math.max(acc.maxY !== undefined ? acc.maxY : pipe.y, pipe.y)
    };
}, {});

console.log("Minimum X:", minX);
console.log("Minimum Y:", minY);
console.log("Maximum X:", maxX);
console.log("Maximum Y:", maxY);



for (let pathIndex = 0; pathIndex < path.length - 1; pathIndex++) {

    let currentPipe = path[pathIndex];
    let nextPipe = path[pathIndex + 1];
    let previousPipe;
    if (pathIndex - 1 < 0) {

        previousPipe = path[path.length - 1];
    } else {
        previousPipe = path[pathIndex - 1];
    }

    let vector = [nextPipe.x - currentPipe.x, nextPipe.y - currentPipe.y];
    let vectorLeft = [vector[1], vector[0] * -1];
    let vectorRight = [vectorLeft[0] * -1, vectorLeft[1] * -1];

    let leftPipeX = vectorLeft[0] + currentPipe.x;
    let leftPipeY = vectorLeft[1] + currentPipe.y;

    let rightPipeX = vectorRight[0] + currentPipe.x;
    let rightPipeY = vectorRight[1] + currentPipe.y;

    // Check boundaries before accessing map
    if (leftPipeX >= 0 && leftPipeX < map[0].length && leftPipeY >= 0 && leftPipeY < map.length) {

        if (map[leftPipeY][leftPipeX].piping == false) {

            map[leftPipeY][leftPipeX].leftOfPipe = true;
        }
    }



    // Check boundaries before accessing map
    if (rightPipeX >= 0 && rightPipeX < map[0].length && rightPipeY >= 0 && rightPipeY < map.length) {

        if (map[rightPipeY][rightPipeX].piping == false) {

            map[rightPipeY][rightPipeX].rightOfPipe = true;
        }

    }

    if (currentPipe.char == '-' || currentPipe.char == '|') {
        continue;
    }
    // Handle corners


    // check from which side does the secondary pipe comes from
    let pipeToLeft;
    if (leftPipeX >= 0 && leftPipeX < map[0].length && leftPipeY >= 0 && leftPipeY < map.length) {
        pipeToLeft = map[leftPipeY][leftPipeX];
    } else {
        pipeToLeft = {};
    }
    let vectorBack = [vector[0] * -1, vector[1] * -1];

    let backPipeX = vectorBack[0] + currentPipe.x;
    let backPipeY = vectorBack[1] + currentPipe.y;





    if (JSON.stringify(pipeToLeft) == JSON.stringify(previousPipe)) {
        //coming from LEFT
        let diagonalPipeX = vectorRight[0] + backPipeX;
        let diagonalPipeY = vectorRight[1] + backPipeY;
        if (diagonalPipeX >= 0 && diagonalPipeX < map[0].length && diagonalPipeY >= 0 && diagonalPipeY < map.length) {
            map[rightPipeY][rightPipeX].rightOfPipe = true;
        }

    } else {
        //coming from RIGHT
        let diagonalPipeX = vectorLeft[0] + backPipeX;
        let diagonalPipeY = vectorLeft[1] + backPipeY;
        if (diagonalPipeX >= 0 && diagonalPipeX < map[0].length && diagonalPipeY >= 0 && diagonalPipeY < map.length) {
            map[leftPipeY][leftPipeX].leftOfPipe = true;
        }
    }
}




//mark the last pipe
let currentPipe = path[path.length - 1];
let nextPipe = path[0];



//get a list of all unmarked Pipes
let unmarkedPipes = [];

for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[y].length; x++) {
        if (!map[y][x].leftOfPipe && !map[y][x].rightOfPipe && !map[y][x].piping) {
            unmarkedPipes.push(map[y][x]);
        }
    }
}

printMap(map);
let memory = 0;
while (unmarkedPipes.length > 0) {
    console.log(unmarkedPipes.length);
    if (unmarkedPipes.length == memory) {
        break;
    } else {
        memory = unmarkedPipes.length;
    }

    let newUnmarkedPipes = []; // Create a new array to store unmarked pipes for the next iteration

    for (let pipeIndex = 0; pipeIndex < unmarkedPipes.length; pipeIndex++) {

        let selectedPipe = unmarkedPipes[pipeIndex];
        let x = selectedPipe.x;
        let y = selectedPipe.y;

        // Function to check and update the properties of the selected pipe
        const updatePipe = (dx, dy, property) => {
            let adjacentX = x + dx;
            let adjacentY = y + dy;

            // Check if adjacent position is within the map bounds
            if (
                adjacentX >= 0 && adjacentX < map[0].length &&
                adjacentY >= 0 && adjacentY < map.length
            ) {
                let adjacentPipe = map[adjacentY][adjacentX];
                if (adjacentPipe[property] && !adjacentPipe.piping) {
                    selectedPipe[property] = true;
                    return true; // Property set, no need to add to newUnmarkedPipes
                }
            }

            return false; // Property not set, need to add to newUnmarkedPipes
        };

        // Check and update properties for left, right, top, and down
        let leftUpdated = updatePipe(-1, 0, 'leftOfPipe');

        let rightUpdated = updatePipe(1, 0, 'leftOfPipe');

        let topUpdated = updatePipe(0, -1, 'leftOfPipe');

        let downUpdated = updatePipe(0, 1, 'leftOfPipe');

        if (leftUpdated || rightUpdated || topUpdated || downUpdated) {
            map[selectedPipe.y][selectedPipe.x].leftOfPipe = true;
            continue;
        }

        leftUpdated = updatePipe(-1, 0, 'rightOfPipe');
        rightUpdated = updatePipe(1, 0, 'rightOfPipe');
        topUpdated = updatePipe(0, -1, 'rightOfPipe');
        downUpdated = updatePipe(0, 1, 'rightOfPipe');

        if (leftUpdated || rightUpdated || topUpdated || downUpdated) {
            map[selectedPipe.y][selectedPipe.x].rightOfPipe = true;
            continue;
        }

        newUnmarkedPipes.push(selectedPipe);

    }

    // Update unmarkedPipes for the next iteration
    unmarkedPipes = newUnmarkedPipes;
}
printMap(map);





//SCANN
let insideCounter = 0;

for (let y = 0; y < map.length; y++) {
    let inPipeState = false;
    for (let x = 0; x < map[0].length; x++) {
        let selectedPipe = map[y][x];

        if (selectedPipe.piping && selectedPipe.char != '-') {
            if (inPipeState) {
                inPipeState = false;
            } else {
                inPipeState = true;
            }
            continue;
        }

        if (inPipeState) {
            selectedPipe.isInside = true;
            insideCounter++;
        }

    }
}
console.log(insideCounter);
//SCANN


for (let y = 0; y < map.length; y++) {
    let line = "";
    for (let x = 0; x < map[0].length; x++) {
        if (map[y][x].piping) {
            line = line + "*";
        } else if (map[y][x].isInside) {
            line = line + "I";
        } else {
            line = line + "O";
        }

    }
    console.log(line);
}


let rightCount = 0;
for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].rightOfPipe && !map[y][x].piping) {
            rightCount++;
        }
    }
}

let leftCount = 0;
for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].leftOfPipe && !map[y][x].piping) {
            leftCount++;
        }
    }
}
console.log(leftCount, rightCount);

/*
There's several ways to do it. Here are three distinct ones:

Expand the resolution of the map (ie. mapping to a grid 3 times larger) so that you can use a BFS that actually can squeeze through the gaps as necessary.

Given a specific tile on the map, it is possible to detect whether it is inside or outside the loop solely based on the tiles to the left (or right) of it (filtered to only include the ones actually part of the loop) and nothing else. (For instance, if it has an odd number of | tiles to its right and no horizontal segments, it is certainly inside the loop.)

Using the shoelace formula, you can compute the area of your loop. From this, it is possible to get the amount of contained points.
*/