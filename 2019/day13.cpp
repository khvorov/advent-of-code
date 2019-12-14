#include <iostream>

#include "day13_program.h"
#include "intcode.h"

int main(int argc, char** argv) {
    intcode::VM vm(day13_program);

    // part 1
    std::vector<std::uint64_t> counts(5, 0);
    std::uint64_t inst_count{0};

    vm.run(0, [&](std::int64_t arg) {
        if (inst_count++ % 3 == 2) {
            counts.at(arg)++;
        }
    });

    for (auto c : counts) {
        std::cout << c << '\n';
    }

    // part 2
    // TODO

    return 0;
}
