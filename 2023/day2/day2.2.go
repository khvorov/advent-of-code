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

func GamePower(line string) int {
	gameRe := regexp.MustCompile(`^Game (\d+):\s*(.*)$`)
	ballsRe := regexp.MustCompile(`^\s*(\d+) (red|blue|green)$`)

	match := gameRe.FindStringSubmatch(line)

	maxRed, maxGreen, maxBlue := 0, 0, 0

	choices := strings.Split(match[2], ";")

	for _, choice := range choices {
		for _, balls := range strings.Split(choice, ",") {
			match := ballsRe.FindStringSubmatch(balls)

			count, _ := strconv.Atoi(match[1])
			color := match[2]

			if color == "red" {
				maxRed = max(maxRed, count)
			} else if color == "green" {
				maxGreen = max(maxGreen, count)
			} else if color == "blue" {
				maxBlue = max(maxBlue, count)
			}
		}
	}

	power := maxRed * maxGreen * maxBlue

	// fmt.Println(line, "=>", maxRed, maxGreen, maxBlue, power)

	return power
}
func main() {
	scanner := bufio.NewScanner(os.Stdin)

	sum := 0

	for scanner.Scan() {
		line := scanner.Text()
		sum += GamePower(line)
	}

	fmt.Println(sum)
}
