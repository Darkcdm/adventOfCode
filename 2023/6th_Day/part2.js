'use strict';
let testInput = {
    time: 71530,
    distance: 940200
}

let trueInput = {
    time: 60947882,
    distance: 475213810151650
}


let input = trueInput;

let result = 1;


let time = input.time;
let finalDistance = input.distance;

let wins = 0;

for (let speed = 1; speed < time; speed++) {

    let coveredDistance = (time - speed) * speed;

    if (coveredDistance > finalDistance) {
        wins++;
    }

}
console.log(wins);
result = result * wins;


console.log(result);
