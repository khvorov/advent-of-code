import re
import sys

pattern = r'(?=(one|two|three|four|five|six|seven|eight|nine|\d))'

word2digit = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9
}

def convert(match):
    if len(match) == 1 and match[0] >= '0' and match[0] <= '9':
        return int(match)
    
    return word2digit.get(match, None)

sum = 0

for line in sys.stdin:
    matches = [match.group(1) for match in re.finditer(pattern, line)]
    first, last = convert(matches[0]), convert(matches[-1])
    number = first * 10 + last
    sum += number

    print(line, matches, first, last, number, sum)

