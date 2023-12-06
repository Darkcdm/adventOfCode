
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
    seeds = seeds[1:]


    seedList = []
    for seed in seeds:
        seedList.append(int(seed))

    

    return seedList

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


print("reading")

inputFile = open("true.txt", "r").read()

print("parsing and creating seeds")
seedsList = parseSeeds(inputFile[:inputFile.find("\n")])
print("going through rules")
almanac = parseMaps(inputFile[inputFile.find("\n")+2:])


index = 0
countSum = 0

while index + 2 < len(seedsList):
    countSum += seedsList[index+2]
    index +=2

print(countSum)




