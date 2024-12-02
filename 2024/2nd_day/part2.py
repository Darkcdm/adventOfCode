import sys

input_file = sys.argv[1]
input = open(input_file, "r").read().split("\n")


def check_increase(report) -> bool:
    lastCheck = int(report[0]) - 1

    for level in report:
        if int(level) > lastCheck and 1 <= abs(abs(int(level)) - abs(lastCheck)) <= 3:
            lastCheck = int(level)
        else:
            return False
        
    return True


def check_decrease(report) -> bool:
    lastCheck = int(report[0]) + 1

    for level in report:
        if int(level) < lastCheck and 1 <= abs(abs(int(level)) - abs(lastCheck)) <= 3:
            lastCheck = int(level)
        else:
            return False
        
    return True



for i in range(len(input)):
    input[i] = input[i].split()



count = 0

for report in input:

    if check_decrease(report) or check_increase(report):
        print(report)
        count += 1
        continue

    for i in range(len(report)):
        testReport:list = report.copy()
        testReport.pop(i)

        if check_decrease(testReport) or check_increase(testReport):
            print(testReport)
            count += 1
            break

print(count)