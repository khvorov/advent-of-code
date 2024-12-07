import sys
from tqdm import tqdm

field = list()

start_pos = -1

for line in sys.stdin:
    field.append(list(line[:-1]))

    old_start_pos = start_pos

    if start_pos == -1:
        start_pos = line.find(">")
        if start_pos == -1:
            start_pos = line.find("v")
            if start_pos == -1:
                start_pos = line.find("<")
                if start_pos == -1:
                    start_pos = line.find("^");

    if start_pos != old_start_pos:
        x, y = len(field) - 1, start_pos

d = field[x][y]
field[x][y] = "."

x0, y0, d0 = x, y, d

dirs = {
    "^": (-1, 0, ">"),
    ">": (0, 1, "v"),
    "v": (1, 0, "<"),
    "<": (0, -1, "^")
}

X, Y = len(field), len(field[0])

def is_obstacle(x, y):
    v = field[x][y]

    return not (v == "." or v == "<" or v == "^" or v == ">" or v == "v")

def next_pos(x, y, d):
    nx, ny, nd = dirs[d]

    nx, ny = x + nx, y + ny
    
    if nx >= 0 and nx < X and ny >= 0 and ny < Y:
        if is_obstacle(nx, ny):
            return x, y, nd
        else:
            return nx, ny, d

    return -1, -1, "D"

count = 0
visited = {(x, y)}

# part 1
while d != "D":
    count += 1
    visited.add((x, y))

    x, y, d = next_pos(x, y, d)

print(count, len(visited))

# part 2

# try to put an obstacle at any visited position and check if there is a loop
# cycle: already visited some location with same direction
count = 0

# possible obstacle coordinates
for xo, yo in tqdm(visited):
    if xo == x0 and yo == y0:
        continue

    # start position
    field[xo][yo] = "#"

    x, y, d = x0, y0, d0

    visited2 = {(x, y, d)}

    while d != "D":
        x, y, d = next_pos(x, y, d)

        if (x, y, d) in visited2:
            count += 1
            break

        visited2.add((x, y, d))

    # remove the obstacle
    field[xo][yo] = "."
    
print(count)
