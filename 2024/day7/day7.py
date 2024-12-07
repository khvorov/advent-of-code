import sys

from itertools import product
from tqdm import tqdm

def parse_line(line):
    tgt, tail = line.split(":")
    return int(tgt), [int(v) for v in tail.strip().split(" ")]

lines = [parse_line(line[:-1]) for line in sys.stdin]

# part 1
sum = 0

for tgt, nums in tqdm(lines):
    for ops in product("+*", repeat=len(nums) - 1):
        result = nums[0]

        for i, op in enumerate(ops):
            num = nums[i + 1]

            if op == "+":
                result += num
            elif op == "*":
                result *= num

            if result > tgt:
                break

        if result == tgt:
            sum += tgt
            break

print(sum)

# part 2
sum = 0

for tgt, nums in tqdm(lines):
    for ops in product("+*|", repeat=len(nums) - 1):
        result = nums[0]

        for i, op in enumerate(ops):
            num = nums[i + 1]

            if op == "+":
                result += num
            elif op == "*":
                result *= num
            elif op == "|":
                result = int(str(result) + str(num))

            if result > tgt:
                break

        if result == tgt:
            sum += tgt
            break

print(sum)
