import re
import sys

sum = 0

for line in sys.stdin:
    lst = [int(v) for v in line.split(" ")]
    incSorted = all(lst[i] < lst[i+1] and lst[i+1]-lst[i] <= 3 for i in range(len(lst) - 1))
    decSorted = all(lst[i] > lst[i+1] and lst[i] - lst[i+1] <= 3 for i in range(len(lst) - 1))

    sum += incSorted or decSorted

print(sum)
