const fs = require('fs');


//simple space object to futureproof the code 
class spaceCell {
    constructor(char, coords) {
        this.char = char;
        this.coords = coords;
        this.y = coords[0];
        this.x = coords[1];
        this.shortestPath = Infinity;


        if (char == "#") {
            this.type = "star";
        } else {
            this.type = "space";
        }

    }
}

//helper function to printout the map
function printMap(map) {
    for (let y = 0; y < map.length; y++) {
        let line = "";
        for (let x = 0; x < map[y].length; x++) {
            if (map[y][x].id != undefined) {
                line += map[y][x].id;
            } else {
                line += map[y][x].char;

            }
        }
        console.log(line);
    }
}

function addSpacerLine(map) {
    let line = [];
    for (let x = 0; x < map[0].length; x++) {
        line.push(new spaceCell(".", [map.length, x]));
    }
    map.push(line);
    return map;
}


function addSpacerCollumn(map) {
    for (let y = 0; y < map.length; y++) {

        map[y].push(new spaceCell(".", [y, map[y].length]));

    }
    return map;
}

//START OF EXEC CODE
//defining all start variables
let input = fs.readFileSync("test", "utf8");
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




//checking for empty space in rows

let spaceMapAfterExpansion = [];
for (let y = 0; y < map.length; y++) {
    let emptyRowStatus = true;
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].type == "star") {
            emptyRowStatus = false;
        }

    }
    spaceMapAfterExpansion.push(map[y]);
    if (emptyRowStatus) {
        spaceMapAfterExpansion = addSpacerLine(spaceMapAfterExpansion);
    }

}

map = spaceMapAfterExpansion;
spaceMapAfterExpansion = [];



//preseeting the map
for (let y = 0; y < map.length; y++) {
    spaceMapAfterExpansion.push([]);
}

//checking for empty space in collums
for (let x = 0; x < map[0].length; x++) {
    let emptyCollumStatus = true;
    for (let y = 0; y < map.length; y++) {
        let selectedCell = map[y][x];

        if (selectedCell.char == '#') {
            emptyCollumStatus = false;
        }
        spaceMapAfterExpansion[y].push(selectedCell);
    }
    if (emptyCollumStatus) {
        spaceMapAfterExpansion = addSpacerCollumn(spaceMapAfterExpansion);
    }
}
map = spaceMapAfterExpansion;


//mark get list of each start cells
//give each start an ID
//reset the coords of the stars
let stars = [];

let counter = 1;
for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[y].length; x++) {
        if (map[y][x].type === "star") {
            map[y][x].id = counter;
            counter++;
            map[y][x].x = x;
            map[y][x].y = y;
            stars.push(map[y][x]);

        }
    }

}
printMap(map);


const pairs = [];
for (let i = 0; i < stars.length; i++) {
    for (let j = i + 1; j < stars.length; j++) {
        const pair = [stars[i], stars[j]];
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