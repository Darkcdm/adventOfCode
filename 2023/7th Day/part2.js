const fs = require('fs');

class Hand {

    constructor(line) {
        line = line.split(" ");

        let cardsString = line[0];
        let bidString = line[1];

        this.cards = new Array();
        this.bid = new Number(bidString);
        this.rank = 0;
        this.wins = 0;
        this.rank = -1;


        for (var i = 0; i < cardsString.length; i++) {
            this.cards.push(new Card(cardsString[i]));
        }


        this.strength = this.returnComboStrength();
    }

    returnBaseStrength(cardsCount, jockeys) {
        //Five of a kind, where all five cards have the same label: AAAAA #140

        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 5) {
                return 140;
            }
        }

        //Four of a kind, where four cards have the same label and one card has a different label: AA8AA #120
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 4) {
                return 120;
            }
        }
        //Full house, where three cards have the same label, and the remaining two cards share a different label: 23332 #100
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 3) {
                for (var j = 0; j < cardsCount.size; j++) {
                    if ([...cardsCount.entries()][j][1] == 2 && j != i) {
                        return 100;
                    }
                }
            }
        }
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] == 3) {
                for (var j = 0; j < cardsCount.size; j++) {
                    if ([...cardsCount.entries()][j][1] + jockeys == 2 && j != i) {
                        return 100;
                    }
                }
            }
        }

        //Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98 #80
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 3) {
                return 80;
            }
        }
        //Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432 #60
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 2) {
                for (var j = 0; j < cardsCount.size; j++) {
                    if (j != i && [...cardsCount.entries()][j][1] == 2 && j != i) {
                        return 60;
                    }
                }
            }
        }

        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] == 2) {
                for (var j = 0; j < cardsCount.size; j++) {
                    if (j != i && [...cardsCount.entries()][j][1] + jockeys == 2 && j != i) {
                        return 60;
                    }
                }
            }
        }
        //One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4 #40
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 2) {
                return 40;
            }
        }
        //High card, where all cards' labels are distinct: 23456 #20


        if (jockeys >= 4) {
            return 140;
        }
        if (jockeys == 3) {
            return 80;
        }
        if (jockeys == 2) {
            return 40;
        }

        return 20;

    }

    returnComboStrength() {

        let cardsCount = new Map();


        this.cards.forEach(card => {
            const currentCount = cardsCount.get(card.value) || 0;
            cardsCount.set(card.value, currentCount + 1);
        });

        let jockeys = cardsCount.get(10);
        cardsCount.delete(10);

        jockeys == undefined ? jockeys = 0 : 0;

        let baseScore = this.returnBaseStrength(cardsCount, jockeys);

        return baseScore;
    }
}

class Card {

    constructor(char) {
        this.char = char;
        let cardValuesLookup = {


            'A': 13,
            'K': 12,
            'Q': 11,
            'J': 0,
            'T': 9,
            '9': 8,
            '8': 7,
            '7': 6,
            '6': 5,
            '5': 4,
            '4': 3,
            '3': 2,
            '2': 1,

        }
        this.value = cardValuesLookup[char];
    }
}

function showDown(fighterHand, opponentHand) {

    for (let i = 0; i < fighterHand.cards.length; i++) {
        if (fighterHand.cards[i].value == opponentHand.cards[i].value) {
            continue;
        }

        /*
        if (fighterHand.cards[i].value == 10 || fighterHand.cards[i].char == 'J') {
            return -1;
        }
        if (opponentHand.cards[i].value == 10 || opponentHand.cards[i].char == 'J') {
            return 1;
        }
        */

        if (fighterHand.cards[i].value > opponentHand.cards[i].value) {
            return 1;
        } else {
            return -1;
        }
    }
}

let input = fs.readFileSync("test", 'utf8');
input = input.split('\n');

let hands = [];


for (let i = 0; i < input.length; i++) {
    hands.push(new Hand(input[i]));
}


/*
//fighting it out
for (let fighterIndex = 0; fighterIndex < hands.length; fighterIndex++) {
    for (let opponentIndex = 0; opponentIndex < hands.length; opponentIndex++) {
        if (fighterIndex == opponentIndex) {
            continue;
        }

        fighterHand = hands[fighterIndex];
        opponentHand = hands[opponentIndex];

        let holding = fighterHand.strength;

        if (fighterHand.bid == 5) {
            console.log(fighterHand);
        }

        if (fighterHand.strength == opponentHand.strength) {
            fighterHand.strength = fighterHand.strength + 
        }


        if (fighterHand.strength > opponentHand.strength) {
            fighterHand.wins++;
        } else {
            opponentHand.wins++;
        }

        fighterHand.strength = holding;
    }
}
*/

hands.sort(function (a, b) {
    let result = a.strength - b.strength;
    if (result == 0) {
        result = showDown(a, b);
    }
    return result;
});



for (let index = 0; index < hands.length; index++) {
    hands[index].rank = index + 1;
}

let totalWinnings = 0;

for (let index = 0; index < hands.length; index++) {
    totalWinnings = totalWinnings + (hands[index].rank * hands[index].bid);
}

console.log(hands);

console.log(totalWinnings);