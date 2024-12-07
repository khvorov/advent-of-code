package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	re := regexp.MustCompile("[0-9]{1}")

	sum := 0

	for scanner.Scan() {
		line := scanner.Text()
		digits := re.FindAllString(line, -1)

		first, _ := strconv.Atoi(digits[0])
		last, _ := strconv.Atoi(digits[len(digits)-1])

		var num int = first*10 + last
		sum += num

		fmt.Println(line, " ==> ", digits, ", ", num, ", ", sum)
	}
}
