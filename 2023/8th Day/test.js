const fs = require('node:fs');
const lcm = require('compute-lcm');
let answer = 1;
try {
    const input = fs.readFileSync('true', 'utf8');
    const lines = input.split("\r\n");
    const lr = lines[0].trim().split("");
    let camelmap = new Map();
    let locations = [];

    for (i = 2; i < lines.length; i++) {
        const bits = lines[i].match(/\w{3}/g);
        camelmap.set(bits[0], [bits[1], bits[2]]);
        if (bits[0].charAt(2) == 'A') locations.push(bits[0]);
    }
    console.log(locations);

    let answers = [];

    locations.forEach((loc) => {
        let i = 0;
        while (true) {
            let offset = i % lr.length;
            let lor = lr[offset];
            loc = (lor == 'L') ? camelmap.get(loc)[0] : camelmap.get(loc)[1];
            i++;
            if (loc.charAt(2) == 'Z') { answers.push(i); break; }
        }
    });
    console.log(answers);
    answer = lcm(answers);
}
catch (e) {
    console.error(e);
}

console.log("The answer to part 2 is:", answer);