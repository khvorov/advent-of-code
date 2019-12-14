#include <iostream>
#include <map>

#include "day11_program.h"
#include "intcode.h"

using coord_t = std::pair<std::int64_t, std::int64_t>;
using panel_t = std::map<coord_t, std::int64_t>;

void part1() {
    intcode::VM vm(day11_program);
    panel_t panel;

    std::uint64_t orientation = 0;
    coord_t xy(0, 0);

    std::uint64_t part1_answer = 0;

    while (!vm.is_halted()) {
        auto it = panel.find(xy);
        bool was_here = it != panel.end();

        std::int64_t input = panel[xy];

        std::int64_t color = vm.run(
            input, [](std::int64_t) {}, true);
        std::int64_t direction = vm.run(
            input, [](std::int64_t) {}, true);

        // paint the wall
        if (color != input && !was_here) {
            ++part1_answer;
        }

        panel[xy] = color;

        // update orientation
        if (direction == 0) {
            // turn left 90 degrees
            --orientation;
        } else if (direction == 1) {
            // turn right 90 degrees
            ++orientation;
        } else {
            // unknow direction
            throw std::runtime_error("Unknown direction");
        }
        orientation %= 4;

        // update position
        if (0 == orientation) {
            ++xy.second;
        } else if (1 == orientation) {
            ++xy.first;
        } else if (2 == orientation) {
            --xy.second;
        } else if (3 == orientation) {
            --xy.first;
        }
    }

    std::cout << "part1: " << part1_answer << '\n';
}

void part2() {
    intcode::VM vm(day11_program);
    panel_t panel;

    std::uint64_t orientation = 0;
    coord_t xy(0, 0);
    panel[xy] = 1;

    std::int64_t min_x{0}, min_y{0}, max_x{0}, max_y{0};

    while (!vm.is_halted()) {
        std::int64_t input = panel[xy];

        std::int64_t color = vm.run(
            input, [](std::int64_t) {}, true);
        std::int64_t direction = vm.run(
            input, [](std::int64_t) {}, true);

        // paint the wall
        panel[xy] = color;

        // update orientation
        if (direction == 0) {
            // turn left 90 degrees
            --orientation;
        } else if (direction == 1) {
            // turn right 90 degrees
            ++orientation;
        } else {
            // unknow direction
            throw std::runtime_error("Unknown direction");
        }
        orientation %= 4;

        // update position
        if (0 == orientation) {
            ++xy.second;
            max_y = std::max(max_y, xy.second);
        } else if (1 == orientation) {
            ++xy.first;
            max_x = std::max(max_x, xy.first);
        } else if (2 == orientation) {
            --xy.second;
            min_y = std::min(min_y, xy.second);
        } else if (3 == orientation) {
            --xy.first;
            min_x = std::min(min_x, xy.first);
        }
    }

    std::cout << "part2: " << min_x << ", " << min_y << ", " << max_x << ", " << max_y << '\n';

    std::stringstream ss;

    for (std::int64_t y = max_y; y >= min_y; --y) {
        for (std::int64_t x = min_x; x <= max_x; ++x) {
            char c = panel[std::make_pair(x, y)] ? '#' : ' ';
            ss << c;
        }
        ss << '\n';
    }

    std::cout << ss.str();
}

int main(int argc, char** argv) {
    // part 1
    part1();

    // part 2
    part2();
#if 0
    for (auto& v : panel)
    {
        std::cout << v.first.first << ", " << v.first.second << ": " << v.second << '\n';
    }
#endif

    return 0;
}
