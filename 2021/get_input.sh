#!/usr/bin/bash
# usage COOKIE=<browser session cookie> ./get_input.sh <number of day>
# the file will be stored in the ./data directory

SCRIPT_DIR=`dirname "$0"`
URL="https://adventofcode.com/2021/day/$1/input"

curl -X GET -H "cookie: session=$COOKIE" $URL > $SCRIPT_DIR/data/input$1.txt
