// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
// Game <number>: ((<number> <color>);?)*

package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func ParseGame(line string) (int, bool) {
	gameRe := regexp.MustCompile(`^Game (\d+):\s*(.*)$`)
	ballsRe := regexp.MustCompile(`^\s*(\d+) (red|blue|green)$`)

	match := gameRe.FindStringSubmatch(line)
	gameId, _ := strconv.Atoi(match[1])

	choices := strings.Split(match[2], ";")

	for _, choice := range choices {
		for _, balls := range strings.Split(choice, ",") {
			match := ballsRe.FindStringSubmatch(balls)

			count, _ := strconv.Atoi(match[1])
			color := match[2]

			if (color == "red" && count > 12) || (color == "green" && count > 13) || (color == "blue" && count > 14) {
				return gameId, false
			}
		}
	}

	return gameId, true
}
func main() {
	scanner := bufio.NewScanner(os.Stdin)

	sum := 0

	for scanner.Scan() {
		line := scanner.Text()
		gameId, possible := ParseGame(line)

		if possible {
			sum += gameId
		}

		fmt.Println(line, "==>", gameId, possible, "==>", sum)
	}
}
