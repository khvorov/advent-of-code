#include <iostream>
#include <limits>

int main() {
    int pos = 0, depth = 0, aim = 0;

    std::string cmd;
    int val;

    while (std::cin >> cmd >> val) {
        switch (cmd[0]) {
            case 'f':
                pos += val;
                depth += (aim * val);
                break;

            case 'd':
                aim += val;
                break;

            case 'u':
                aim -= val;
                break;

            default:
                std::cerr << "Unknown command: " << cmd << '\n';
        }
    }

    std::cout << pos << ", " << depth << ", " << aim << ", " << (pos * depth) << '\n';

    return 0;
}
