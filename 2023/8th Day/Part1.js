const fs = require('fs');


let input = fs.readFileSync("test", 'utf8');
input = input.split('\n');

let network = new Map();
let instructions = new String();

instructions = input[0].trim();

let startNodeStrings = [];
let endNodeStrings = [];

for (let i = 2; i < input.length; i++) {

    let line = input[i];
    line = line.split('=');

    let nodeName = line[0][0] + line[0][1] + line[0][2];

    line = line[1].split(',');

    let nodeLeft = line[0][2] + line[0][3] + line[0][4];
    let nodeRight = line[1][1] + line[1][2] + line[1][3];

    if (nodeName[2] == 'A') {
        startNodeStrings.push(nodeName);
    }

    if (nodeName[2] == 'Z') {
        endNodeStrings.push(nodeName);
    }


    network.set(nodeName, [nodeLeft, nodeRight]);
}

activeNodes = [];
for (let i = 0; i < startNodeStrings.length; i++) {
    activeNodes.push(network.get(startNodeStrings[i]))
}

finalNodes = [];
for (let i = 0; i < endNodeStrings.length; i++) {
    finalNodes.push(network.get(endNodeStrings[i]))

}

let counter = 0;
let instructionCounter = 0;

let results = [];

for (let startNodeIndex = 0; startNodeIndex < activeNodes.length; startNodeIndex++) {
    activeNode = activeNodes[startNodeIndex];
    let counter = 0;
    let instructionCounter = 0;



    while (checkNode(activeNode, finalNodes)) {
        if (instructionCounter >= instructionCounter.length) {
            instructionCounter = 0;
        }

        if (instructions[instructionCounter] == 'L') {
            activeNode = network.get(activeNode[0]);
        } else {
            activeNode = network.get(activeNode[1]);
        }

        counter++;
        instructionCounter++;
    }

    results.push(counter);

}



console.log("LCM of", results, "is:", lcmArray(results));





function checkNode(activeNode, finalNodes) {

    for (let j = 0; j < finalNodes.length; j++) {
        if (activeNode == finalNodes[j]) {
            return false;
        }
    }

    return true;


}


// Function to calculate the greatest common divisor (GCD)
function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}

// Function to calculate the LCM of an array of numbers
function lcmArray(numbers) {
    // Helper function to calculate the LCM of two numbers
    function lcm(a, b) {
        return (a * b) / gcd(a, b);
    }

    // Reduce the array of numbers using the LCM function
    return numbers.reduce(function (acc, num) {
        return lcm(acc, num);
    }, 1);
}
