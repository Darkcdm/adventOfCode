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

        for (var i = 0; i < cardsString.length; i++) {
            this.cards.push(new Card(cardsString[i]));
        }


        this.strength = this.returnComboStrength();
    }

    returnBaseStrength(cardsCount, jockeys) {
        if (jockeys == 5) {
            return 7;
        }


        //#7# Five of a kind, where all five cards have the same label: AAAAA
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 5) {
                return 7;
            }
        }
        //#6# Four of a kind, where four cards have the same label and one card has a different label: AA8AA
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 4) {
                return 6;
            }
        }
        //#5# Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 3) {

                let freeJockeys = 3 - (jockeys + [...cardsCount.entries()][i][1]);

                for (var j = 0; j < cardsCount.size; j++) {
                    if ([...cardsCount.entries()][j][1] + freeJockeys == 2 && j != i) {
                        return 5;
                    }
                }
            }

        }
        //#4# Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 3) {
                return 4;
            }
        }
        //#3# Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 2) {

                let freeJockeys = 2 - (jockeys + [...cardsCount.entries()][i][1]);

                for (var j = 0; j < cardsCount.size; j++) {
                    if ([...cardsCount.entries()][j][1] + freeJockeys == 2 && j != i) {
                        return 3;
                    }
                }
            }

        }
        //#2# One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
        for (var i = 0; i < cardsCount.size; i++) {
            if ([...cardsCount.entries()][i][1] + jockeys == 2) {
                return 2;
            }
        }
        //#1# High card, where all cards' labels are distinct: 23456

        return 1;
    }

    returnComboStrength() {

        let cardsCount = new Map();


        this.cards.forEach(card => {
            const currentCount = cardsCount.get(card.value) || 0;
            cardsCount.set(card.value, currentCount + 1);
        });

        let jockeys = cardsCount.get(1);
        cardsCount.delete(1);

        jockeys == undefined ? jockeys = 0 : 0;


        let baseScore = this.returnBaseStrength(cardsCount, jockeys);

        let fullScoreString = String(baseScore);

        for (let i = 0; i < this.cards.length; i++) {
            if (this.cards[i].value < 10) {
                fullScoreString += "0";
            }
            fullScoreString += String(this.cards[i].value);

        }

        return Number(fullScoreString);
    }
}

class Card {

    constructor(char) {
        this.char = char;
        let cardValuesLookup = {


            'A': 13,
            'K': 12,
            'Q': 11,
            'T': 10,
            '9': 9,
            '8': 8,
            '7': 7,
            '6': 6,
            '5': 5,
            '4': 4,
            '3': 3,
            '2': 2,
            'J': 1,

        }
        this.value = cardValuesLookup[char];
    }
}
function run(inputStr) {

    let input = fs.readFileSync(inputStr, 'utf8');
    input = input.split('\n');

    let hands = [];


    for (let i = 0; i < input.length; i++) {
        hands.push(new Hand(input[i]));
    }


    hands.sort((a, b) => {
        return a.strength - b.strength
    });

    let sumScore = 0;

    for (let i = 0; i < hands.length; i++) {
        hands[i].rank = i + 1;

        sumScore += hands[i].rank * hands[i].bid;
    }


    console.log(hands);
    console.log(sumScore);

}


run("true");