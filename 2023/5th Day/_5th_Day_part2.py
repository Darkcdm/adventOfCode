def parse(data):
    seeds = data[0].split(": ")[1].split()
    for i, seed in enumerate(seeds):
        seeds[i] = int(seed)

    maps = []
    i = -1

    for line in data[2:]:
        if not line:
            pass
        elif line[0].isdigit():
            maps[i].append(line.split())

            for j, n in enumerate(maps[i][-1]):
                maps[i][-1][j] = int(n)

        else:
            maps.append([])
            i += 1

    return seeds, maps

def locate(n, maps, reverse=False):
    if reverse:
        maps = maps[::-1]

    for map in maps:
        for submap in map:
            if reverse:
                submap = (submap[1], submap[0], submap[2])
            if n in range(submap[1], submap[1] + submap[2]):
                n += submap[0] - submap[1]
                break
    return n

def find_ranged(start, end, seeds, maps, step):
    if not step:
        return end
    for location in range(start, end + 1, step):
        for s in range(0, len(seeds), 2):
            if locate(location, maps, True) in range(seeds[s], seeds[s] + seeds[s + 1]):
                return find_ranged(location - step, location, seeds, maps, step // 10)

def run(data):
    seeds, maps = parse(data)

    single = float('inf')
    for seed in seeds:
        seed = locate(seed, maps)
        single = min(single, seed)

    span = 0
    for i in range(0, len(seeds), 2):
        span = max(span, seeds[i] + seeds[i + 1])

    '''
    There is a chance that the solution won't be computed
    correctly if your input's direct mapping has narrow
    subranges. If this is the case, try decreasing the step.
    '''

    step = 10**6
    ranged = find_ranged(0, span, seeds, maps, step)

    print(f"Part 1: {single}")
    print(f"Part 2: {ranged}")


f = open("true.txt", "r")
input = f.read().splitlines()

run(input)