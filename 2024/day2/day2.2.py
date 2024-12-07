import re
import sys

def is_safe(lst):
    safe = all(lst[i] < lst[i+1] and lst[i+1] - lst[i] <= 3 for i in range(len(lst) - 1))
    return safe | all(lst[i] > lst[i+1] and lst[i] - lst[i+1] <= 3 for i in range(len(lst) - 1))


sum = 0

for line in sys.stdin:
    lst = [int(v) for v in line.split(" ")]

    safe = is_safe(lst)

    if not safe:
        for i in range(len(lst)):
            tmp = lst.copy()
            del tmp[i]
            safe |= is_safe(tmp)

            if safe:
                break

    sum += safe

print(sum)
