const fs = require("fs");


let input = fs.readFileSync("true", 'utf8');

input = input.split('\n');


let resultSum = 0;

//for each input line
for (let lineIndex = 0; lineIndex < input.length; lineIndex++) {

    //Load
    let sets = [];
    sets.push(parseInput(input[lineIndex]));

    //reverse the set
    for (let i = 0; i < sets.length; i++) {

        sets[i].reverse();

    }

    //calculate till you get zerosfor (let lineIndex = 0; lineIndex < input.length; lineIndex++) {
    while (!checkZeroSet(sets[sets.length - 1])) {
        sets.push(getDifSet(sets[sets.length - 1]));
    }




    //calculate  the backwards prediction
    sets[sets.length - 1].push(0);

    for (let i = sets.length - 2; i >= 0; i--) {

        sets[i].push(sets[i + 1][sets[i + 1].length - 1] + sets[i][sets[i].length - 1]);

    }

    resultSum += sets[0][sets[0].length - 1];
    console.log(sets);
}


console.log(resultSum);

function getDifSet(set) {
    let difSet = [];
    for (let i = 0; i < set.length - 1; i++) {
        let dif = (set[i] - set[i + 1]) * -1;
        difSet.push(dif);
    }
    return difSet;
}


function checkZeroSet(lastSet) {
    for (let i = 0; i < lastSet.length; i++) {
        if (lastSet[i] != 0) {
            return false;
        }
    }
    return true;
}


function parseInput(line) {
    line = line.split(" ");
    let set = [];

    for (let i = 0; i < line.length; i++) {
        set.push(Number(line[i]));
    }
    return set;
}