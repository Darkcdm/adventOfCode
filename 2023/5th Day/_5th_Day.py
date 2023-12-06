
class Rule:
    def __init__(self, destination, source, length):
        self.source = source
        self.destination = destination
        self.length = length

    def passSeed(self, seed):
        if seed < self.source or self.source + self.length - 1 < seed:
            return seed

        Dlength = seed - self.source

        return self.destination + Dlength


def contains_number(string):
    for char in string:
        if char.isdigit():
            return True

    return False

def parseSeeds(line):
    seeds = line.split()
    return seeds[1:]


def parseMaps(text):
    almanac = []
    rules = []

    text = text.split("\n")
    for line in text:
        if contains_number(line):
            splits = line.split()
            rules.append( Rule ( int(splits[0] ) , int(splits[1] ), int(splits[2] ) ) ) 

        if len(line) == 0:
            almanac.append(rules)
            rules = []
            
    return almanac

inputFile = open("true.txt", "r").read()


seeds = parseSeeds(inputFile[:inputFile.find("\n")])

almanac = parseMaps(inputFile[inputFile.find("\n")+2:])

newSeeds = []
for seed in seeds:
    
    seed = int(seed)
    
    for category in almanac:
        for rule in category:
            newSeed = rule.passSeed(seed)
            if (seed != newSeed):
                seed = newSeed
                break

    newSeeds.append(seed)

print(newSeeds)
newSeeds.sort()
print(newSeeds)
print(newSeeds[0])