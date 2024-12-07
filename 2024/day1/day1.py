import pandas as pd

# pre-process original input by replacing spaces with commas
df = pd.read_csv("input.txt", names=["l", "r"])

left = df["l"].sort_values().reset_index(drop=True)
right = df["r"].sort_values().reset_index(drop=True)

# part 1
part1 = (left - right).abs().sum()
print(f"part1: {part1}")

# part 2
score = 0

for num in df["l"]:
    count = (df["r"] == num).sum()
    score += num * count

print(f"part2: {score}")
