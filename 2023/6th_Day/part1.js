'use strict';
let testInput = {
    time: [7, 15, 30],
    distance: [9, 40, 200]
}

let trueInput = {
    time: [60, 94, 78, 82],
    distance: [475, 2138, 1015, 1650]
}


let input = trueInput;

let result = 1;

for (let i = 0; i < input.distance.length; i++) {
    let time = input.time[i];
    let finalDistance = input.distance[i];

    let wins = 0;

    for (let speed = 1; speed < time; speed++) {

        let coveredDistance = (time - speed) * speed;

        if (coveredDistance > finalDistance) {
            wins++;
        }

    }
    console.log(wins);
    result = result * wins;
}

console.log(result);
