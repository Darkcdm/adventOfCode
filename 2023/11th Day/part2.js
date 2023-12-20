const fs = require('fs');
const spaceCoefficient = 999999;


//simple space object to futureproof the code 
class spaceCell {
    constructor(char, coords) {
        this.char = char;
        this.coords = coords;
        this.y = coords[0];
        this.x = coords[1];
    }
}

function increaseGalaxyFromY(yLimit, galaxies) {
    for (let i = 0; i < galaxies.length; i++) {
        if (galaxies[i].coords[0] > yLimit) {
            galaxies[i].y += spaceCoefficient;
        }
    }
}

function increaseGalaxyFromX(xLimit, galaxies) {
    for (let i = 0; i < galaxies.length; i++) {
        if (galaxies[i].coords[1] > xLimit) {
            galaxies[i].x += spaceCoefficient;
        }
    }
}

//START OF EXEC CODE
//defining all start variables
let input = fs.readFileSync("true", "utf8");
input = input.split("\n");



let map = [];

//loading the map (2D Array) from input
for (let y = 0; y < input.length; y++) {
    let line = input[y];
    line = line.trim();
    let row = [];
    for (let x = 0; x < line.length; x++) {

        row.push(new spaceCell(line[x], [y, x]));

    }
    map.push(row);
}

let galaxies = [];
let idCounter = 1;
for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].char == "#") {
            map[y][x].id = idCounter++;
            galaxies.push(map[y][x]);
        }
    }
}

//check for empty rows
//if detected: for all past galaxies in the map, add coefficients to Y

for (let y = 0; y < map.length; y++) {
    let emptyRowStatus = true;
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].char == "#") {
            emptyRowStatus = false;
        }

    }
    if (emptyRowStatus) {
        increaseGalaxyFromY(y, galaxies);
    }

}


//check for empty collums
//if detected: for all past galaxies in the map, add coefficients to X
for (let x = 0; x < map[0].length; x++) {
    let emptyCollumStatus = true;
    for (let y = 0; y < map.length; y++) {
        let selectedCell = map[y][x];

        if (selectedCell.char == '#') {
            emptyCollumStatus = false;
        }
    }
    if (emptyCollumStatus) {
        increaseGalaxyFromX(x, galaxies);

    }
}


//Commit Taxi cab geometry and calculate final sum

const pairs = [];
for (let i = 0; i < galaxies.length; i++) {
    for (let j = i + 1; j < galaxies.length; j++) {
        const pair = [galaxies[i], galaxies[j]];
        pairs.push(pair);
    }
}


let sum = 0;
for (let i = 0; i < pairs.length; i++) {
    let pointA = pairs[i][0];
    let pointB = pairs[i][1];

    let distance = Math.abs(pointA.x - pointB.x) + Math.abs(pointA.y - pointB.y);

    sum += distance;
}

console.log(sum);
